#pragma once
#include "GPIO.h"
#include "project.h"
#include "thermal_sensor.h"

#include <assert.h>

#define HEATER_TEMP_CUTOFF_HIGH 45
#define HEATER_TEMP_CUTOFF_LOW 42
#define HEATER_MINIMUM_SWITCH_TIME 1000

#define HEATER_STATE_OFF 0
#define HEATER_STATE_ON 1

class Heater
{
  public:
    Heater() {}
    void update()
    {
      if(!is_ready())
      {
        set_heater(OFF);  // Heater is not ready yet or temperature is too high
        return;
      }

      if(digitalRead(PIN_IN_HTR_SW) == LOW)
      {
        set_heater(OFF);  // Heater switch is off
        return;
      }
     
      if (thermal_sensor.get_temperature() < HEATER_TEMP_CUTOFF_LOW)
      {
        set_heater(ON);  // Switch ON if temperature is too low
      }
    }
    
    void init()
    {

    }

    bool is_ready()
    {
      if(!thermal_sensor.is_valid()) 
      { 
        LOG_PRINT(LOG_LEVEL_DEBUG, "Temperature is invalid");
        return false; // Temperature is invalid
      }

      if(thermal_sensor.get_temperature() > HEATER_TEMP_CUTOFF_HIGH) 
      {
        LOG_PRINT(LOG_LEVEL_DEBUG, "Temperature is too high");
        return false; // Temperature already high enough
      }

      if((last_state_change_time + HEATER_MINIMUM_SWITCH_TIME > millis()) && (m_state == OFF))
      {
        LOG_PRINT(LOG_LEVEL_DEBUG, "Last switch on was too recent");
        return false; // Prevent Relay from switching on too fast
      }

      return true;
    }

  private:
    void set_heater(int new_state)
    {
      if (new_state == m_state) 
        return; // Nothing to do

      if (new_state == ON)
      {
        LOG_PRINT(LOG_LEVEL_DEBUG, "Switching heater ON");
      }
      else
      {
        LOG_PRINT(LOG_LEVEL_DEBUG, "Switching heater OFF");
      }

      digitalWrite(PIN_HEATER, new_state);
      m_state = new_state;
      last_state_change_time = millis();

    }
  private:
    int m_state = OFF;
    uint32_t last_state_change_time = 0;
};


Heater heater;
