#include <she_test.h>
#include <sheer.h>

namespace {
const std::string RESET_COLOR   = "[0m";
const std::string RED_COLOR     = "[31m";
const std::string GREEN_COLOR   = "[32m";
const std::string YELLOW_COLOR  = "[33m";
const std::string PURPLE_COLOR  = "[35m";
const std::string BLUE_COLOR    = "[34m";
}

SHE_TEST(destructor, sample) {
  std::cout << YELLOW_COLOR << "[t8_util::run] >>> start" << RESET_COLOR << std::endl;
  test_support::final_action<std::function<void()>> auto_release1(
      []() { std::cout << GREEN_COLOR << "[t8_util::run] >>> done" << RESET_COLOR << "\n\n"; });

  auto auto_release2 = test_support::finally(
      []() { std::cout << GREEN_COLOR << "[t8_util::run] >>> done, from gsl::finally" << RESET_COLOR << "\n"; });

  std::cout << __LINE__ << std::endl;
  std::cout << "t8_util run test, start destructor..." << std::endl;

  return true;
}
