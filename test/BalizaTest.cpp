#include <Arduino.h>
#include "unity.h"
#include "baliza.h"

void test1(void) {
    TEST_ASSERT_EQUAL(32, 32);
}

// setup connects serial, runs test cases (upcoming)
void setup() {
  delay(1000);

  UNITY_BEGIN();
  RUN_TEST(test1);
  UNITY_END();
}


void loop() {
  // nothing to be done here.
}
