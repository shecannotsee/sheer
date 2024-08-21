#include <she_test.h>
#include <sheer.h>

SHE_TEST(ring_buffer, sample) {
  test_support::ring_buffer<int> buffer(3);

  buffer.push_back(1);
  buffer.push_back(2);
  buffer.push_back(99);
  {
    auto temp = buffer.get();
    for (const auto& e : temp) {
      std::cout << e << ",";  // 1,2,99
    }
    std::cout << "\n";
  }

  buffer.back() = 3;
  {
    auto temp = buffer.get();
    for (const auto& e : temp) {
      std::cout << e << ",";  // 1,2,3
    }
    std::cout << "\n";
  }

  buffer.push_back(4);
  buffer.push_back(5);
  buffer.push_back(6);
  {
    auto temp = buffer.get();
    for (const auto& e : temp) {
      std::cout << e << ",";  // 4,5,6
    }
    std::cout << "\n";
  }

  buffer.push_back(7);
  {
    auto temp = buffer.get();
    for (const auto& e : temp) {
      std::cout << e << ",";  // 5,6，7
    }
    std::cout << "\n";
  }

  return true;
}
