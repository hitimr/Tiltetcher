#pragma once

// System constants
#define STEPPER_MOTOR_ENABLED false

#define WARMUP_TIME_MS 1000L

// Misc
#define PRECISION 4

#define ON 1
#define OFF 0
#define SUCCESS 0

// Logging
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_ERROR 3
#define LOG_LEVEL_FATAL 4
#define LOG_LEVEL_NONE 5
#define LOG_LEVEL LOG_LEVEL_DEBUG

#define LOG_LEVEL_STRING(level)                                                                    \
  (level == LOG_LEVEL_DEBUG   ? "DEBUG"                                                            \
   : level == LOG_LEVEL_INFO  ? "INFO"                                                             \
   : level == LOG_LEVEL_WARN  ? "WARN"                                                             \
   : level == LOG_LEVEL_ERROR ? "ERROR"                                                            \
   : level == LOG_LEVEL_FATAL ? "FATAL"                                                            \
   : level == LOG_LEVEL_NONE  ? "NONE"                                                             \
                              : "UNKNOWN")

#define LOG_PRINT(level, ...)                                                                      \
  if (LOG_LEVEL <= level)                                                                          \
  {                                                                                                \
    Serial.print("[");                                                                             \
    Serial.print(LOG_LEVEL_STRING(level));                                                         \
    Serial.print("] ");                                                                            \
    Serial.print(__VA_ARGS__);                                                                     \
    Serial.print("\n");                                                                            \
  }

#define SERIAL_BAUD_RATE 115200