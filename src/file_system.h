#ifndef SHEER_FILE_SYSTEM_H
#define SHEER_FILE_SYSTEM_H

#include <string>

namespace sheer {

class file_system {
 public:
  /**
   * @brief Used to check if the directory exists
   * @param full_path Complete path
   * @return true means the directory exists, false means the directory does not exist
   */
  static bool is_directory_exists(const std::string& full_path);

  /**
   * @brief Used to check if the directory exists
   * @param dir_path example:"/path/to/your/directory"
   * @param dir_name example:"target_folder"
   * @return true means the directory exists, false means the directory does not exist
   */
  static bool is_directory_exists(const std::string& dir_path, const std::string& dir_name);

  /**
   * @brief create dir.Before creating a directory, check if the directory exists
   * @param dir_path dir path
   * @throw Failed to create
   */
  static void create_dir(const std::string& dir_path);

  /**
   * @brief Delete dir
   * @param dir_path dir path
   * @throw Failed to delete
   */
  static void remove_directory(const std::string& dir_path);
};

}  // namespace sheer

#endif  // SHEER_FILE_SYSTEM_H
