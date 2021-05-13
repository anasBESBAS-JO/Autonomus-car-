// with ultrasonic sensors 

#include <HCSR04.h>   // used to control HCSR04 Sensors.
#include <IRremote.h> // used to control the IR reciver and remote.
#include <Servo.h>    // used to control the motors.
#include "DHT.h"      // used to control DHT sensor.

// IR recever pin and configuration
const int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;    // store read value from the remote

// LEDs from different checks and signs
byte LEDONE = 7;          // LED for the proximity  function
byte LED    = 9;          // led for blinking function
byte LEDFR  = 19;         // indicate a call for frontRight sensor
byte LEDFL  = 14;         // indicate a call for frontLeft sensor
byte LEDF   = 15;         // indicate a call for front sensor
byte LEDB   = 16;         // indicate a call for Back sensor
byte LEDR   = 17;         // indicate a call for Right sensor
byte LEDL   = 18;         // indicate a call for Left sensor

//Create ESC drive motor 'motor' and steering servo 'steer'
Servo motor;
Servo steer;

int direct     = steer.read(); // read actual servo direction
int speedMicro = motor.read(); // read actual motor speed

//Motor Speed control -> PWM signal
const int speedCenter = 1500;    // new speed center 1500
const int forwardSpeed = 1400;    // Min Speed front new speed min 1400 new
// speed max 1280
const int forwardSpeedMax = 1280;    // Max Speed front
const int reverseSpeed = 1960;    // reverse //1570 1550 //  new one for min :
// 1620 // max new 1960
const int reverseSpeedMin = 1620;    //Min Speed reverse

// tmp sensor
#define DHTPIN 4      //define the digital pin for DHT temprature Sensor
#define DHTTYPE DHT11 // define the type of DHT Sensor
DHT dht(DHTPIN, DHTTYPE); // Creat DHT object to Initialize DHT sensor

//Servo position control values
const int neutral = 1480; // Steering servo positions for straight, left
// turns, and right turns
const int steerRight = 1000;
const int steerLeft = 1960;

// Sonars pins & initialisations by creating an object from type HCSR04
HCSR04 fSonic(37, 2); //initialisation class HCSR04 for the front sensor (trig
// pin , echo pin)
HCSR04 flSonic(39, 5); //initialisation class HCSR04 for the frontleft
// sensor(trig pin , echo pin)
HCSR04 frSonic(38, 8); //initialisation class HCSR04 for the frontright sensor
// (trig pin , echo pin)
HCSR04 baSonic(40, 6); //initialisation class HCSR04 for the back sensor(trig
// pin , echo pin)

// infarad pins
#define Right  A0 //Pins for sonarR()
#define Left   A1  //Pins for sonarL()
#define InfaradFRight A2 //Pins for sonarFRSide()
#define BackRight A3 //Pins for sonarBR()

//Thresholds
const int frontThreshold = 66;    //Thresholds for the different 'types' of
// sonar sensors front,sides, and Back.In
// centimeters.
const int sideThreshold = 25;
const int backThreshold = 40;
const int frontSideThreshold = 66;

float distance;          // vars for sonar readings.
float distance2;
float distance3;
float distance4;
float distance5;

void setup() {
  Serial.begin(9600);                                  // Start serial
  // communication at 9600
  // Baud
  motor.attach(3);                                     //Attaches motor to pin 3
  Serial.println("MOTOR ATTACHED");
  speedCenterN();                                      // Set motor to neutral
  delay(500);
  steer.attach(12);                                    //Attaches steering servo
  // to pin 12
  Serial.println("Steer ATTACHED");
  delay(500);
  steer.write(neutral);                                // Set steering to
  // straight
  irrecv.enableIRIn();                                 //Enable IR reciver
  irrecv.blink13(true);                                // Blink LED13 every time
  // IR reciver recive a signal
  pinMode(LEDONE, OUTPUT);                            // LEDS initialisation
  pinMode(LED   , OUTPUT);
  pinMode(LEDF  , OUTPUT);
  pinMode(LEDB  , OUTPUT);
  pinMode(LEDFR , OUTPUT);
  pinMode(LEDFL , OUTPUT);
  pinMode(LEDL  , OUTPUT);
  pinMode(LEDR  , OUTPUT);

  digitalWrite(LED, HIGH);
  blinking();                                         // Blink the top led to
  // indecate car is ready
  turnOffLED();                                       // turn off all leds
  dht.begin();                                        // start dht sensor comunication
}


