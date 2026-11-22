void MC(int speedL, int speedR) {
  constrain(speedL, -255, 255);
  constrain(speedR, -255, 255);
  if (speedL >= 0) {
    digitalWrite(Ain1, HIGH);
    digitalWrite(Ain2, LOW);
    analogWrite(PwmA, speedL);

  } else {
    digitalWrite(Ain1, LOW);
    digitalWrite(Ain2, HIGH);
    analogWrite(PwmA, speedL * -1);
  }

  if (speedR >= 0) {
    digitalWrite(Cin1, LOW);
    digitalWrite(Cin2, HIGH);
    analogWrite(PwmC, speedR);

  } else {
    digitalWrite(Cin1, HIGH);
    digitalWrite(Cin2, LOW);
    analogWrite(PwmC, speedR * -1);
  }
}

void mct(int L, int R, int time) {
  unsigned long looptime = millis();
  while (millis() - looptime <= time) {
    MC(L, R);
  }
}

void STOP() {
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, HIGH);
  analogWrite(PwmA, 255);
  digitalWrite(Cin1, HIGH);
  digitalWrite(Cin2, HIGH);
  analogWrite(PwmC, 255);
}

void yt(int s) {
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, HIGH);
  analogWrite(PwmA, 255);
  digitalWrite(Cin1, HIGH);
  digitalWrite(Cin2, HIGH);
  analogWrite(PwmC, 255);
  delay(s);
}

