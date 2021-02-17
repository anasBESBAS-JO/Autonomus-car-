// ------------------ SECOND_SHOW_ ------------------
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
  delay(475);
  steer.write(neutral);
  Serial.println("LONG LEFT");
}

void longRightTurn() {          //Function called to execute a long, right turn
                                // when a wall is detected by the front sensor.
                                // Should be approximately 90 degrees.
  steer.write(steerRight);
  motor.writeMicroseconds(forwardSpeed);
  delay(475);
  steer.write(neutral);
  Serial.println("LONG RIGHT");
}
