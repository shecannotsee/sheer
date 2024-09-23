#include "io.h"

#include <fstream>
#include <stdexcept>

auto sheer::io::read_binary_file(const std::string& file_path) -> std::vector<uint8_t> {
  // 打开文件，二进制模式和输入模式
  std::ifstream file(file_path, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    throw std::runtime_error(std::string("Failed to open file: " + file_path));
  }

  // 获取文件大小
  const std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  // 创建缓冲区
  std::vector<uint8_t> buffer(size);
  if (file.read(reinterpret_cast<char*>(buffer.data()), size)) {
    return buffer;
  } else {
    throw std::runtime_error(std::string("Failed to read file: " + file_path));
  }
}

void sheer::io::append_to_file(const std::string& file_path, const std::vector<uint8_t>& data) {
  std::ofstream file(file_path, std::ios::binary | std::ios::app);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file " + file_path);
  }
  file.write(reinterpret_cast<const char*>(data.data()), data.size());
  if (!file) {
    throw std::runtime_error("Failed to write to file " + file_path);
  }
}

void sheer::io::append_to_file(const std::string& file_path, const std::string& data) {
  std::ofstream file(file_path, std::ios::app);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file " + file_path);
  }
  file << data;
  if (!file) {
    throw std::runtime_error("Failed to write to file " + file_path);
  }
}

void sheer::io::clear_and_write(const std::string& file_path, const std::vector<uint8_t>& data) {
  std::ofstream file(file_path, std::ios::binary | std::ios::trunc);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file " + file_path);
  }
  file.write(reinterpret_cast<const char*>(data.data()), data.size());
  if (!file) {
    throw std::runtime_error("Failed to write to file " + file_path);
  }
}

void sheer::io::clear_and_write(const std::string& file_path, const std::string& data) {
  std::ofstream file(file_path, std::ios::trunc);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open file " + file_path);
  }
  file << data;
  if (!file) {
    throw std::runtime_error("Failed to write to file " + file_path);
  }
}
