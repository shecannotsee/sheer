#ifndef SHEER_FILE_SYSTEM_H
#define SHEER_FILE_SYSTEM_H

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdexcept>
#include <string>

namespace sheer {

class file_system {
 public:
  /**
   * @brief Used to check if the directory exists
   * @param full_path Complete path
   * @return true means the directory exists, false means the directory does not exist
   */
  static bool is_directory_exists(const std::string& full_path) {
    struct stat info {};
    if (stat(full_path.c_str(), &info) != 0) {
      // Cannot access the path (file/directory does not exist)
      return false;
    } else if (info.st_mode & S_IFDIR) {
      // The path exists and it is a directory
      return true;
    } else {
      // The path exists but it is not a directory
      return false;
    }
  }

  /**
   * @brief Used to check if the directory exists
   * @param dir_path example:"/path/to/your/directory"
   * @param dir_name example:"target_folder"
   * @return true means the directory exists, false means the directory does not exist
   */
  static bool is_directory_exists(const std::string& dir_path, const std::string& dir_name) {
    DIR* dir = opendir(dir_path.c_str());
    if (dir == nullptr) {
      return false;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
      if (entry->d_type == DT_DIR && entry->d_name == dir_name) {
        closedir(dir);
        return true;
      }
    }

    closedir(dir);
    return false;
  }

  /**
   * @brief create dir.Before creating a directory, check if the directory exists
   * @param dir_path dir path
   * @throw Failed to create
   */
  static void create_dir(const std::string& dir_path) {
    if (is_directory_exists(dir_path)) {
      return;
    }
    // Mode 0755 gives read, write, and execute permissions to the owner,
    // and read and execute permissions to group and others
    mode_t mode = 0755;

    // Create the directory
    int result = mkdir(dir_path.c_str(), mode);

    if (result != 0) {
      throw std::runtime_error(std::string("Failed to create directory: " + dir_path));
    }
  }

  /**
   * @brief Delete dir
   * @param dir_path dir path
   * @throw Failed to delete
   */
  static void remove_directory(const std::string& dir_path) {
    if (rmdir(dir_path.c_str()) != 0) {
      throw std::runtime_error(std::string("Failed to delete directory " + dir_path));
    }
  }
};

}  // namespace sheer

#endif  // SHEER_FILE_SYSTEM_H
