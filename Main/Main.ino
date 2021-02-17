#include <IRremote.h> // to control the IR reciver and remote 
#include <Servo.h> // to control the motors 
#include <TimerOne.h> // used to preforme interruption functions 
#include "DHT.h" // to control tmp sensor 
//#include <HCSR04.h>

#define TIMER_US 50       // 50 uS timer duration
#define TICK_COUNTS 4000  // 200 mS worth of timer ticks
#define echo_int 0       // Interrupt id for front echo pulse

const int RECV_PIN = 3;    // IR recever pin and configuration

IRrecv irrecv(RECV_PIN);
decode_results results;    // store read value from the remote

byte LEDONE = 7;           // LED for the interrupt function 
byte LED = 9;         // led for blinking function

Servo motor;               //Create ESC drive motor 'motor' and steering servo 'steer'
Servo steer;
int direct = steer.read(); // read actual servo direction

//Motor Speed control -> PWM signal
const int speedCenter = 1450;  // neutral
int forwardSpeed = 1380;       // MAX Speed front
int reverseSpeed = 1550;       // reverse

#define DHTPIN 4      //define the digital pin for DHT temprature Sensor
#define DHTTYPE DHT11 // define the type of DHT Sensor
DHT dht(DHTPIN, DHTTYPE); //  Initialize DHT sensor

//Servo Angle control degree
const int neutral = 90; // Steering servo positions for straight, left turns,
                        // and right turns. These can be changed and are set in
                        // degrees.
const int steerRight = 40; // 55
const int steerLeft = 140; // 145

// Sonar pins
const int echoF = 2;     //Pins for readFront() - Sonar on front interrupt pin
const int trigF = 37;


const int echoB = 34;    //Pins for readBack() - Sonar on back
const int trigB = 36;

// infarad pins
const int FrontRight = 24; //Pins for readFrontR()
const int FrontLeft = 29;  //Pins for readFrontL()
const int BackRight = 25;  //Pins for readBackR()
const int BackLeft = 31;   //Pins for readBackL()


const int frontThreshold = 66;    //Thresholds for the different 'types' of sonar sensors -- front, front side, and side. These can be changed and are set in centimeters.
const int frontSideThreshold = 45;
const int sideThreshold = 10;

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 Baud
  motor.attach(3);      //Attaches motor to pin 8
  motor.writeMicroseconds(speedCenter); // Set motor to neutral
  delay(500);
  motor.writeMicroseconds(speedCenter);
  steer.attach(12);     //Attaches steering servo to pin 12
  steer.write(neutral); // Set steering to straight
  Serial.println("MOTOR ATTACHED");
  delay(500);
  irrecv.enableIRIn();  //Enable IR reciver 
  irrecv.blink13(true); // Blink LED13 every time reciver recive a signal 
  pinMode(LEDONE, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LEDONE, LOW);
  digitalWrite(LED, LOW);
  pinMode(trigF, OUTPUT);                             // Trigger pin set to output                                                                                              
  pinMode(echoF, INPUT);                              // Echo pin set to Input  
  Timer1.initialize(TIMER_US);                        // Initialise timer 1
  Timer1.attachInterrupt(timerIsr);                   // Attach interrupt to the timer service routine
  attachInterrupt(echo_int, echo_interrupt, CHANGE);  // Attach interrupt to the sensor echo input
  dht.begin();
}

void loop() {
  blinking();
  accelatarte();
  Serial.println("Ready to recive :)");
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume();
    if (results.value == 0xFF30CF) {
      blinking();
      Serial.println("hi");
      irrecv.resume();
    } else if (irrecv.decode(&results) == 0xFF30CF) {
      blinking();
      Serial.println(results.value, HEX);
      turnShow();
      irrecv.resume();
    }
  }
}
