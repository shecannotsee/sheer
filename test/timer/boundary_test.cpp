#include <she_test.h>
#include <sheer.h>

#include <thread>

SHE_TEST(test_timer, boundary_test) {
  {
    test_support::timer record;
    record.end();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    record.start();
    std::cout << "     seconds: " << record.get_elapsed<std::chrono::seconds>()      << " passed." << std::endl;
    std::cout << "milliseconds: " << record.get_elapsed<std::chrono::milliseconds>() << " passed." << std::endl;
    std::cout << "microseconds: " << record.get_elapsed<std::chrono::microseconds>() << " passed." << std::endl;
  }

  {
    test_support::timer record_without_init;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    try {
      std::cout << "     seconds: " << record_without_init.get_elapsed<std::chrono::seconds>()      << " passed.\n";
      std::cout << "milliseconds: " << record_without_init.get_elapsed<std::chrono::milliseconds>() << " passed.\n";
      std::cout << "microseconds: " << record_without_init.get_elapsed<std::chrono::microseconds>() << " passed.\n";
    } catch (const std::runtime_error& ex) {
      std::cout << ex.what() << std::endl;
    }
  }

  {
    test_support::timer record_without_start;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    record_without_start.end();
    try {
      std::cout << "     seconds: " << record_without_start.get_elapsed<std::chrono::seconds>()      << " passed.\n";
      std::cout << "milliseconds: " << record_without_start.get_elapsed<std::chrono::milliseconds>() << " passed.\n";
      std::cout << "microseconds: " << record_without_start.get_elapsed<std::chrono::microseconds>() << " passed.\n";
    } catch (const std::runtime_error& ex) {
      std::cout << ex.what() << std::endl;
    }
  }

  {
    test_support::timer record_without_end;
    record_without_end.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    try {
      std::cout << "     seconds: " << record_without_end.get_elapsed<std::chrono::seconds>()      << " passed.\n";
      std::cout << "milliseconds: " << record_without_end.get_elapsed<std::chrono::milliseconds>() << " passed.\n";
      std::cout << "microseconds: " << record_without_end.get_elapsed<std::chrono::microseconds>() << " passed.\n";
    } catch (const std::runtime_error& ex) {
      std::cout << ex.what() << std::endl;
    }
  }

  return true;
}
