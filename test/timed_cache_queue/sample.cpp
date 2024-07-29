#include <she_test.h>
#include <sheer.h>

namespace {
struct test_struct {
  std::chrono::time_point<std::chrono::system_clock> timestamp;  // timestamp
  test_struct(std::chrono::time_point<std::chrono::system_clock> ts) : timestamp(ts) {
  }
};

}  // namespace

SHE_TEST(timed_cache_queue, sample) {
  test_support::timed_cache_queue<test_struct> cache(10);

  // 模拟添加几个元素
  cache.push(test_struct(std::chrono::system_clock::now()));  // Current timestamp
  std::this_thread::sleep_for(std::chrono::seconds(5));       // Wait 5 seconds
  cache.push(test_struct(std::chrono::system_clock::now()));  // Current timestamp

  // 测试获取元素
  auto timestamp = std::chrono::system_clock::now();
  test_struct elem(timestamp);
  if (cache.pop(elem)) {
    std::cout << "Popped element timestamp: " << std::chrono::system_clock::to_time_t(elem.timestamp) << std::endl;
  } else {
    std::cout << "Queue is empty." << std::endl;
  }

  std::cout << "Before cleanup, cache size: " << cache.size() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(10));  // Wait 10 seconds to trigger automatic cleanup
  std::cout << "After automatic cleanup, cache size: " << cache.size() << std::endl;

  // 测试并发添加和自动清理
  std::thread add_thread([&cache]() {
    for (int i = 0; i < 5; ++i) {
      cache.push(test_struct(std::chrono::system_clock::now()));  // Current timestamp
      std::this_thread::sleep_for(std::chrono::seconds(2));       // Wait 2 seconds
    }
  });

  std::thread clean_thread([&cache]() {
    std::this_thread::sleep_for(std::chrono::seconds(20));  // Wait 20 seconds to trigger automatic cleanup
    std::cout << "Concurrent cleanup, cache size: " << cache.size() << std::endl;
  });

  add_thread.join();
  clean_thread.join();

  // build error message like this:
  // /sheer/src/timed_cache_queue.h:30:17: error: static assertion failed due to requirement 'has_timestamp_member<int,
  // void>::value': T must have a 'timestamp' member of type std::chrono::time_point
  //    30 |   static_assert(has_timestamp_member<T>::value, "T must have a 'timestamp' member of type
  //    std::chrono::time_point");
  // test_support::timed_cache_queue<int> error(10);
  return true;
}
