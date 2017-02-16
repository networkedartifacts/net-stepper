#include <Arduino.h>
#include <MQTTClient.h>

#ifndef NETSTEPPER_STEPPER_H
#define NETSTEPPER_STEPPER_H

#define STEPPER_EN 5
#define STEPPER_MS1 4
#define STEPPER_MS2 3
#define STEPPER_MS3 2
#define STEPPER_STEP 1
#define STEPPER_DIR 0
#define STEPPER_POS 0

enum DriveMode { Idle, Absolute, Continuous };

enum Direction { CW, CCW };

class Stepper {
private:
  boolean powered = false;
  DriveMode mode = Idle;
  int resolution = 1;
  Direction direction = CW;
  int speed = 5000;
  int threshold = 0;
  double target = 0.0;
  double position = 0.0;

  unsigned long lastStep = 0;
  boolean stepping = false;
  int lastReading = 0;
  DriveMode lastStatus = Idle;
  MQTTClient *client;

  void writePower(boolean on);
  void writeResolution(int resolution);
  void writeResolutionBits(uint8_t, uint8_t, uint8_t);
  void writeDirection(Direction direction);

public:
  void setup(MQTTClient *);
  void handle(String topic, String payload);
  void loop();
};

#endif // NETSTEPPER_STEPPER_H
