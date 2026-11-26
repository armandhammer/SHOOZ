// Test runner: ./native_tests [substring-filter]
#include "test.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <avr/io.h>

volatile uint8_t native_sreg = 0x80;
volatile uint8_t native_sfr[0x200];
uint8_t native_eeprom[E2END + 1];

namespace native_test {

static TestCase* head = 0;
static TestCase* tail = 0;
static int failures_in_test = 0;

void Register(TestCase* test) {
  // Keep registration order (file order) for readable output.
  if (!head) {
    head = tail = test;
  } else {
    tail->next = test;
    tail = test;
  }
}

void Fail(const char* file, int line, const char* expression) {
  fprintf(stderr, "    %s:%d: CHECK(%s) failed\n", file, line, expression);
  ++failures_in_test;
}

void FailEq(const char* file, int line, const char* a, const char* b,
            long va, long vb) {
  fprintf(stderr, "    %s:%d: %s == %s failed (%ld vs %ld)\n",
          file, line, a, b, va, vb);
  ++failures_in_test;
}

void FailMsg(const char* file, int line, const char* message) {
  fprintf(stderr, "    %s:%d: %s\n", file, line, message);
  ++failures_in_test;
}

}  // namespace native_test

int main(int argc, char** argv) {
  using namespace native_test;
  const char* filter = argc > 1 ? argv[1] : 0;
  int run = 0;
  int failed = 0;
  for (TestCase* t = head; t; t = t->next) {
    if (filter && !strstr(t->name, filter)) {
      continue;
    }
    failures_in_test = 0;
    t->fn();
    ++run;
    if (failures_in_test) {
      ++failed;
      printf("FAIL %s\n", t->name);
    } else {
      printf("ok   %s\n", t->name);
    }
  }
  printf("\n%d tests, %d passed, %d failed\n", run, run - failed, failed);
  return failed ? 1 : 0;
}
