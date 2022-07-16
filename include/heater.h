#pragma once
#include "project.h"

void init_heater()
{
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_HEATER_LED, OUTPUT);
}

void set_heater(int state)
{
  assert(state == ON || state == OFF);

  digitalWrite(PIN_HEATER, state);
  digitalWrite(PIN_HEATER_LED, state);
}