#include <she_test.h>
#include <sheer.h>

#include <thread>

SHE_TEST(test_timer, sample) {
  test_support::timer record;

  record.start();
  std::this_thread::sleep_for(std::chrono::seconds(2));
  record.end();

  std::cout << "     seconds: " << record.get_elapsed<std::chrono::seconds>() << " passed." << std::endl;
  std::cout << "milliseconds: " << record.get_elapsed<std::chrono::milliseconds>() << " passed." << std::endl;
  std::cout << "microseconds: " << record.get_elapsed<std::chrono::microseconds>() << " passed." << std::endl;

  return true;
}
