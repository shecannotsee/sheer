#ifndef TIMED_CACHE_QUEUE_H
#define TIMED_CACHE_QUEUE_H

#include <condition_variable>
#include <queue>
#include <thread>

template <typename T>
class timed_cache_queue {
 public:
  timed_cache_queue() = delete;

  explicit timed_cache_queue(const int cache_time_in_seconds)
      : cache_time_(cache_time_in_seconds), stop_thread_(false) {
    cleanup_thread_ = std::thread(&timed_cache_queue::cleanup_expired_elements, this);
  }

  ~timed_cache_queue() {
    stop_thread_ = true;
    cv_.notify_all();
    if (cleanup_thread_.joinable()) {
      cleanup_thread_.join();
    }
  }

 private:
  std::queue<T> queue_;
  int cache_time_;
  mutable std::mutex mutex_;
  std::condition_variable cv_;
  std::thread cleanup_thread_;
  bool stop_thread_;

 private:
  void cleanup_expired_elements() {
    while (!stop_thread_) {
      std::unique_lock<std::mutex> lock(mutex_);
      cv_.wait_for(lock, std::chrono::seconds(cache_time_), [this] { return stop_thread_ || !queue_.empty(); });

      if (stop_thread_) {
        break;
      }

      auto now = std::chrono::system_clock::now();
      while (!queue_.empty() && queue_.front().timestamp + std::chrono::seconds(cache_time_) < now) {
        queue_.pop();
      }
    }
  }

 public:
  size_t size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
  }

  void push(const T& element) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(element);
  }
};

#endif  // TIMED_CACHE_QUEUE_H
