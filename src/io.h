#ifndef SHEER_IO_H
#define SHEER_IO_H

#include <cstdint>
#include <string>
#include <vector>

class io {
 public:
  /**
   * @brief Read binary data from a file
   * @param file_path file path
   * @return Read binary data stream
   */
  static auto read_binary_file(const std::string& file_path) -> std::vector<uint8_t>;

  /**
   * @brief Write binary data to a file
   * @param file_path file path
   * @param data data to write
   */
  static void write_binary_to_file(const std::string& file_path, const std::vector<uint8_t>& data);
};

#endif  // SHEER_IO_H
