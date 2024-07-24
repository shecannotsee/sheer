#include <she_test.h>

#include "sheer.h"

namespace {
struct test_struct {
  std::chrono::time_point<std::chrono::system_clock> timestamp;  // 时间戳
  test_struct(std::chrono::time_point<std::chrono::system_clock> ts) : timestamp(ts) {
  }
};

}  // namespace

SHE_TEST(timed_cache_queue_test, main) {
  sheer::timed_cache_queue<test_struct> cache(10);

  // 模拟添加几个元素
  cache.push(test_struct(std::chrono::system_clock::now()));  // 当前时间戳
  std::this_thread::sleep_for(std::chrono::seconds(5));       // 等待5秒
  cache.push(test_struct(std::chrono::system_clock::now()));  // 当前时间戳

  // 测试获取元素
  auto timestamp = std::chrono::system_clock::now();
  test_struct elem(timestamp);
  if (cache.pop(elem)) {
    std::cout << "Popped element timestamp: " << std::chrono::system_clock::to_time_t(elem.timestamp) << std::endl;
  } else {
    std::cout << "Queue is empty." << std::endl;
  }

  std::cout << "Before cleanup, cache size: " << cache.size() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(10));  // 等待10秒，触发自动清理
  std::cout << "After automatic cleanup, cache size: " << cache.size() << std::endl;

  // 测试并发添加和自动清理
  std::thread add_thread([&cache]() {
    for (int i = 0; i < 5; ++i) {
      cache.push(test_struct(std::chrono::system_clock::now()));  // 当前时间戳
      std::this_thread::sleep_for(std::chrono::seconds(2));       // 等待2秒
    }
  });

  std::thread clean_thread([&cache]() {
    std::this_thread::sleep_for(std::chrono::seconds(20));  // 等待20秒，触发自动清理
    std::cout << "Concurrent cleanup, cache size: " << cache.size() << std::endl;
  });

  add_thread.join();
  clean_thread.join();

  return true;
}
