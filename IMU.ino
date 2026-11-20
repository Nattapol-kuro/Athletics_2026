void getIMU() {
  float y = -1.0;
  for (int i = 0; i < 7; i++) {
    float v = getYaw();
    if (v >= 0) y = v;
    delay(5);
  }
  while (y < 0) {
    y = getYaw();
    delay(5);
  }
  startYaw = y;
}

float getAngleError(float target, float current) {
  float error = target - current;
  if (error > 180.0) error -= 360.0;
  if (error < -180.0) error += 360.0;
  return error;
}

void gyroDrive(int speed, unsigned long ms) {
  getIMU();
  float target = startYaw;
  unsigned long start = millis();
  while (millis() - start < ms) {
    float y = getYaw();
    if (y < 0) y = lastYaw;
    float err = getAngleError(target, y) * YAW_DIR;
    int corr = (int)(err * KP_STRAIGHT);
    MC(speed + corr, speed - corr);
    delay(5);
  }
  STOP();
}

int readFrontSensor(int ch) {
  my_mux.channel(ch);
  delayMicroseconds(50);
  return analogRead(signal_pin);
}

int readBackSensor(int ch) {
  my_mub.channel(ch);
  delayMicroseconds(50);
  return analogRead(signal_pinB);
}


void gyrocrossDrive(int speed, int sensorIndex) {
  getIMU();
  float target = startYaw;

  bool back = speed < 0;

  while (true) {

    int value;

    if (back) {
      value = readBackSensor(sensorIndex);
    } else {
      value = readFrontSensor(sensorIndex);
    }

    // ตรวจสอบค่าตาม Calibration ของเซนเซอร์
    int sensorThreshold;

    if (back) {
      sensorThreshold = senbackMin[sensorIndex] + (senbackMax[sensorIndex] - senbackMin[sensorIndex]) * 0.5;
    } else {
      sensorThreshold = sensorMin[sensorIndex] + (sensorMax[sensorIndex] - sensorMin[sensorIndex]) * 0.5;
    }

    if (value >= sensorThreshold) break;

    float y = getYaw();
    if (y < 0) y = lastYaw;

    float err = getAngleError(target, y) * YAW_DIR;
    int corr = (int)(err * KP_STRAIGHT);

    MC(speed + corr, speed - corr);
  }

  STOP();
}


void gyroPivot(float angle, bool goForward) {
  getIMU();
  float delta = goForward ? -angle : angle;
  bool useRight = angle > 0;
  float prevYaw = startYaw;
  float rotated = 0;
  unsigned long start = millis();
  int stable = 0;

  while (stable < 5 && millis() - start < 8000) {
    float y = getYaw();
    if (y >= 0) {
      rotated += getAngleError(y, prevYaw);
      prevYaw = y;
    }
    float err = delta - rotated * YAW_DIR;

    if (abs(err) <= TOLERANCE) {
      stable++;
      STOP();
      delay(5);
      continue;
    }
    stable = 0;

    int u = (int)(abs(err) * KP_TURN);
    u = constrain(u, TURN_MIN, TURN_MAX);
    if (err < 0) u = -u;
    if (useRight) MC(0, -u);
    else MC(u, 0);
    delay(5);
  }
  STOP();
}

void GF(int speed, unsigned long ms) {
  gyroDrive(abs(speed), ms);
}

void GB(int speed, unsigned long ms) {
  gyroDrive(-abs(speed), ms);
}

void GCF(int speed, int mode) {
  gyrocrossDrive(abs(speed), mode);
}

void GCB(int speed, int mode) {
  gyrocrossDrive(-abs(speed), mode);
}

void GTF(float angle) {
  gyroPivot(angle, true);
}

void GTB(float angle) {
  gyroPivot(angle, false);
}

const float KP_SPIN = 2.0;
const int SPIN_MIN = 22;
const int SPIN_MAX = 160;
const float SPIN_TOLERANCE = 1.0;

void gyroSpin(float angle) {
  getIMU();
  float delta = -angle;
  float prevYaw = startYaw;
  float rotated = 0;
  unsigned long start = millis();
  int stable = 0;

  while (stable < 5 && millis() - start < 8000) {
    float y = getYaw();
    if (y >= 0) {
      rotated += getAngleError(y, prevYaw);
      prevYaw = y;
    }
    float err = delta - rotated * YAW_DIR;

    if (abs(err) <= SPIN_TOLERANCE) {
      stable++;
      STOP();
      delay(5);
      continue;
    }
    stable = 0;

    int u = (int)(abs(err) * KP_SPIN);
    u = constrain(u, SPIN_MIN, SPIN_MAX);
    if (err < 0) u = -u;

    MC(u, -u);
    delay(5);
  }
  STOP();
}