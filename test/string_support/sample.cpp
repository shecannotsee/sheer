#include <she_test.h>
#include <sheer.h>

SHE_TEST(string_support, alignment_sample) {
  using string_support = test_support::string_support;

  {
    std::string str1 = "1";
    std::string str2 = "22";
    std::string str3 = "333";
    std::string str4 = "4444";
    std::string str5 = "55555";
    string_support::align(string_support::alignment::LEFT, str1, str2, str3, str4, str5);

    std::cout << "|" << str1 << "|" << std::endl;
    std::cout << "|" << str2 << "|" << std::endl;
    std::cout << "|" << str3 << "|" << std::endl;
    std::cout << "|" << str4 << "|" << std::endl;
    std::cout << "|" << str5 << "|" << std::endl;
  }

  {
    std::string str1 = "1";
    std::string str2 = "22";
    std::string str3 = "333";
    std::string str4 = "4444";
    std::string str5 = "55555";
    string_support::align(string_support::alignment::CENTER, str1, str2, str3, str4, str5);

    std::cout << "|" << str1 << "|" << std::endl;
    std::cout << "|" << str2 << "|" << std::endl;
    std::cout << "|" << str3 << "|" << std::endl;
    std::cout << "|" << str4 << "|" << std::endl;
    std::cout << "|" << str5 << "|" << std::endl;
  }

  {
    std::string str1 = "1";
    std::string str2 = "22";
    std::string str3 = "333";
    std::string str4 = "4444";
    std::string str5 = "55555";
    string_support::align(string_support::alignment::RIGHT, str1, str2, str3, str4, str5);

    std::cout << "|" << str1 << "|" << std::endl;
    std::cout << "|" << str2 << "|" << std::endl;
    std::cout << "|" << str3 << "|" << std::endl;
    std::cout << "|" << str4 << "|" << std::endl;
    std::cout << "|" << str5 << "|" << std::endl;
  }

  return true;
}
