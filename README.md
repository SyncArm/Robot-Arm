# Robot_Arm

### 컨트롤러
__MCU__: Arduino Leonardo

__서보 드라이버__: PCA9685 16채널 PWM 서보 드라이버 모듈

__통신 프로토콜__: 시리얼 통신 (UART), 115200 baud rate

- 라즈베리파이로부터 받은 좌표 데이터를 파싱후 서보 각도로 매핑
<br /><br />

### 모터
__Servo__: RDS3115MG

-	Servo 1: 로봇 팔의 전후 움직임 (손의 Y좌표에 매핑)

-	Servo 2: 로봇 팔의 높이 조절 (Depth에 매핑)

-	Servo 3: 로봇 팔의 좌우 움직임 (손의 X좌표에 매핑)
<br /><br /><br /> 

![image](https://github.com/user-attachments/assets/b2b20710-4701-4749-b648-39c56a6880a3)
