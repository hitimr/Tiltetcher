#pragma once
#include "GPIO.h"
#include <RingBuf.h>
#include <math.h>

// Settings
#define NUM_MEASUREMENTS (8)
#define TEMPERATURE_INVALID (double) -999.0

// Hardware
// Sensor data sheet:
// https://media.digikey.com/pdf/Data%20Sheets/Infineon%20PDFs/KT,KTY.pdf
#define ALPHA (0.00788)   // from data sheet
#define BETA (0.00001937) // from data sheet
#define R25 (1970.0)      // Sensor impedance at 25°C
#define V_SOURCE 5.0      // Source Voltage (5V from Arduino)
#define R1 3000.0         // Resistor for Temperature sensor
#define MIN_PLAUSIBLE_TEMP (1.0)
#define MAX_PLAUSIBLE_TEMP (100.0)

class ThermalSensor
{
public:
  

  // Read the temperature, convert it to Celsius and store it in the buffer
  // This function should be called periodically by an interrupt
  void update()
  {
    // perform a measurement and convert to Celsius
    double V_sens = (double)analogRead(PIN_THERMAL_SENSOR) * V_SOURCE / (double)1023;
    double R_T = R1 * (V_SOURCE / V_sens - 1);
    double k_T = R_T / R25;
    double T = 25 + (sqrt(ALPHA * ALPHA - 4. * BETA + 4. * BETA * k_T) - ALPHA) / (2. * BETA);

    // store the temperature in the buffer
    double tmp;
    if (buffer.isFull())
    {
      buffer.pop(tmp);
    }
    buffer.lockedPush(T);

    m_is_valid = check_validity();
    if(is_valid())
    {
      m_temperature = m_calculate_temperature();
    }
    else
    {
      m_temperature = TEMPERATURE_INVALID;
    }
  }

  bool is_valid() { return m_is_valid; }
  double get_temperature() { return m_temperature; }

private:
  RingBuf<double, NUM_MEASUREMENTS> buffer;

  bool m_is_valid = false;
  double m_temperature = TEMPERATURE_INVALID;
  
  bool check_validity()
  {
    if (!buffer.isFull())
      return false;

    for (int i = 0; i < NUM_MEASUREMENTS; i++)
    {
      if ((buffer[i] < MIN_PLAUSIBLE_TEMP) || (buffer[i] > MAX_PLAUSIBLE_TEMP))
        return false;
    }

    return true;
  }
  
  double m_calculate_temperature()
  {
    // calculate average over the last measurements
    double sum = 0.0;
    for (int i = 0; i < NUM_MEASUREMENTS; i++)
    {
      sum += buffer[i];
    }
    return sum / NUM_MEASUREMENTS;
  }
};

ThermalSensor thermal_sensor;
