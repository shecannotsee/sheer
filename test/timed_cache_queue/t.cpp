#include <she_test.h>

#include "timed_cache_queue.h"

namespace {
struct test_struct {
  std::chrono::time_point<std::chrono::system_clock> timestamp;  // 时间戳
  test_struct(std::chrono::time_point<std::chrono::system_clock> ts) : timestamp(ts) {
  }
};
}  // namespace

SHE_TEST(timed_cache_queue_test, main) {
  timed_cache_queue<test_struct> cache(10);

  // 模拟添加一些元素
  cache.push(test_struct(std::chrono::system_clock::now()));  // 当前时间戳
  std::this_thread::sleep_for(std::chrono::seconds(5));       // 等待5秒
  cache.push(test_struct(std::chrono::system_clock::now()));  // 当前时间戳

  std::cout << "Before cleanup, cache size: " << cache.size() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(15));  // 等待15秒，触发自动清理
  std::cout << "After automatic cleanup, cache size: " << cache.size() << std::endl;

  return true;
}
