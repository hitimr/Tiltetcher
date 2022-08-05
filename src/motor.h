#pragma once
#include "GPIO.h"
#include "project.h"
#include <Arduino.h>

void init_motor()
{
  // Motor
  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);
  pinMode(PIN_MOTOR_3, OUTPUT);
  pinMode(PIN_MOTOR_4, OUTPUT);
}

void setMotor(byte in1, byte in2, byte in3, byte in4)
{
  digitalWrite(PIN_MOTOR_1, in1);
  digitalWrite(PIN_MOTOR_2, in2);
  digitalWrite(PIN_MOTOR_3, in3);
  digitalWrite(PIN_MOTOR_4, in4);
}

void motor_step()
{
  static uint64_t state = 0;
  switch (state % 8)
  {
  case 0:
    setMotor(LOW, LOW, LOW, HIGH);
    break;
  case 1:
    setMotor(LOW, LOW, HIGH, HIGH);
    break;
  case 2:
    setMotor(LOW, LOW, HIGH, LOW);
    break;
  case 3:
    setMotor(LOW, HIGH, HIGH, LOW);
    break;
  case 4:
    setMotor(LOW, HIGH, LOW, LOW);
    break;
  case 5:
    setMotor(HIGH, HIGH, LOW, LOW);
    break;
  case 6:
    setMotor(HIGH, LOW, LOW, LOW);
    break;
  case 7:
    setMotor(HIGH, LOW, LOW, HIGH);
    break;
  default:
    setMotor(LOW, LOW, LOW, LOW);
    break;
  }
  state++;
}
