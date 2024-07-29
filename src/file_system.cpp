#include "file_system.h"

bool sheer::file_system::is_directory_exists(const std::string& full_path) {
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

bool sheer::file_system::is_directory_exists(const std::string& dir_path, const std::string& dir_name) {
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

void sheer::file_system::create_dir(const std::string& dir_path) {
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

void sheer::file_system::remove_directory(const std::string& dir_path) {
  if (rmdir(dir_path.c_str()) != 0) {
    throw std::runtime_error(std::string("Failed to delete directory " + dir_path));
  }
}
