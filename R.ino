int analog16(int channel) {
  my_mux.channel(channel);
  return analogRead(signal_pin);
}

void readPrivate() {
  for (int i = 0; i < NUMSENSOR; i++) {
    sensorValues[i] = analog16(i);
  }
}

void readCalibrated() {
  readPrivate();
  for (int i = 0; i < NUMSENSOR; i++) {
    int denominator = sensorMax[i] - sensorMin[i];
    long x = 0;
    if (denominator != 0) {
      x = ((long)sensorValues[i] - sensorMin[i]) * 1000 / denominator;
    }
    if (x < 0) x = 0;
    if (x > 1000) x = 1000;
    sensorValues[i] = x;
  }
}

int readLine(int keep_track, int noise_threshold) {
  unsigned char on_line = 0;
  unsigned long avg = 0;
  unsigned int sum = 0;
  static int last_value = 0;

  readCalibrated();

  for (int i = 0; i < NUMSENSOR; i++) {
    int value = sensorValues[i];
    if (value > keep_track) {
      on_line = 1;
    }
    if (value > noise_threshold) {
      avg += (long)value * (i * 1000);
      sum += value;
    }
  }

  if (!on_line) {
    if (last_value < 7500)
      return 0;
    else
      return 15000;
  }

  last_value = avg / sum;
  return last_value;
}

void calibrate(int calibrateTime) {
  int readMin[NUMSENSOR];
  int readMax[NUMSENSOR];

  Serial.println("Calibrating");
  for (int j = 0; j < calibrateTime; j++) {
    readPrivate();
    for (int i = 0; i < NUMSENSOR; i++) {
      if (j == 0 || readMax[i] < sensorValues[i]) readMax[i] = sensorValues[i];
      if (j == 0 || readMin[i] > sensorValues[i]) readMin[i] = sensorValues[i];
    }
    delay(5);
  }
  Serial.println("Calibrated");

  Serial.print("int sensorMax[16] = {");
  for (int i = 0; i < NUMSENSOR; i++) {
    Serial.print(readMax[i]);
    if (i != NUMSENSOR - 1) Serial.print(",");
    else Serial.println("};");
  }
  Serial.print("int sensorMin[16] = {");
  for (int i = 0; i < NUMSENSOR; i++) {
    Serial.print(readMin[i]);
    if (i != NUMSENSOR - 1) Serial.print(",");
    else Serial.println("};");
  }
}

void monitorSensor() {
  while (1) {
    Serial.print(readLine(330, 50));
    Serial.print("\t");
    for (int k = 0; k < NUMSENSOR; k++) {
      Serial.print(sensorValues[k]);
      Serial.print("\t");
    }
    Serial.println();
    delay(100);
  }
}

void Read(){
  while(1){
    Serial.print(analogRead(61));
    Serial.print("\n\n");
    Serial.print(analogRead(60));
    Serial.print("\t");
  }
}