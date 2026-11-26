// Minimal unit test framework for the native (host) firmware harness.
//
// Firmware code is C++98 (avr-gcc 4.3.5), so tests are too.
#ifndef NATIVE_HARNESS_TEST_H_
#define NATIVE_HARNESS_TEST_H_

#include <stdio.h>

namespace native_test {

typedef void (*TestFn)();

struct TestCase {
  const char* name;
  TestFn fn;
  TestCase* next;
};

void Register(TestCase* test);
void Fail(const char* file, int line, const char* expression);
void FailEq(const char* file, int line, const char* a, const char* b,
            long va, long vb);
void FailMsg(const char* file, int line, const char* message);

struct Registrar {
  Registrar(TestCase* test) { Register(test); }
};

}  // namespace native_test

#define TEST(name) \
  static void test_##name(); \
  static native_test::TestCase test_case_##name = { #name, test_##name, 0 }; \
  static native_test::Registrar test_registrar_##name(&test_case_##name); \
  static void test_##name()

#define CHECK(c) do { \
  if (!(c)) { native_test::Fail(__FILE__, __LINE__, #c); return; } \
} while (0)

// Like CHECK but keeps going (use inside loops to report the first failure
// without aborting the whole test early is not needed; this one stops too).
#define CHECK_EQ(a, b) do { \
  long check_a_ = static_cast<long>(a); \
  long check_b_ = static_cast<long>(b); \
  if (check_a_ != check_b_) { \
    native_test::FailEq(__FILE__, __LINE__, #a, #b, check_a_, check_b_); \
    return; \
  } \
} while (0)

#define CHECK_NEAR(a, b, tolerance) do { \
  long check_a_ = static_cast<long>(a); \
  long check_b_ = static_cast<long>(b); \
  long check_d_ = check_a_ > check_b_ ? check_a_ - check_b_ : check_b_ - check_a_; \
  if (check_d_ > static_cast<long>(tolerance)) { \
    native_test::FailEq(__FILE__, __LINE__, #a, #b, check_a_, check_b_); \
    return; \
  } \
} while (0)

#define CHECK_MSG(c, ...) do { \
  if (!(c)) { \
    char check_buffer_[256]; \
    snprintf(check_buffer_, sizeof(check_buffer_), __VA_ARGS__); \
    native_test::FailMsg(__FILE__, __LINE__, check_buffer_); \
    return; \
  } \
} while (0)

#endif  // NATIVE_HARNESS_TEST_H_
