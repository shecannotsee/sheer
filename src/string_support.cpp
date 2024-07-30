#include "string_support.h"

namespace sheer {
void string_support::left_align_string(std::string& str, const size_t width) {
  if (str.length() < width) {
    str.append(width - str.length(), ' ');
  }
}

void string_support::center_align_string(std::string& str, const size_t width) {
  if (str.length() < width) {
    const size_t left_padding  = (width - str.length()) / 2;
    const size_t right_padding = width - str.length() - left_padding;
    str.insert(0, left_padding, ' ');
    str.append(right_padding, ' ');
  }
}
void string_support::right_align_string(std::string& str, const size_t width) {
  if (str.length() < width) {
    str.insert(0, width - str.length(), ' ');
  }
}



}  // namespace sheer