#include "HCPCA9685.h"

#define I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);

unsigned long lastReceivedTime = 0;
float currentPos[4] = {0, 240, 240, 135};
float targetPos[4] = {0, 240, 240, 135};
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 100;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);

  HCPCA9685.Servo(1, 240);
  HCPCA9685.Servo(2, 240);
  HCPCA9685.Servo(3, 150);
}

void loop() {
  if (Serial1.available() > 0) {
    String receivedData = Serial1.readStringUntil('\n');
    Serial.println(receivedData);

    int avg_x, avg_y, depth;
    int result = sscanf(receivedData.c_str(), "%d,%d,%d", &avg_x, &avg_y, &depth);

    targetPos[1] = constrain(map(avg_y, 0, 800, 0, 240), 0, 240);
    targetPos[2] = constrain(map(depth, 200, 400, 0, 250), 30, 250);
    targetPos[3] = constrain(map(avg_x, 200, 850, 0, 300), 0, 300);
  }

  if (millis() - lastUpdateTime >= updateInterval) {
    lastUpdateTime = millis();
    for (int i = 1; i < 4; i++) {
      if (currentPos[i] != targetPos[i]) {
        float step = (targetPos[i] - currentPos[i]) * 0.1;
        currentPos[i] += step;
        HCPCA9685.Servo(i, (int)currentPos[i]);
      }
    }
  }
}
