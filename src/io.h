#ifndef SHEER_IO_H
#define SHEER_IO_H

#include <cstdint>
#include <string>
#include <vector>

namespace sheer {
class io {
 public:
  /**
   * @brief Read binary data from a file
   * @param file_path file path
   * @return Read binary data stream
   */
  static auto read_binary_file(const std::string& file_path) -> std::vector<uint8_t>;

  static void append_to_file(const std::string& file_path, const std::vector<uint8_t>& data);

  static void append_to_file(const std::string& file_path, const std::string& data);

  static void clear_and_write(const std::string& file_path, const std::vector<uint8_t>& data);

  static void clear_and_write(const std::string& file_path, const std::string& data);
};
}  // namespace sheer

#endif  // SHEER_IO_H
