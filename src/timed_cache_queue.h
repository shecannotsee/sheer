#ifndef SHEER_TIMED_CACHE_QUEUE_H
#define SHEER_TIMED_CACHE_QUEUE_H

#include <condition_variable>
#include <cstdint>
#include <queue>
#include <thread>

namespace sheer {

// Forward declaration of timed_cache_queue
template <typename T>
class timed_cache_queue;

// Primary template for checking timestamp member
template <typename T, typename = void>
struct has_timestamp_member : std::false_type {};

// Specialization for types that have a timestamp member
template <typename T>
struct has_timestamp_member<T, std::void_t<decltype(std::declval<T>().timestamp)>> : std::true_type {};

/**
 * @brief A thread-safe queue with timed element eviction based on their timestamps.
 *
 * @tparam T The type of elements stored in the queue. Must have a public member 'timestamp' of type
 * std::chrono::time_point.
 */
template <typename T>
class timed_cache_queue {
  static_assert(has_timestamp_member<T>::value, "T must have a 'timestamp' member of type std::chrono::time_point");

 public:
  /**
   * @brief Deleted default constructor. Use explicit constructor to initialize.
   */
  timed_cache_queue() = delete;

  /**
   * @brief Constructs a timed cache queue with a specified cache expiration time.
   *
   * @param cache_time_in_seconds The time in seconds after which elements are evicted from the queue.
   */
  explicit timed_cache_queue(const int cache_time_in_seconds)
      : cache_time_(cache_time_in_seconds), stop_thread_(false) {
    cleanup_thread_ = std::thread(&timed_cache_queue::cleanup_expired_elements, this);
  }

  /**
   * @brief Destructor. Stops the cleanup thread and waits for it to join.
   */
  ~timed_cache_queue() {
    stop_thread_ = true;
    cv_.notify_all();
    if (cleanup_thread_.joinable()) {
      cleanup_thread_.join();
    }
  }

 private:
  std::queue<T> queue_;         ///< The queue storing elements of type T.
  int32_t cache_time_;          ///< Time in seconds after which elements are considered expired.
  mutable std::mutex mutex_;    ///< Mutex to synchronize access to the queue.
  std::condition_variable cv_;  ///< Condition variable to signal changes in the queue.
  std::thread cleanup_thread_;  ///< Thread for periodically cleaning up expired elements.
  bool stop_thread_;            ///< Flag to signal the cleanup thread to stop.

 private:
  /**
   * @brief Worker function for the cleanup thread that removes expired elements from the queue.
   */
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
  /**
   * @brief Returns the number of elements currently in the queue.
   *
   * @return size_t The number of elements in the queue.
   */
  size_t size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.size();
  }

  /**
   * @brief Adds an element to the queue.
   *
   * @param element The element to be added to the queue.
   */
  void push(const T& element) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(element);
  }

  /**
   * @brief Removes the front element from the queue, if available.
   *
   * @param element Reference to store the popped element.
   * @return true If an element was successfully popped.
   * @return false If the queue was empty.
   */
  bool pop(T& element) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
      return false;
    }
    element = queue_.front();
    queue_.pop();
    return true;
  }
};

}  // namespace sheer

#endif  // SHEER_TIMED_CACHE_QUEUE_H
