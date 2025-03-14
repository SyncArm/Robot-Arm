#include "HCPCA9685.h"

#define I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);

const int right_X = A2;
const int right_Y = A3;

unsigned long previousMillis = 0;
const long interval = 50; // 더 빠르게 업데이트 (부드럽게 움직이도록)

int previousServoX = 135;  // 초기값을 현재 서보 위치와 동일하게 설정
int previousServoY = 240;

void setup() {
    Serial.begin(9600);
    HCPCA9685.Init(SERVO_MODE);
    HCPCA9685.Sleep(false);

    HCPCA9685.Servo(0, 0);   
    HCPCA9685.Servo(1, 240);
    HCPCA9685.Servo(2, 240);
    HCPCA9685.Servo(3, 135);
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        
        int x1 = analogRead(right_X);
        int y1 = analogRead(right_Y);
        
        // 1023 값을 360도 범위로 변환 (map() 없이)
        int targetServoX = x1 / 4;  // 0~1023 → 0~255
        int targetServoY = y1 / 4+50;

        // 이전 값과 새 값 사이에서 부드럽게 보간 (가중치 0.9)
        previousServoX = 0.8 * previousServoX + 0.2 * targetServoX;
        previousServoY = 0.8 * previousServoY + 0.2 * targetServoY;

        // 서보 모터 회전
        HCPCA9685.Servo(3, previousServoX);
        HCPCA9685.Servo(2, previousServoY);

        // 시리얼 모니터 출력
        Serial.print("RX: "); Serial.print(x1);
        Serial.print(" (Target ServoX: "); Serial.print(targetServoX);
        Serial.print(" -> Smooth ServoX: "); Serial.print(previousServoX);
        Serial.print(") RY: "); Serial.print(y1);
        Serial.print(" (Target ServoY: "); Serial.print(targetServoY);
        Serial.print(" -> Smooth ServoY: "); Serial.print(previousServoY);
        Serial.println(")");
    }
}

