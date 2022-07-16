#include "project.h"

void setup()
{
  // Serial Comms
  Serial.begin(SERIAL_BAUD_RATE);

  // Motor
  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);
  pinMode(PIN_MOTOR_3, OUTPUT);
  pinMode(PIN_MOTOR_4, OUTPUT);

  init_heater();
}

void loop()
{
  set_heater(ON);
  // put your main code here, to run repeatedly:
}