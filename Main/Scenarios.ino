void accelatarte() { //Function called to execute speeding with acceleration from min to max speed
  steer.write(neutral);
  for (int i = 1380; i > 1250; --i) { 
    motor.writeMicroseconds(i);
    delay(30);
  }
  delay(2000);
  for (int i = 1250; i < 1380; ++i) {
    motor.writeMicroseconds(i);
    delay(30);
  }
  motor.writeMicroseconds(speedCenter);
  delay(2000);
  for (int i = 1550; i < 1630; ++i) {
    motor.writeMicroseconds(i);
    delay(30);
  }
  delay(2000);
  for (int i = 1630; i > 1550; --i) {
    motor.writeMicroseconds(i);
    delay(30);
  }
  motor.writeMicroseconds(speedCenter);
  delay(2000);
  
}

void autoParking(){
  speedCenterN();
  delay(50);
  speedBMin();
  while(sonarFR() > 10){
    sonarFR();
    delay(30);
   }
}

void turnShow() { //  Function called to execute a multiple turn
  rightTurn();
  delay(500);
  leftTurn();
  delay(500);
  longLeftTurn();
  delay(500);
  longRightTurn();
}


void autoDrive(){
  steer.write(neutral);
  speedFMax(); 
}


void overTaking(){
  
}
