#ifndef SHEER_DATE_TIME_H
#define SHEER_DATE_TIME_H

#include <chrono>
#include <iomanip>
#include <string>

namespace sheer {

class date_time {
 public:
  /**
   * @brief Get the current time point.
   *
   * This method returns a `std::chrono::time_point` object representing the current system time.
   *
   * @return The current time point.
   */
  static auto get_time_point() -> std::chrono::time_point<std::chrono::system_clock> {
    return std::chrono::system_clock::now();
  }

  /**
   * @brief Convert the time point to a specific duration.
   *
   * This template function converts the given time point to a duration since the Unix epoch (1970-01-01).
   * The duration type is specified by the template parameter `Duration`, such as `std::chrono::seconds` for seconds,
   * `std::chrono::milliseconds` for milliseconds, and `std::chrono::microseconds` for microseconds.
   *
   * @tparam duration The type of duration (e.g., `std::chrono::seconds`, `std::chrono::milliseconds`,
   * `std::chrono::microseconds`).
   * @param time_point The time point to convert.
   * @return The duration since the Unix epoch in the specified units.
   */
  template <typename duration>
  static long long to_duration_number(const std::chrono::system_clock::time_point& time_point) {
    return std::chrono::duration_cast<duration>(time_point.time_since_epoch()).count();
  }

  /**
   * @brief Convert the time point to a date string.
   *
   * This method converts the given time point to a formatted string in the form "YYYY-MM-DD HH:MM:SS".
   *
   * @param time_point The time point to convert.
   * @return A formatted date string.
   */
  static std::string format_date_string(const std::chrono::system_clock::time_point& time_point) {
    std::time_t time = std::chrono::system_clock::to_time_t(time_point);
    std::tm tm       = *std::localtime(&time);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
  }
};

}  // namespace sheer

#endif  // SHEER_DATE_TIME_H
