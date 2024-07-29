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
   * @brief Recording start time
   */
  void start() {
    start_time = std::chrono::high_resolution_clock::now();
  }

  /**
   * @brief Recording end time
   */
  void end() {
    end_time = std::chrono::high_resolution_clock::now();
  }

  /**
   * @brief Calculate the interval between start and end times
   * @tparam Duration
   * std::chrono::seconds seconds;
   * std::chrono::milliseconds milliseconds;
   * std::chrono::microseconds microseconds;
   * @return The time elapsed between the start and end
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
