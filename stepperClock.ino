#include "motor.h"

Motor motor1(13, 23, 24, 25);

void setup() {
  motor1.init();
  motor1.setFrequency(1);
  motor1.enable();
}

void tick(long ms) {
  unsigned long startUS = micros();
  while((micros() - startUS) < (ms*1000)) {
    motor1.tick();
  }
}

void loop() {
  motor1.setFrequency(5);
  tick(5000);
  motor1.setFrequency(10);
  tick(1000);
}
