#ifndef SHEER_TIMER_H
#define SHEER_TIMER_H

#include <chrono>
#include <stdexcept>

namespace sheer {

class timer {
  std::chrono::high_resolution_clock::time_point start_time{};  ///< Start timestamp
  std::chrono::high_resolution_clock::time_point end_time{};    ///< End timestamp

 public:
  /**
   * @brief Record the start time.
   *
   * This method records the current time as the start time using the high resolution clock.
   */
  void start() {
    start_time = std::chrono::high_resolution_clock::now();
  }

  /**
   * @brief Record the end time.
   *
   * This method records the current time as the end time using the high resolution clock.
   */
  void end() {
    end_time = std::chrono::high_resolution_clock::now();
  }

  /**
   * @brief Calculate the interval between start and end times.
   *
   * This template function calculates the elapsed time between the recorded start and end times.
   * The duration type is specified by the template parameter `Duration`, such as `std::chrono::seconds` for seconds,
   * `std::chrono::milliseconds` for milliseconds, and `std::chrono::microseconds` for microseconds.
   *
   * @tparam Duration The type of duration (e.g., `std::chrono::seconds`, `std::chrono::milliseconds`,
   * `std::chrono::microseconds`).
   * @return The elapsed time between the start and end times in the specified units.
   * @throws std::runtime_error If start or end time has not been set.
   */
  template <typename Duration>
  [[nodiscard]] long long get_elapsed() const {
    if (start_time == std::chrono::high_resolution_clock::time_point{} ||
        end_time == std::chrono::high_resolution_clock::time_point{}) {
      throw std::runtime_error("Please use the interface correctly before obtaining the time interval");
    }
    Duration elapsed = std::chrono::duration_cast<Duration>(end_time - start_time);
    return elapsed.count();
  }
};

}  // namespace sheer

#endif  // SHEER_TIMER_H
