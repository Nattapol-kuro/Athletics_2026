#include <light_CD74HC4067.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_BNO08x.h>
#define BNO08X_RESET -1
#define NUMSENSOR 16
#define KNOB_PIN A0
#define BUZZER_PIN 4
#define NUMBER_KNOB 4
CD74HC4067 my_mux(59, 58, 57, 56);
CD74HC4067 my_mub(67, 66, 65, 64);
Adafruit_BNO08x bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

const int signal_pin = A1;
const int signal_pinB = A9;
int sensorValues[NUMSENSOR];
int sensorMax[16] = { 470, 679, 657, 694, 713, 658, 562, 713, 607, 537, 589, 700, 615, 649, 427, 467 };
int sensorMin[16] = { 44, 45, 46, 46, 47, 46, 42, 47, 42, 43, 44, 47, 44, 45, 42, 43 };
int senbackMax[16] = { 667, 630, 590, 606, 641, 595, 546, 547, 638, 577, 541, 578, 588, 652, 585, 677 };
int senbackMin[16] = { 37, 36, 36, 36, 36, 35, 37, 36, 37, 35, 35, 36, 36, 36, 35, 34 };
int sl, sr;
#define sl (980 + 310) / 2
#define sr (980 + 370) / 2

unsigned int Position = 0;
int leftPower, rightPower;
int error, last_error;
int PIDValue;

const int YAW_DIR = -1;
const float KP_STRAIGHT = 3.0;
const float KP_TURN = 4.335;
const int TURN_MIN = 20;
const int TURN_MAX = 150;
const float TOLERANCE = 0.4;
float lastYaw = 0;
float startYaw = 0;


#define PwmA 2
#define Ain1 22
#define Ain2 23
#define PwmC 5
#define Cin1 27
#define Cin2 26

Servo myservo1;
Servo myservo2;
Servo myservo3;

void setReports(void) {
  if (!bno08x.enableReport(SH2_GAME_ROTATION_VECTOR)) {
    Serial.println("Error: Could not enable game vector");
  }
}

float getYaw() {
  if (bno08x.wasReset()) {
    setReports();
  }
  if (bno08x.getSensorEvent(&sensorValue)) {
    if (sensorValue.sensorId == SH2_GAME_ROTATION_VECTOR) {
      float qr = sensorValue.un.gameRotationVector.real;
      float qi = sensorValue.un.gameRotationVector.i;
      float qj = sensorValue.un.gameRotationVector.j;
      float qk = sensorValue.un.gameRotationVector.k;

      float siny_cosp = 2.0 * (qr * qk + qi * qj);
      float cosy_cosp = 1.0 - 2.0 * (qj * qj + qk * qk);
      float yaw = atan2(siny_cosp, cosy_cosp) * 180.0 / PI;

      if (yaw < 0) yaw += 360.0;
      lastYaw = yaw;
      return yaw;
    }
  }
  return -1.0;
}

int menu() {
  static int lastX = -1;

  int value = analogRead(KNOB_PIN);

  int x = map(value, 0, 1023, 1, NUMBER_KNOB + 1);
  x = constrain(x, 1, NUMBER_KNOB);

  if (x != lastX) {
    tone(BUZZER_PIN, 600 + (x - 1) * 500, 150);
    lastX = x;

    // Serial.print("VALUE = ");
    // Serial.print(value);
    // Serial.print(" | MODE = ");
    // Serial.println(x);
  }
  return x;
}

void MENU() {
}


void setup() {
  Serial.begin(9600);
  pinMode(signal_pin, INPUT);
  pinMode(PwmA, OUTPUT);
  pinMode(Ain1, OUTPUT);
  pinMode(Ain2, OUTPUT);
  pinMode(PwmC, OUTPUT);
  pinMode(Cin1, OUTPUT);
  pinMode(Cin2, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(30);
  myservo1.write(110);
  myservo2.write(62);
  myservo3.write(130);
  Wire.begin();
  if (!bno08x.begin_I2C()) {
    Serial.println("BNO08x not found");
    while (1) delay(10);
  }
  setReports();
  tone(4, 1200, 100);
  // calibrate(1500);
  // monitorSensor();
  // calibrateB(1500);
  // monitorSensorB();
  // Read();
}

void loop() {
  static int x = 1;
  STOP();
  x = menu();
  delay(20);
  if (digitalRead(7) == HIGH) {
    delay(300);
    RUN();
    while (digitalRead(7) == HIGH) {
      delay(5);
    }
  }
  if (digitalRead(8) == HIGH) {
    delay(30);
    if (digitalRead(8) == HIGH) {
      delay(300);
      switch (x) {
        case 1:
          zone(1);
          break;
        case 2:
          zone(2);
          break;
        case 3:
          zone(3);
          break;
        case 4:
          c();
          break;
      }
      STOP();
    }
  }
}
// void loop() {
//   static int x = 1;

//   STOP();

//   // เลือกโหมดด้วยปุ่ม 8
//   if (digitalRead(8) == HIGH) {
//     delay(30);
//     if (digitalRead(8) == HIGH) {
//       while (digitalRead(8) == HIGH) {
//         STOP();
//         x = menu();
//         delay(20);
//       }
//     }
//   }

//   // กดปุ่ม 7 เพื่อ RUN
//   if (digitalRead(7) == HIGH) {
//     delay(30);
//     if (digitalRead(7) == HIGH) {
//       Serial.println("RUN");
//       RUN();

//       while (digitalRead(7) == HIGH) {
//         delay(5);
//       }
//     }
//   }

//   // กดปุ่ม 8 เพื่อเข้า CASE
//   if (digitalRead(8) == HIGH) {
//     delay(30);
//     if (digitalRead(8) == HIGH) {
//       tone(4, 2000, 200);

//       switch (x) {
//         case 1: while (1) zone(1);
//         case 2: while (1) zone(2);
//         case 3: while (1) zone(3);
//         case 4: while (1) c();
//       }
//     }
//   }
// }

void bt() {
  while (digitalRead(7) == 0) {
    STOP();
  }
  delay(300);
}