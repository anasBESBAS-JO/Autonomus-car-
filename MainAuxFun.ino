void blinking() {
  digitalWrite(LEDONE, !digitalRead(LEDONE)); // Toggle the LED
  delay(70);
  digitalWrite(LEDONE, !digitalRead(LEDONE));
  delay(70);
  digitalWrite(LEDONE, !digitalRead(LEDONE));
  delay(70);
  digitalWrite(LEDONE, !digitalRead(LEDONE));
  delay(70);
  digitalWrite(LEDONE, !digitalRead(LEDONE));
}

void turnOffLED(){ // turn off sensor's led
  digitalWrite(LEDFR,LOW);
  digitalWrite(LEDFL,LOW);
  digitalWrite(LEDF,LOW);
  digitalWrite(LEDB,LOW);
  digitalWrite(LEDR,LOW);
  digitalWrite(LEDL,LOW);
}


void turnOnLED(char LEDNAME){ // indicate which sensor is active NOW 
  digitalWrite(LEDNAME,HIGH);
}
