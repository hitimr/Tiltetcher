#include "math.h"
#include "assert.h"

#define V_SOURCE 5.0 // Source Voltage (5V from Arduino)
#define R1 3000.0    // Resistor for Temperature sensor

// Sensor Datasheet:
// https://media.digikey.com/pdf/Data%20Sheets/Infineon%20PDFs/KT,KTY.pdf
#define ALPHA 0.00788 // from Datasheet
#define BETA  0.00001937 // from datasheet
#define R25 ((double) 1970) // Sensor impendance at 25°C

// Stepper Motor Pins
#define PIN_IN1 10  // blue
#define PIN_IN2 11  // pink
#define PIN_IN3 12 // yellow
#define PIN_IN4 13 // orange

// Sensor
#define PIN_SENS A1 

// Heater
#define PIN_HEATER 3
#define PIN_HEATER_LED 4
#define TEMP_CUTOFF_HIGH 45
#define TEMP_CUTOFF_LOW 42

// Misc
#define PRECISION 4

void setup() 
{
  // Serial Comms
  Serial.begin(9600);

  // Motor
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);

  // Heater
  pinMode(PIN_HEATER, OUTPUT);
  pinMode(PIN_HEATER_LED, OUTPUT);

}

double get_temperature()
{
  double V_sens = (double) analogRead(PIN_SENS) * V_SOURCE / (double) 1023;
  double R_T = R1 * (V_SOURCE / V_sens - 1);
  double k_T = R_T / R25;
  double T = 25 + (sqrt(ALPHA*ALPHA - 4.*BETA + 4.*BETA * k_T) - ALPHA) / (2.* BETA);
  return T; 
}

void setMotor(byte in1, byte in2, byte in3, byte in4, unsigned int motorSpeed)
{
    digitalWrite(PIN_IN1, in1);
    digitalWrite(PIN_IN2, in2);
    digitalWrite(PIN_IN3, in3);
    digitalWrite(PIN_IN4, in4);
    delayMicroseconds(motorSpeed);
}

void rotateRight(unsigned int motorSpeed)
{
    setMotor(LOW, LOW, LOW, HIGH, motorSpeed);
    setMotor(LOW, LOW, HIGH, HIGH, motorSpeed);
    setMotor(LOW, LOW, HIGH, LOW, motorSpeed);
    setMotor(LOW, HIGH, HIGH, LOW, motorSpeed);
    setMotor(LOW, HIGH, LOW, LOW, motorSpeed);
    setMotor(HIGH, HIGH, LOW, LOW, motorSpeed);
    setMotor(HIGH, LOW, LOW, LOW, motorSpeed);
    setMotor(HIGH, LOW, LOW, HIGH, motorSpeed);
}

void rotateLeft(unsigned int motorSpeed)
{
    setMotor(HIGH, LOW, LOW, LOW, motorSpeed);
    setMotor(HIGH, HIGH, LOW, LOW, motorSpeed);
    setMotor(LOW, HIGH, LOW, LOW, motorSpeed);
    setMotor(LOW, HIGH, HIGH, LOW, motorSpeed);
    setMotor(LOW, LOW, HIGH, LOW, motorSpeed);
    setMotor(LOW, LOW, HIGH, HIGH, motorSpeed);
    setMotor(LOW, LOW, LOW, HIGH, motorSpeed);
    setMotor(HIGH, LOW, LOW, HIGH, motorSpeed);
}

void stopMotor()
{
    setMotor(LOW, LOW, LOW, LOW, 0);
}

void set_heater(int status)
{
  assert((status == HIGH) || (status == LOW));
  digitalWrite(PIN_HEATER, status);
  //digitalWrite(PIN_HEATER_LED, status);
}

void loop() 
{
  double T = get_temperature();
  if(T < TEMP_CUTOFF_LOW)
  {
    set_heater(HIGH);
  }
  if(T > TEMP_CUTOFF_HIGH)
  {
    set_heater(LOW);
  }
  
  Serial.println(T, PRECISION);          // debug value
  rotateRight(1000);  
}
