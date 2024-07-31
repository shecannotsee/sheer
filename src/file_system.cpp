#include "file_system.h"

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdexcept>

bool sheer::file_system::file::exists(const std::string& file_path) {
  struct stat temp {};
  const auto ret = (stat(file_path.c_str(), &temp) == 0);
  return ret;
}

void sheer::file_system::file::create(const std::string& file_path) {
  if (file_system::file::exists(file_path)) {
    return;
  }
  FILE* file = fopen(file_path.c_str(), "w");
  if (!file) {
    throw std::runtime_error("Failed to create file " + file_path);
  }
  fclose(file);
}

void sheer::file_system::file::remove(const std::string& file_path) {
  if (unlink(file_path.c_str()) != 0) {
    throw std::runtime_error("Failed to delete file " + file_path);
  }
}

auto sheer::file_system::directory::list(const std::string& dir_path) -> std::vector<std::tuple<type, std::string>> {
  std::vector<std::tuple<type, std::string>> lists;

  DIR* dir = opendir(dir_path.c_str());
  if (!dir) {
    throw std::runtime_error("Failed to open directory " + dir_path);
  }

  struct dirent* entry;
  struct stat statbuf;
  while ((entry = readdir(dir)) != nullptr) {
    std::string entry_name = entry->d_name;
    if (entry_name == "." || entry_name == "..") {
      continue;
    }

    std::string entry_path;
    if (dir_path.back() != '/') {
      entry_path = dir_path + "/" + entry_name;
    } else {
      entry_path = dir_path + entry_name;
    }

    if (stat(entry_path.c_str(), &statbuf) != 0) {
      closedir(dir);
      throw std::runtime_error("Failed to stat entry " + entry_path);
    }

    if (S_ISDIR(statbuf.st_mode)) {
      lists.emplace_back(type::DIRECTORY, entry_name);
    } else {
      lists.emplace_back(type::FILE, entry_name);
    }
  }

  closedir(dir);

  return lists;
}

bool sheer::file_system::directory::exists(const std::string& dir_path) {
  struct stat info {};
  if (stat(dir_path.c_str(), &info) != 0) {
    // Cannot access the path (file/directory does not exist)
    return false;
  }
  // The path exists and it is a directory
  if (info.st_mode & S_IFDIR) {
    return true;
  }
  // The path exists but it is not a directory
  return false;
}

void sheer::file_system::directory::create(const std::string& dir_path) {
  if (file_system::directory::exists(dir_path)) {
    return;
  }
  // Mode 0755 gives read, write, and execute permissions to the owner,
  // and read and execute permissions to group and others
  constexpr mode_t mode = 0755;

  const auto size = dir_path.size();
  std::string use_dir_path;
  for (int i = 0; i < size; i++) {
    // check
    if ((dir_path[i] == '/' && use_dir_path.back() != '.') || (i == (size - 1))) {
      if (i == size - 1) {
        use_dir_path += dir_path[i];
      }
      // mkdir
      if (const int ret = mkdir(use_dir_path.c_str(), mode); ret != 0) {
        throw std::runtime_error(std::string("Failed to create directory: " + use_dir_path));
      }
    }
    use_dir_path += dir_path[i];
  }
}

void sheer::file_system::directory::remove(const std::string& dir_path) {
  if (rmdir(dir_path.c_str()) != 0) {
    throw std::runtime_error(std::string("Failed to delete directory(The directory may not be empty) " + dir_path));
  }
}

void sheer::file_system::directory::remove_all(const std::string& dir_path) {
  auto entries = directory::list(dir_path);
  for (const auto& entry : entries) {
    const auto& entry_type = std::get<0>(entry);
    const auto& entry_name = std::get<1>(entry);
    std::string entry_path;
    if (dir_path.back() != '/') {
      entry_path = dir_path + "/" + entry_name;
    } else {
      entry_path = dir_path + entry_name;
    }

    if (entry_type == type::DIRECTORY) {
      // Recursively remove the directory
      directory::remove_all(entry_path);
    } else {
      // Remove the file
      file::remove(entry_path);
    }
  }

  // Remove the now-empty directory
  directory::remove(dir_path);
}