void L(int time, char mode) {
  MC(-80, 200);
  delay(time);
  readLine(330, 50);
  while (sensorValues[7] < 500) {
    readLine(330, 50);
    MC(-50, 180);
  }
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void L2(int time, char mode) {
  MC(-200, 200);
  delay(time);
  readLine(330, 50);
  while (sensorValues[5] < 500) {
    readLine(330, 50);
    MC(-150, 150);
  }
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void R(int time, char mode) {
  MC(200, -50);
  delay(time);
  readLine(330, 50);
  while (sensorValues[8] < 500) {
    readLine(330, 50);
    MC(180, -30);
  }
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void R2(int time, char mode) {
  MC(200, -200);
  delay(time);
  readLine(330, 50);
  while (sensorValues[10] < 500) {
    readLine(330, 50);
    MC(150, -150);
  }
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void stdPID(int BaseSpeed, float Kp, float Kd, int crossSpeed = 10) {
  Position = readLine(330, 50);
  int error = Position - 7500;
  PIDValue = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  if (PIDValue > BaseSpeed) PIDValue = BaseSpeed;
  if (PIDValue < -BaseSpeed) PIDValue = -BaseSpeed;
  leftPower = BaseSpeed + PIDValue;
  rightPower = BaseSpeed - PIDValue;
  if (leftPower >= 255) leftPower = 255;
  if (leftPower <= 0) leftPower = -120;
  if (rightPower >= 255) rightPower = 255;
  if (rightPower <= 0) rightPower = -120;
  MC(leftPower, rightPower);
}

void stdPIDSS(int BaseSpeed, float Kp, float Kd, int crossSpeed = 10) {
  Position = readLine(330, 50);
  int error = Position - 7500;
  PIDValue = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  if (PIDValue > BaseSpeed) PIDValue = BaseSpeed;
  if (PIDValue < -BaseSpeed) PIDValue = -BaseSpeed;
  leftPower = BaseSpeed + PIDValue;
  rightPower = BaseSpeed - PIDValue;
  if (leftPower >= 255) leftPower = 255;
  if (leftPower <= 0) leftPower = -200;
  if (rightPower >= 255) rightPower = 255;
  if (rightPower <= 0) rightPower = -200;
  MC(leftPower, rightPower);
}

void stdPIDU(int BaseSpeed, float Kp, float Kd, int crossSpeed = 10) {
  Position = readLine(330, 50);
  int error = Position - 3500;
  PIDValue = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  if (PIDValue > BaseSpeed) PIDValue = BaseSpeed;
  if (PIDValue < -BaseSpeed) PIDValue = -BaseSpeed;
  leftPower = BaseSpeed + PIDValue;
  rightPower = BaseSpeed - PIDValue;
  if (leftPower >= 255) leftPower = 255;
  if (leftPower <= 0) leftPower = -120;
  if (rightPower >= 255) rightPower = 255;
  if (rightPower <= 0) rightPower = -120;
  MC(leftPower, rightPower);
}

void stdPIDC(int BaseSpeed, float Kp, float Kd, int crossSpeed = 10) {
  Position = readLine(330, 50);
  if (sensorValues[3] > 500 || sensorValues[12] > 500) MC(BaseSpeed + crossSpeed, BaseSpeed + crossSpeed);
  else {
    int error = Position - 7500;
    PIDValue = (Kp * error) + (Kd * (error - last_error));
    last_error = error;
    if (PIDValue > BaseSpeed) PIDValue = BaseSpeed;
    if (PIDValue < -BaseSpeed) PIDValue = -BaseSpeed;
    leftPower = BaseSpeed + PIDValue;
    rightPower = BaseSpeed - PIDValue;
    if (leftPower >= 255) leftPower = 255;
    if (leftPower <= 0) leftPower = -120;
    if (rightPower >= 255) rightPower = 255;
    if (rightPower <= 0) rightPower = -120;
    MC(leftPower, rightPower);
  }
}

void FT(int BaseSpeed, float Kp, float Kd, int time, char mode) {
  unsigned long looptime;
  looptime = millis();
  while (millis() - looptime <= time) {
    Position = readLine(330, 50);
    stdPID(BaseSpeed, Kp, Kd);
  }
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void SST(int BaseSpeed, float Kp, float Kd, int time) {
  unsigned long looptime;
  looptime = millis();
  while (millis() - looptime <= time) {
    Position = readLine(330, 50);
    stdPIDSS(BaseSpeed, Kp, Kd);
  }
}

void FTU(int BaseSpeed, float Kp, float Kd, int time, char mode) {
  unsigned long looptime;
  looptime = millis();
  while (millis() - looptime <= time) {
    Position = readLine(330, 50);
    stdPIDU(BaseSpeed, Kp, Kd);
  }
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void FCU(int BaseSpeed, float Kp, float Kd, int time, char mode) {
  Position = readLine(330, 50);
  while (sensorValues[3] < 500 || sensorValues[12] < 500) {
    Position = readLine(330, 50);
    stdPIDU(BaseSpeed, Kp, Kd);
  }
  mct(BaseSpeed, BaseSpeed, time);
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void FC(int BaseSpeed, float Kp, float Kd, int time, char mode) {
  Position = readLine(330, 50);
  while (sensorValues[3] < 500 || sensorValues[12] < 500) {
    Position = readLine(330, 50);
    stdPID(BaseSpeed, Kp, Kd);
  }
  mct(BaseSpeed, BaseSpeed, time);
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void FR(int BaseSpeed, float Kp, float Kd, int time, char mode) {
  Position = readLine(330, 50);
  while (sensorValues[15] < 250) {
    Position = readLine(330, 50);
    stdPID(BaseSpeed, Kp, Kd);
  }
  mct(BaseSpeed, BaseSpeed, time);
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void FL(int BaseSpeed, float Kp, float Kd, int time, char mode) {
  Position = readLine(330, 50);
  while (sensorValues[0] < 500) {
    Position = readLine(330, 50);
    stdPID(BaseSpeed, Kp, Kd);
  }
  mct(BaseSpeed, BaseSpeed, time);
  if (mode == 'k') {
    K();
  } else if (mode == 'd') {
    down();
  } else if (mode == 'u') {
    up();
  } else if (mode == 'r') {
    RO();
  } else if (mode == 'l') {
    LO();
  } else if (mode == 'dk') {
    DK();
  } else if (mode == 'o') {
    O();
  } else if (mode == 'o2') {
    O2();
  } else if (mode == 'n') {
  }
}

void SC(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLine(330, 50);
  while (sensorValues[3] < 500 || sensorValues[12] < 500) {
    Position = readLine(330, 50);
    stdPIDC(BaseSpeed, Kp, Kd);
  }
  Position = readLine(330, 50);
  while (analogRead(60) > sl || analogRead(60) > sr) {
    Position = readLine(330, 50);
    stdPID(100, 0.015, 0.08);
  }
  mct(BaseSpeed, BaseSpeed, time);
}

void SL(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLine(330, 50);
  while (sensorValues[3] < 500) {
    Position = readLine(330, 50);
    stdPIDC(BaseSpeed, Kp, Kd);
  }
  Position = readLine(330, 50);
  while (analogRead(60) > sl) {
    Position = readLine(330, 50);
    stdPID(100, 0.015, 0.08);
  }
  mct(BaseSpeed, BaseSpeed, time);
}

void SR(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLine(330, 50);
  while (sensorValues[12] < 500) {
    Position = readLine(330, 50);
    stdPIDC(BaseSpeed, Kp, Kd);
  }
  Position = readLine(330, 50);
  while (analogRead(60) > sr) {
    Position = readLine(330, 50);
    stdPID(100, 0.015, 0.08);
  }
  mct(BaseSpeed, BaseSpeed, time);
}

void THUNH() {
  FT(130, 0.03, 0.15, 150, 'n');
  FR(130, 0.03, 0.15, 150, 'n');
  L2B(30);
  BL(130, 0.025, 0.1, 150);
  R2(50, 'n');


  // FC(70, 0.03, 0.12, 0, 'k');
  // mct(100, 100, 100);
  // K();
  // mct(-100, -100, 100);
  // // BT(130, 0.03, 0.15, 150);
  // // BR(130, 0.03, 0.15, 150);
  // L2(50, 'n');
  // FL(130, 0.03, 0.15, 150, 'n');
  // R2B(30);
  // BT(130, 0.03, 0.15, 150);
  // BL(130, 0.03, 0.15, 130);
  // L2(50,'n');
  // L2(50,'n');
}

void umb() {
  FT(200, 0.03, 0.12, 200, 'n');
  FL(200, 0.03, 0.12, 0, 'n');
  L(100, 'n');
  FR(200, 0.03, 0.12, 0, 'n');
  R(100, 'r');
  down();
  FTU(200, 0.03, 0.12, 400, 'n');
  FTU(70, 0.005, 0.08, 380, 'k');
  BTU(70, 0.005, 0.08, 200);
  BL(150, 0.03, 0.12, 0);
  LB(100);
  BR(150, 0.03, 0.12, 0);
  RB(100);
  BT(200, 0.03, 0.12, 200);
  BR(200, 0.03, 0.12, 50);
}

void s() {
  FT(200, 0.03, 0.12, 640, 'o');
  mct(-130, 130, 35);
  down();
  K();
  up();
  yt(150);
  R2B(10);
  BC(200, 0.03, 0.12, 10);
}

void hfs() {
  FR(150, 0.025, 0.1, 0, 'n');
  R(100, 'n');
  FL(150, 0.025, 0.1, 0, 'o');
  L(100, 'd');
  FT(150, 0.025, 0.1, 100, 'k');
  yt(50);
  BT(150, 0.025, 0.1, 50);
  BR(150, 0.025, 0.1, 0);
  RB(100);
  BL(150, 0.025, 0.1, 0);
  LB(100);
  BC(150, 0.025, 0.1, 50);
}

void hc() {
  FR(200, 0.03, 0.12, 0, 'n');
  R(100, 'd');
  FT(70, 0.025, 0.1, 800, 'k');
  BT(70, 0.025, 0.1, 500);
  BR(150, 0.025, 0.1, 0);
}

void s2() {
  FL(200, 0.03, 0.12, 0, 'n');
  L(100, 'n');
  FL(150, 0.03, 0.12, 0, 'n');
  L(100, 'n');
  FR(100, 0.01, 0.1, 0, 'n');
  R(100, 'n');
}

void n() {
  FR(200, 0.03, 0.12, 50, 'n');
  L2(10, 'n');
  mct(-130, 130, 100);
  down();
  mct(70, 70, 200);
  yt(150);
  K();
  yt(150);
  up();
  mct(-70, -70, 300);
  L2B(20);
}