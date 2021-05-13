void rightTurn() {              //Function called to execute a short, right turn
                                // to get away from a wall
  steer.write(steerRight);
  motor.writeMicroseconds(forwardSpeed);
  delay(50);
  steer.write(neutral);
  Serial.println("RIGHT TURN");
}

void leftTurn() {               //Function called to execute a short, left turn
                                // to get away from a wall
  steer.write(steerLeft);
  motor.writeMicroseconds(forwardSpeed);
  delay(50);
  steer.write(neutral);
  Serial.println("LEFT TURN");
}


void longLeftTurn() {           //Function called to execute a long, left turn
                                // when a wall is detected by the front sensor.
                                // Should be approximately 90 degrees.
  steer.write(steerLeft);
  motor.writeMicroseconds(forwardSpeed);
  delay(250);
  steer.write(neutral);
  Serial.println("LONG LEFT");
}

void longRightTurn() {          //Function called to execute a long, right turn
                                // when a wall is detected by the front sensor.
                                // Should be approximately 90 degrees.
  steer.write(steerRight);
  motor.writeMicroseconds(forwardSpeed);
  delay(250);
  steer.write(neutral);
  Serial.println("LONG RIGHT");
}

void widerightTurn() {          //Function called to execute a long, right turn
                                // when a wall is detected by the front sensor.
                                // Should be approximately 90 degrees.
  steer.write(steerRight);
  motor.writeMicroseconds(forwardSpeed);
  delay(1300);
  steer.write(neutral);
  Serial.println("LONG RIGHT");
}


void shortRightTurn(){ //Function called to execute a short short , right turn
                                // to get away from a wall
  steer.write(steerRight);
  motor.writeMicroseconds(forwardSpeed);
  delay(30);
  steer.write(neutral);
  Serial.println("shortRightTurn");
}
void shortshortRightTurn(){ //Function called to execute a short short , left turn
                                // to get away from a wall
  steer.write(steerRight);
  motor.writeMicroseconds(forwardSpeed);
  delay(10);
  steer.write(neutral);
  Serial.println("shortRightTurn");
}

void shortLeftTurn(){ //Function called to execute a short, left turn
                                // to get away from a wall
  steer.write(steerLeft);
  motor.writeMicroseconds(forwardSpeed);
  delay(30);
  steer.write(neutral);
  Serial.println("shortLeftTurn");
}
void frontLeftTurn() {          //Function called to execute a 45 degree right
                                // turn when the front left sensor is triggered.
  steer.write(steerLeft);
  motor.writeMicroseconds(forwardSpeed);
  delay(90);
  steer.write(neutral);
  Serial.println("FRONT LEFT TURN");
}

void frontRightTurn() {         //Function called to execute a 45 degree right
                                // turn when the front left sensor is triggered.
  steer.write(steerRight);
  motor.writeMicroseconds(forwardSpeed);
  delay(90);
  steer.write(neutral);
  Serial.println("FRONT RIGHT TURN");
}

void turnSpeedDirTime(int Speed, int Direction, int Time) { //Function called to execute a turn with given
                                                            // direction speed and time
  steer.write(Direction);
  motor.writeMicroseconds(Speed);
  delay(Time);
  steer.write(neutral);
}

void stopReverseTurn() { // stop reverse and turn the car depending on sensors values 
                         // to determin in which way the car should move 
  breaking();
  if (sonarBack() > backThreshold) {
    if (sonarR() > sideThreshold && sonarR() != 0) {
      steer.write(steerLeft);
      Serial.println("Left revesing");
      motor.writeMicroseconds(reverseSpeed);
      delay(1000);
      steer.write(neutral);
    } else if (sonarL() > sideThreshold && sonarL() != 0) {
      steer.write(steerRight);
      Serial.println("Right revesing");
      motor.writeMicroseconds(reverseSpeed);
      delay(1000);
      steer.write(neutral);
    } else {
      steer.write(neutral);
      Serial.println("line revesing");
      motor.writeMicroseconds(reverseSpeed);
      delay(500);
      steer.write(steerRight);
      delay(500);
    }
  }
  steer.write(neutral);
  motor.writeMicroseconds(speedCenter);
  Serial.println("Stop turn reverse Done");
  turnOffLED();
}

void checkFront() { // check front if the car and call stopReverseTurn() function
                    // if an obstical is present in front of the car (wall ....etc)
                    // this function use front sensor 
  Serial.print("\ncheckFront : ");
  float distanceFront = sonarFront(); 
  if (distanceFront < 11) {
    Serial.println("wall detected");
    stopReverseTurn();
  } else {
  Serial.print("wall non detected");
  }
}

void correctionSteering(){ // function to correct the mechanical problem of the car
                           //it mesure all side of the car and determine if right or left turn 
                           // is nessecary for the car to keep on track
  steer.write(neutral);
  float dis1 = sonarFL();
  float dis2 = sonarFR();
  float dis3 = sonarL();
  float dis4 = sonarR();
  if (dis1 > dis2 || (dis3 > dis4 && dis3 <= 30)){
    motor.writeMicroseconds(forwardSpeed);
    steer.write(steerRight);
    delay(90);
  } else if (dis1 < dis2 || (dis3 < dis4 && dis4 <= 30)){
    motor.writeMicroseconds(forwardSpeed);
    steer.write(steerLeft);
    delay(90);
  } else {
    steer.write(neutral);
  }
  steer.write(neutral);
}