/* 
 the used  IR Remote is " Tsop 8m 38kHz 1838 Ir Transmetteur Arduino " 
 if another remote is on use follow the next steps :
 1 - make sure to put all code line in the loop in comment exept for 
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
    }
 2 - download the programe into the arduino
 3 - open serial monitor
 4 - get values from the monitor and replace them with the old ones

*/
void loop() {
  if (getTMP() > 45){ // IF MOTOR tmp is greater than 45 
    delay(60000); // sleep for 60 seconds
    Serial.println("Moteur TMP :");
    Serial.println(getTMP());
  }
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
    if (results.value == 0xFF30CF) { // press 1
      blinking();
      Serial.println("autoDrive() >>> Loading");
      //testsensor();
      autoDrive();
      Serial.println("autoDrive() >>> Done");
      irrecv.resume();
    } else if (results.value == 0xFF18E7) { // press 2
      blinking();
      Serial.println(results.value, HEX);
      Serial.println("forwardReverseDemo() >>> Loading");
      motor.writeMicroseconds(speedCenter);
      forwardReverseDemo();
      motor.writeMicroseconds(speedCenter);
      Serial.println("forwardReverseDemo() >>> Done");
      irrecv.resume();
    } else if (results.value == 0xFF7A85) { // press 3
      blinking();
      Serial.println(results.value, HEX);
      Serial.println("SteerDemo() >>> Loading");
      SteerDemo();
      Serial.println("SteerDemo() >>> Done");
      irrecv.resume();
    } else if (results.value == 0xFF10EF) { // press 4
      blinking();
      Serial.println(results.value, HEX);
      Serial.println("overTaking() >>> Loading");
      overTaking();
      Serial.println("overTaking() >>> Done");
      irrecv.resume();
    } else if (results.value == 0xFF38C7) { // press 5
      blinking();
      Serial.println(results.value, HEX);
      Serial.println("autoParking() >>> Loading");
      autoParking();
      Serial.println("autoParking() >>> Done");
      irrecv.resume();
    } else if (results.value == 0xFFA857) { // press +
      blinking();
      Serial.println(results.value, HEX);
      Serial.println("Speeding >>> Loading");
      motor.writeMicroseconds(forwardSpeed);
      Serial.println("Speeding >>> Done");
      irrecv.resume();
    } else if (results.value == 0xFFE01F) { // press -
      blinking();
      Serial.println(results.value, HEX);
      Serial.println("breaking >>> Loading");
      turnOnLED(LEDB);
      breaking();
      delay(500);
      turnOffLED();
      speedCenterN();
      Serial.println("breaking >>> Done");
      irrecv.resume();
    } else if (results.value == 0xFF02FD) { // press >>|
      blinking();
      Serial.println(results.value, HEX);
      Serial.println("right turn >>> Loading");
      motor.writeMicroseconds(forwardSpeed);
      longRightTurn();
      Serial.println("right turn >>> Done");
      irrecv.resume();
    } else if (results.value == 0xFF22DD) { // press |<<
      blinking();
      Serial.println(results.value, HEX);
      Serial.println("Left turn >>> Loading");
      motor.writeMicroseconds(forwardSpeed);
      longLeftTurn();
      Serial.println("breaking >>> Done");
      irrecv.resume();
    } else if (results.value == 0xFF6897) { // press 0
      blinking();
      Serial.println(results.value, HEX);
      Serial.println("reversing >>> Loading");
      turnOnLED(LEDB);
      speedCenterN();
      motor.writeMicroseconds(reverseSpeed);
      delay(200);
      speedCenterN();
      turnOffLED();
      Serial.println("reversing >>> Done");
      irrecv.resume();
    }
  }
  blinking();
}
