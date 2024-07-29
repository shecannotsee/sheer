#ifndef SHEER_STRING_ALIGNMENT_H
#define SHEER_STRING_ALIGNMENT_H

#include <algorithm>  // for std::max
#include <string>

namespace sheer {

class string_support {
  /**
   * @brief Left-aligns a string within a specified width.
   *
   * If the string length is less than the specified width, spaces are appended to the right
   * of the string until it reaches the desired width.
   *
   * @param str The string to align.
   * @param width The desired width.
   */
  static void left_align_string(std::string& str, const size_t width) {
    if (str.length() < width) {
      str.append(width - str.length(), ' ');
    }
  }

  /**
   * @brief Center-aligns a string within a specified width.
   *
   * If the string length is less than the specified width, spaces are added equally
   * to the left and right sides of the string until it reaches the desired width.
   *
   * @param str The string to align.
   * @param width The desired width.
   */
  static void center_align_string(std::string& str, const size_t width) {
    if (str.length() < width) {
      const size_t left_padding  = (width - str.length()) / 2;
      const size_t right_padding = width - str.length() - left_padding;
      str.insert(0, left_padding, ' ');
      str.append(right_padding, ' ');
    }
  }

  /**
   * @brief Right-aligns a string within a specified width.
   *
   * If the string length is less than the specified width, spaces are inserted
   * to the left of the string until it reaches the desired width.
   *
   * @param str The string to align.
   * @param width The desired width.
   */
  static void right_align_string(std::string& str, const size_t width) {
    if (str.length() < width) {
      str.insert(0, width - str.length(), ' ');
    }
  }

  /**
   * @brief Calculates the maximum length among several strings.
   *
   * This function determines the length of the longest string among the provided strings.
   *
   * @return The maximum length among the strings.
   */
  static size_t max_length() {
    return 0;
  }

  /**
   * @brief Calculates the maximum length among several strings.
   *
   * This recursive template function calculates the length of the longest string
   * among the provided strings using std::max.
   *
   * @tparam T The type of the first string.
   * @tparam Ts The types of the remaining strings.
   * @param first The first string.
   * @param rest The remaining strings.
   * @return The maximum length among the strings.
   */
  template <typename T, typename... Ts>
  static size_t max_length(const T& first, const Ts&... rest) {
    return std::max(first.size(), max_length(rest...));
  }

 public:
  /**
   * @brief Enum specifying the alignment options.
   */
  enum class alignment { LEFT, CENTER, RIGHT };

  /**
   * @brief Aligns multiple strings based on the specified alignment method and maximum length.
   *
   * This function aligns multiple strings according to the specified alignment method
   * (LEFT, CENTER, or RIGHT) using the maximum length among the strings.
   *
   * @tparam Strings The types of the strings to align.
   * @param align_method The alignment method (LEFT, CENTER, or RIGHT).
   * @param strs The strings to align.
   */
  template <typename... Strings>
  static void align(const alignment align_method, Strings&... strs) {
    size_t max_len = max_length(strs...);

    switch (align_method) {
      case alignment::LEFT:
        (left_align_string(strs, max_len), ...);
        break;
      case alignment::CENTER:
        (center_align_string(strs, max_len), ...);
        break;
      case alignment::RIGHT:
        (right_align_string(strs, max_len), ...);
        break;
    }
  }
};

}  // namespace sheer

#endif  // SHEER_STRING_ALIGNMENT_H
