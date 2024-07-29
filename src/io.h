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
   * @param file_path Path to the file
   * @return A vector containing the binary data read from the file
   */
  static auto read_binary_file(const std::string& file_path) -> std::vector<uint8_t>;

  /**
   * @brief Append binary data to a file
   * @param file_path Path to the file
   * @param data Binary data to be appended to the file
   */
  static void append_to_file(const std::string& file_path, const std::vector<uint8_t>& data);

  /**
   * @brief Append string data to a file
   * @param file_path Path to the file
   * @param data String data to be appended to the file
   */
  static void append_to_file(const std::string& file_path, const std::string& data);

  /**
   * @brief Clear the contents of a file and write binary data to it
   * @param file_path Path to the file
   * @param data Binary data to be written to the file
   */
  static void clear_and_write(const std::string& file_path, const std::vector<uint8_t>& data);

  /**
   * @brief Clear the contents of a file and write string data to it
   * @param file_path Path to the file
   * @param data String data to be written to the file
   */
  static void clear_and_write(const std::string& file_path, const std::string& data);
};
}  // namespace sheer

#endif  // SHEER_IO_H
