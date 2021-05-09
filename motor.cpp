#include "motor.h"
#include <Arduino.h>

Motor::Motor(int pinA, int pinB, int pinC, int pinD) {
  A = pinA; B = pinB; C = pinC; D = pinD;
};

void Motor::setFrequency(float freq) {
  this->usPeriod = (long)(1000000 / freq);
  this->step = 0;
}

void Motor::init() {
  pinMode(this->A, OUTPUT);
  pinMode(this->B, OUTPUT);
  pinMode(this->C, OUTPUT);
  pinMode(this->D, OUTPUT);
  this->resetPort();
  this->state=0;
  this->setFrequency(20);
}

void Motor::resetPort() {
  digitalWrite(this->A, LOW);
  digitalWrite(this->B, LOW);
  digitalWrite(this->C, LOW);
  digitalWrite(this->D, LOW);
}

void Motor::lock() {
  this->disable();
  this->resetPort();
  digitalWrite(this->B, HIGH);
  digitalWrite(this->D, HIGH);
}

void Motor::enable() {
  this->state = 1;
  this->step = 0;
}

void Motor::disable() {
  this->state = 0;
  this->step = 0;
}

void Motor::tick() {
  if(this->state) {
    if((micros() - this->usSinceLastStep) > this->usPeriod) {
      this->usSinceLastStep = micros();
      this->nextStep();
    }
  } else {
    this->usSinceLastStep = micros();
  }
}

void Motor::nextStep() {
  switch(this->step%4) {
    case 0:
      digitalWrite(this->A, LOW);
      digitalWrite(this->B, HIGH);
      break;
    case 1:
      digitalWrite(this->B, LOW);
      digitalWrite(this->C, HIGH);
      break;
    case 2:
      digitalWrite(this->C, LOW);
      digitalWrite(this->D, HIGH);
      break;
    case 3:
      digitalWrite(this->D, LOW);
      digitalWrite(this->A, HIGH);
      break;
  }

  this->step += 1;
}