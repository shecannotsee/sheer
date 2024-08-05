#ifndef SHEER_FILE_SYSTEM_H
#define SHEER_FILE_SYSTEM_H

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

namespace sheer {

class file_system {
 public:
  /**
   * @brief Enum representing the type of a filesystem entry.
   */
  enum class type { FILE, DIRECTORY };

  /**
   * @brief Class providing file operations.
   */
  class file {
   public:
    /**
     * @brief Checks if a file exists at the specified path.
     *
     * @param file_path The path of the file to check.
     * @return true if the file exists, false otherwise.
     */
    [[nodiscard]] static bool exists(const std::string& file_path);

    /**
     * @brief Creates a file at the specified path.
     *
     * Checks if the file exists before attempting to create it.
     *
     * @param file_path The path of the file to create.
     */
    static void create(const std::string& file_path);

    /**
     * @brief Removes the file at the specified path.
     *
     * @param file_path The path of the file to remove.
     */
    static void remove(const std::string& file_path);
  };

  /**
   * @brief Class providing directory operations.
   */
  class directory {
   public:
    /**
     * @brief Lists the contents of a directory.
     *
     * @param dir_path The path of the directory to list.
     * @return A vector of tuples, each containing the type (file or directory) and name of an entry.
     */
    [[nodiscard]] static auto list(const std::string& dir_path) -> std::vector<std::tuple<type, std::string>>;

    /**
     * @brief Checks if a directory exists at the specified path.
     *
     * @param dir_path The path of the directory to check.
     * @return true if the directory exists, false otherwise.
     */
    [[nodiscard]] static bool exists(const std::string& dir_path);

    /**
     * @brief Creates a directory at the specified path.
     *
     * Checks if the directory exists before attempting to create it.
     *
     * @param dir_path The path of the directory to create.
     * @throws std::runtime_error if the directory cannot be created.
     */
    static void create(const std::string& dir_path);

    /**
     * @brief Removes the directory at the specified path.
     *
     * @param dir_path The path of the directory to remove.
     * @throws std::runtime_error if the directory(not empty) cannot be removed.
     */
    static void remove(const std::string& dir_path);

    /**
     * @brief Recursively removes a directory and all its contents.
     *
     * @param dir_path The path of the directory to remove.
     */
    static void remove_all(const std::string& dir_path);
  };
};

}  // namespace sheer

#endif  // SHEER_FILE_SYSTEM_H
