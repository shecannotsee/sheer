#ifndef SHEER_DESTRUCTOR_H
#define SHEER_DESTRUCTOR_H

#include <algorithm>
#include <type_traits>
#include <utility>

namespace sheer {

// https://github.com/microsoft/GSL/blob/b39e7e4b0987859f5b19ff7686b149c916588658/include/gsl/util#L70
// version: 4.0.0
template <class F>
class final_action {
 public:
  static_assert(!std::is_reference<F>::value && !std::is_const<F>::value && !std::is_volatile<F>::value,
                "Final_action should store its callable by value");

  explicit final_action(F f) noexcept : f_(std::move(f)) {
  }

  final_action(final_action&& other) noexcept : f_(std::move(other.f_)), invoke_(std::exchange(other.invoke_, false)) {
  }

  final_action(const final_action&)            = delete;
  final_action& operator=(const final_action&) = delete;
  final_action& operator=(final_action&&)      = delete;

  ~final_action() noexcept {
    if (invoke_) f_();
  }

 private:
  F f_;
  bool invoke_{true};
};

// finally() - convenience function to generate a final_action
template <class F>
[[nodiscard]] final_action<typename std::remove_cv<typename std::remove_reference<F>::type>::type> finally(
    F&& f) noexcept {
  return final_action<typename std::remove_cv<typename std::remove_reference<F>::type>::type>(std::forward<F>(f));
}
}  // namespace sheer

#endif  // SHEER_DESTRUCTOR_H
