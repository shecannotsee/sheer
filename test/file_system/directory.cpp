#include <she_test.h>
#include <sheer.h>

SHE_TEST(file_system, directory_list) {
  using fs = test_support::file_system;

  auto lists = fs::directory::list("./");

  for (auto element : lists) {
    if (std::get<0>(element) == fs::type::FILE) {
      std::cout << "file: ";
    } else {
      std::cout << " dir: ";
    }
    std::cout << std::get<1>(element) << std::endl;
  }

  return true;
}

SHE_TEST(file_system, directory_create_and_remove) {
  using fs             = test_support::file_system;
  using string_support = test_support::string_support;

  const std::string dir_depth_1 = "./dir_depth_1/";
  const std::string dir_depth_2 = "dir_depth_2/";
  const std::string dir_depth_3 = "dir_depth_3/";

  std::string expect_exists     = "expect exists... ";
  std::string expect_not_exists = "expect not exists... ";
  std::string create            = "create";
  std::string remove            = "remove";
  std::string remove_all        = "remove_all";
  string_support::align(string_support::alignment::LEFT, expect_exists, expect_not_exists, create, remove, remove_all);
  auto check_dir = [](const std::string& expect, const std::string& dir_path) {
    std::cout << expect;
    if (fs::directory::exists(dir_path)) {
      std::cout << dir_path << " exists\n";
    } else {
      std::cout << dir_path << " not exists\n";
    }
  };

  check_dir(expect_not_exists, dir_depth_1 + dir_depth_2 + dir_depth_3);
  fs::directory::create(dir_depth_1 + dir_depth_2 + dir_depth_3);
  std::cout << create << dir_depth_1 + dir_depth_2 + dir_depth_3 << std::endl;
  check_dir(expect_exists, dir_depth_1 + dir_depth_2 + dir_depth_3);

  fs::directory::remove(dir_depth_1 + dir_depth_2 + dir_depth_3);
  std::cout << remove << dir_depth_1 + dir_depth_2 + dir_depth_3 << std::endl;
  check_dir(expect_not_exists, dir_depth_1 + dir_depth_2 + dir_depth_3);

  check_dir(expect_exists, dir_depth_1 + dir_depth_2);
  fs::directory::remove(dir_depth_1 + dir_depth_2);
  std::cout << remove << dir_depth_1 + dir_depth_2 << std::endl;
  check_dir(expect_not_exists, dir_depth_1 + dir_depth_2);

  check_dir(expect_exists, dir_depth_1);
  fs::directory::remove(dir_depth_1);
  std::cout << remove << dir_depth_1 << std::endl;
  check_dir(expect_not_exists, dir_depth_1);
  // dir cleaning completed

  check_dir(expect_not_exists, dir_depth_1 + dir_depth_2 + dir_depth_3);
  fs::directory::create(dir_depth_1 + dir_depth_2 + dir_depth_3);
  std::cout << create << dir_depth_1 + dir_depth_2 + dir_depth_3 << std::endl;
  check_dir(expect_exists, dir_depth_1 + dir_depth_2 + dir_depth_3);
  check_dir(expect_exists, dir_depth_1 + dir_depth_2);
  check_dir(expect_exists, dir_depth_1);

  fs::directory::remove_all(dir_depth_1);
  std::cout << remove_all << dir_depth_1 << std::endl;
  check_dir(expect_not_exists, dir_depth_1 + dir_depth_2 + dir_depth_3);
  check_dir(expect_not_exists, dir_depth_1 + dir_depth_2);
  check_dir(expect_not_exists, dir_depth_1);

  return true;
}

SHE_TEST(file_system, directory_remove_boundary) {
  using fs = test_support::file_system;

  const std::string file_path      = "directory_boundary.txt";
  const std::string directory_path = "./directory_boundary/";
  fs::directory::create(directory_path);
  fs::file::create(directory_path + file_path);
  try {
    fs::directory::remove(directory_path);
  } catch (const std::runtime_error& ex) {
    printf("%s\n", ex.what());
  }
  fs::file::remove(directory_path + file_path);
  fs::directory::remove(directory_path);

  if (!fs::directory::exists(directory_path)) {
    std::cout << "dir right\n";
  }
  if (!fs::file::exists(directory_path + file_path)) {
    std::cout << "file right\n";
  }

  return true;
}
