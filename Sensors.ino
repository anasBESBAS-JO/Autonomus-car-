// ---------------- Sonar Sensor functions  -----------------

float sonarFront() {
  turnOffLED();
  turnOnLED(LEDF);
  return fSonic.dist(); //return current distance (cm)
}

float sonarBack() {
  turnOffLED();
  turnOnLED(LEDB);
  return baSonic.dist(); //return current distance (cm)
}

float sonarFR() {
  turnOffLED();
  turnOnLED(LEDFR);
  return frSonic.dist(); //return current distance (cm)
}

float sonarFL() {
  turnOffLED();
  turnOnLED(LEDFL);
  return  flSonic.dist(); //return current distance (cm);
}


//-------------------Infarad sensor-----------------

//Necessary vars for sonar readings, setting speeds, etc.
int valR = 0;  // used to stock the distance from the Front right infarad sensor
int valL = 0;  // used to stock the distance from the front  left infarad sensor
int valBR = 0; // used to stock the distance from the back  right infarad sensor
int valFRS = 0; // used to stock the distance from the back   left infarad sensor

float mesureDisInfarad(int sensor){
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  return 13*pow(volts, -1); // worked out from datasheet graph
}
int sonarR() {
  turnOffLED();
  turnOnLED(LEDR);
  valR = mesureDisInfarad(Right);   // reads the value of the sharp sensor FrontRight
  Serial.println(valR);            // prints the value of the sensor to the serial monitor
  return valR == 0 ? 80 : valR;
}

int sonarL() {
  turnOffLED();
  turnOnLED(LEDL);
  valL = mesureDisInfarad(Left);       // reads the value of the sharp sensor FrontLeft
  Serial.println(valL);            // prints the value of the sensor to the serial monitor
  return valL== 0 ? 80 : valL;
}

int sonarBR() {
  valBR = mesureDisInfarad(BackRight);       // reads the value of the sharp sensor BackRight
  Serial.println(valBR);            // prints the value of the sensor to the serial monitor
  return valBR == 0 ? 80 : valBR;
}

int sonarFRSide() {
  valFRS = mesureDisInfarad(InfaradFRight);       // reads the value of the sharp sensor BackLeft
  Serial.println(valFRS);            // prints the value of the sensor to the serial monitor
  return valFRS == 0 ? 80 : valFRS;
}


void testsensor(){ // test all sensors are functionnal 
  Serial.println(sonarFront());
  Serial.println(sonarFront());
  delay(1000);
  Serial.println(sonarBack());
  Serial.println(sonarBack());
  delay(1000);
  Serial.println(sonarFL());
  Serial.println(sonarFL());
  delay(1000);
  Serial.println(sonarFR());
  Serial.println(sonarFR());
  delay(1000);
  Serial.println(sonarR());
  Serial.println(sonarR());
  delay(1000);
  Serial.println(sonarL());
  Serial.println(sonarL());
  delay(1000);
  Serial.println(sonarBR());
  Serial.println(sonarBR());
  delay(1000);
  Serial.println(sonarFRSide());
  Serial.println(sonarFRSide());  
  delay(1000);
}

float getTMP(){
  float t = dht.readTemperature();
  if (isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return t;
  }
  return t;
}
