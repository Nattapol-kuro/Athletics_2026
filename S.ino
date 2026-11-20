void down() {
  yt(50);
  myservo1.write(19);
  yt(50);
}

void downH() {
  yt(50);
  myservo1.write(55);
  yt(50);
}

void up() {
  yt(50);
  myservo1.write(110);
  yt(50);
}

void O() {  //open
  yt(50);
  myservo2.write(162);
  myservo3.write(31);
  yt(150);
}

void O2() {  //open
  yt(50);
  myservo2.write(92);
  myservo3.write(108);
  yt(150);
}

void OH() {  //open
  yt(50);
  myservo2.write(127);
  myservo3.write(73);
  yt(150);
}

void K() {  //keep
  yt(50);
  myservo2.write(62);
  myservo3.write(130);
  yt(150);
}

void DK() {  //down keep
  yt(50);
  myservo1.write(19);
  yt(250);
  myservo2.write(162);
  myservo3.write(31);
  yt(150);
}

void LO() {  //left open
  yt(50);
  myservo2.write(162);
  myservo3.write(120);
  yt(50);
}

void RO() {  //right open
  yt(50);
  myservo2.write(82);
  myservo3.write(31);
  yt(50);
}