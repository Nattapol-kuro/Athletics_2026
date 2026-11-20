void RB(int time) {
  MC(50, -200);
  delay(time);
  readLineB(330, 50);
  while (sensorValues[8] < 300) {
    readLineB(330, 50);
    MC(30, -180);
  }
}

void L2B(int time) {
  MC(-200, 200);
  delay(time);
  readLineB(330, 50);
  while (sensorValues[5] < 300) {
    readLineB(330, 50);
    MC(-180, 180);
  }
}

void LB(int time) {
  MC(-200, 50);
  delay(time);
  readLineB(330, 50);
  while (sensorValues[7] < 300) {
    readLineB(330, 50);
    MC(-180, 30);
  }
}

void R2B(int time) {
  MC(200, -200);
  delay(time);
  readLineB(330, 50);
  while (sensorValues[10] < 300) {
    readLineB(330, 50);
    MC(180, -180);
  }
}

void stdPIDB(int BaseSpeed, float Kp, float Kd, int crossSpeed = 10) {
  Position = readLineB(330, 50);
  int error = Position - 7500;
  PIDValue = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  if (PIDValue > BaseSpeed) PIDValue = BaseSpeed;
  if (PIDValue < -BaseSpeed) PIDValue = -BaseSpeed;
  leftPower = BaseSpeed - PIDValue;
  rightPower = BaseSpeed + PIDValue;
  if (leftPower >= 255) leftPower = 255;
  if (leftPower <= 0) leftPower = -120;
  if (rightPower >= 255) rightPower = 255;
  if (rightPower <= 0) rightPower = -120;
  MC(-leftPower, -rightPower);
}


void stdPIDCB(int BaseSpeed, float Kp, float Kd, int crossSpeed = 10) {
  Position = readLineB(330, 50);
  if (sensorValues[3] > 300 || sensorValues[12] > 300) MC(-BaseSpeed + crossSpeed, -BaseSpeed + crossSpeed);
  else {
    int error = Position - 7500;
    PIDValue = (Kp * error) + (Kd * (error - last_error));
    last_error = error;
    if (PIDValue > BaseSpeed) PIDValue = BaseSpeed;
    if (PIDValue < -BaseSpeed) PIDValue = -BaseSpeed;
    leftPower = BaseSpeed - PIDValue;
    rightPower = BaseSpeed + PIDValue;
    if (leftPower >= 255) leftPower = 255;
    if (leftPower <= 0) leftPower = -120;
    if (rightPower >= 255) rightPower = 255;
    if (rightPower <= 0) rightPower = -120;
    MC(-leftPower, -rightPower);
  }
}
void stdPIDBU(int BaseSpeed, float Kp, float Kd, int crossSpeed = 10) {
  Position = readLineB(330, 50);
  int error = Position - 12500;
  PIDValue = (Kp * error) + (Kd * (error - last_error));
  last_error = error;
  if (PIDValue > BaseSpeed) PIDValue = BaseSpeed;
  if (PIDValue < -BaseSpeed) PIDValue = -BaseSpeed;
  leftPower = BaseSpeed - PIDValue;
  rightPower = BaseSpeed + PIDValue;
  if (leftPower >= 255) leftPower = 255;
  if (leftPower <= 0) leftPower = -120;
  if (rightPower >= 255) rightPower = 255;
  if (rightPower <= 0) rightPower = -120;
  MC(-leftPower, -rightPower);
}

void BT(int BaseSpeed, float Kp, float Kd, int time) {
  unsigned long looptime;
  looptime = millis();
  while (millis() - looptime <= time) {
    Position = readLine(330, 50);
    stdPIDB(BaseSpeed, Kp, Kd);
  }
}

void BTU(int BaseSpeed, float Kp, float Kd, int time) {
  unsigned long looptime;
  looptime = millis();
  while (millis() - looptime <= time) {
    Position = readLine(330, 50);
    stdPIDBU(BaseSpeed, Kp, Kd);
  }
}

void BC(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLine(330, 50);
  while (sensorValues[3] < 300 || sensorValues[12] < 300) {
    Position = readLine(330, 50);
    stdPIDB(BaseSpeed, Kp, Kd);
  }
  mct(-BaseSpeed, -BaseSpeed, time);
}

void BR(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLine(330, 50);
  while (sensorValues[15] < 250) {
    Position = readLine(330, 50);
    stdPIDB(BaseSpeed, Kp, Kd);
  }
  mct(-BaseSpeed, -BaseSpeed, time);
}

void BL(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLine(330, 50);
  while (sensorValues[0] < 300) {
    Position = readLine(330, 50);
    stdPIDB(BaseSpeed, Kp, Kd);
  }
  mct(-BaseSpeed, -BaseSpeed, time);
}

void BSC(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLineB(330, 50);
  while (sensorValues[3] < 300 || sensorValues[12] < 300) {
    Position = readLineB(330, 50);
    stdPIDCB(BaseSpeed, Kp, Kd);
  }
  Position = readLineB(330, 50);
  while (analogRead(60) > sl || analogRead(60) > sr) {
    Position = readLineB(330, 50);
    stdPIDB(100, 0.015, 0.08);
  }
  mct(-BaseSpeed, -BaseSpeed, time);
}

void BSL(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLineB(330, 50);
  while (sensorValues[3] < 300) {
    Position = readLineB(330, 50);
    stdPIDCB(BaseSpeed, Kp, Kd);
  }
  Position = readLineB(330, 50);
  while (analogRead(60) > sl) {
    Position = readLineB(330, 50);
    stdPIDB(100, 0.005, 0.07);
  }
  mct(-BaseSpeed, -BaseSpeed, time);
}

void BSR(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLineB(330, 50);
  while (sensorValues[12] < 300) {
    Position = readLineB(330, 50);
    stdPIDCB(BaseSpeed, Kp, Kd);
  }
  Position = readLine(330, 50);
  while (analogRead(60) > sr) {
    Position = readLineB(330, 50);
    stdPIDB(100, 0.005, 0.07);
  }
  mct(-BaseSpeed, -BaseSpeed, time);
}

void BLU(int BaseSpeed, float Kp, float Kd, int time) {
  Position = readLine(330, 50);
  while (sensorValues[4] < 300) {
    Position = readLine(330, 50);
    stdPIDBU(BaseSpeed, Kp, Kd);
  }
  mct(-BaseSpeed, -BaseSpeed, time);
}