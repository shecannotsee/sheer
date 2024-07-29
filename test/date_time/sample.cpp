#include <she_test.h>
#include <sheer.h>

SHE_TEST(test_date_time, sample) {
  using record = test_support::date_time;

  const auto now = record::get_time_point();

  std::cout << "--------date: " << record::format_date_string(now) << std::endl;
  std::cout << "date with ms: " << record::format_date_string_with_milliseconds(now) << std::endl;
  std::cout << "---timestamp: " << record::to_duration_number<std::chrono::seconds>(now) << std::endl;
  std::cout << "----------ms: " << record::to_duration_number<std::chrono::milliseconds>(now) << std::endl;
  std::cout << "----------us: " << record::to_duration_number<std::chrono::microseconds>(now) << std::endl;

  return true;
}
