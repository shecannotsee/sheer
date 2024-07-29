#include <she_test.h>
#include <sheer.h>

SHE_TEST(file_system, file) {
  using fs = test_support::file_system;
  using string_support = test_support::string_support;


  const std::string test_file_path = "./test_file_system.file_list";

  std::string expect_exists     = "expect exists...";
  std::string expect_not_exists = "expect not exists...";
  string_support::align(string_support::alignment::LEFT, expect_exists, expect_not_exists);
  auto check_file = [](const std::string& expect, const std::string& file_path) {
    std::cout << expect << " ";
    if (fs::file::exists(file_path)) {
      std::cout << file_path << " exists\n";
    } else {
      std::cout << file_path << " not exists\n";
    }
  };

  check_file(expect_not_exists,test_file_path);
  fs::file::create(test_file_path);
  check_file(expect_exists,test_file_path);

  fs::file::remove(test_file_path);
  check_file(expect_not_exists,test_file_path);


  return true;
}


