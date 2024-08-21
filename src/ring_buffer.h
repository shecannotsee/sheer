#ifndef SHEER_RING_BUFFER_H
#define SHEER_RING_BUFFER_H

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace sheer {
/**
 * @brief A simple ring buffer (circular buffer) implementation.
 *        This implementation is not thread-safe.
 * @tparam T The data type to be stored in the buffer.
 */
template <typename T>
class ring_buffer {
  std::vector<T> data_{};  ///< Container to hold the actual data.
  bool empty_{
      true};        ///< Indicates whether the buffer is empty. Initially true, turns false after first data insertion.
  size_t head_{0};  ///< Index of the head (start) of the buffer where data can be read.
  size_t tail_{0};  ///< Index of the tail (end) of the buffer where data can be written.

  /**
   * @brief Updates the buffer's indices after a new element is added.
   *        Adjusts the tail index and, if necessary, moves the head index
   *        to maintain the circular nature of the buffer.
   */
  void update_index() {
    if (empty_) {
      empty_ = false;
    }
    tail_++;
    if (tail_ == data_.size()) {
      tail_ = 0;
    }

    if (tail_ == head_) {
      head_++;
      if (head_ == data_.size()) {
        head_ = 0;
      }
    }
  }

 public:
  /**
   * @brief Default constructor. Initializes an empty ring buffer.
   */
  ring_buffer() = default;

  /**
   * @brief Constructor to initialize the buffer with a specific size.
   * @param buffer_size The maximum number of elements the buffer can hold.
   */
  explicit ring_buffer(const uint64_t buffer_size) : data_(buffer_size + 1) {
  }

  /**
   * @brief Default destructor.
   */
  ~ring_buffer() = default;

 public:
  /**
   * @brief Adds a new element to the end (tail) of the buffer.
   *        If the buffer is full, the oldest element is overwritten.
   * @param value The element to be added to the buffer.
   */
  void push_back(const T& value) {
    data_[tail_] = value;
    update_index();
  }

  /**
   * @brief Adds a new element to the end (tail) of the buffer using move semantics.
   *        If the buffer is full, the oldest element is overwritten.
   * @param value The element to be moved into the buffer.
   */
  void push_back(T&& value) {
    data_[tail_] = std::move(value);
    update_index();
  }

  /**
   * @brief Retrieves the last element (most recently added) from the buffer.
   * @return A reference to the last element in the buffer.
   * @throws std::runtime_error if the buffer is empty.
   */
  auto back() -> T& {
    if (empty_) {
      throw std::runtime_error("Buffer is empty");
    }
    size_t index = (tail_ == 0 ? data_.size() - 1 : tail_ - 1);  // Calculate the index of the last element.
    return data_[index];
  }

  /**
   * @brief Checks if the buffer is empty.
   * @return True if the buffer is empty, false otherwise.
   */
  [[nodiscard]] auto empty() const -> bool {
    return empty_;
  }

  /**
   * @brief Retrieves all elements currently stored in the buffer in order.
   *        The elements are returned as a vector, starting from the head of the buffer.
   * @return A vector containing all the elements in the buffer.
   */
  auto get() -> std::vector<T> {
    if (empty_) {
      return {};
    }

    std::vector<T> ret;
    if (head_ <= tail_) {
      ret.insert(ret.end(), data_.begin() + head_, data_.begin() + tail_);
    } else {
      ret.insert(ret.end(), data_.begin() + head_, data_.end());
      ret.insert(ret.end(), data_.begin(), data_.begin() + tail_);
    }
    return ret;
  }
};
}  // namespace sheer

#endif  // SHEER_RING_BUFFER_H
