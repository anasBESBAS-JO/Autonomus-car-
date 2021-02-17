// ---------------- sonar Sensor functions  -----------------

float time_ = 0;          // Time to receve the pulse
float distanceFront = 0;  //  Distance for the front sensor
float distanceBack = 0;   //  Distance for the  back sensor

int sonarFront() {
  time_ = 0;
  distanceFront = 0;
  digitalWrite(trigF, LOW);
  delayMicroseconds(2);
  digitalWrite(trigF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigF, LOW);
  delayMicroseconds(2);
  time_ = pulseIn(echoF, HIGH);
  distanceFront = time_ * 340 / 20000;
  return distanceFront;
}

int sonarBack() {
  time_ = 0;
  distanceBack = 0;
  digitalWrite(trigB, LOW);
  delayMicroseconds(2);
  digitalWrite(trigB, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigB, LOW);
  delayMicroseconds(2);
  time_ = pulseIn(echoB, HIGH);
  distanceBack = time_ * 340 / 20000;
  return distanceBack;
}


//-------------------Infarad sensor-----------------

 //Necessary vars for sonar readings, setting speeds, etc.
int valFR = 0; // used to stock the distance from the Front right infarad sensor
int valFL = 0; // used to stock the distance from the front  left infarad sensor
int valBR = 0; // used to stock the distance from the back  right infarad sensor
int valBL = 0; // used to stock the distance from the back   left infarad sensor

int sonarFR() {
  valFR = analogRead(FrontRight);   // reads the value of the sharp sensor FrontRight
  Serial.println(valFR);            // prints the value of the sensor to the serial monitor
  return valFR;
}

int sonarFL() {
  valFL = analogRead(FrontLeft);       // reads the value of the sharp sensor FrontLeft
  Serial.println(valFL);            // prints the value of the sensor to the serial monitor
  return valFL;
}

int sonarBR() {
  valBR = analogRead(BackRight);       // reads the value of the sharp sensor BackRight
  Serial.println(valBR);            // prints the value of the sensor to the serial monitor
  return valBR;
}

int sonarBL() {
  valBL = analogRead(BackLeft);       // reads the value of the sharp sensor BackLeft
  Serial.println(valBL);            // prints the value of the sensor to the serial monitor
  return valBL;
}

float getTMP(){
  float t = dht.readTemperature();
  if (isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return t;
  }
  return t;
}
