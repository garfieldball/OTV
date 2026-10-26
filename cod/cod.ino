#include "Enes100.h"
#include "Tank.h"

#define PIN_MOTOR_1_FORWARD 11
#define PIN_MOTOR_1_REVERSE 10
#define PIN_MOTOR_2_FORWARD 9
#define PIN_MOTOR_2_REVERSE 8
#define PIN_MOTOR_3_FORWARD 4
#define PIN_MOTOR_3_REVERSE 5
#define PIN_MOTOR_4_FORWARD 2
#define PIN_MOTOR_4_REVERSE 3
// Bump Sensors
#define PIN_BUMP_FRONT 32
#define PIN_BUMP_REAR 33
// Ultrasonic Sensors
#define PIN_US_FRONT_TRIG 18
#define PIN_US_FRONT_ECHO 19
#define PIN_US_REAR_TRIG 27
#define PIN_US_REAR_ECHO 26
// Infrared Sensors
#define PIN_IR_1 15
#define PIN_IR_2 17
#define PIN_IR_3 14
#define PIN_IR_4 16
// WiFi Modules
#define PIN_WIFI_TX 52
#define PIN_WIFI_RX 50

int collision_tolerance = 15;
bool obstacleDetected = false;

float theta;
float y;

void setup() {
  Enes100.begin("Green Machine", HYDROGEN, 10, 1116, 52, 50);
  Tank.begin();

  pinMode(PIN_US_FRONT_TRIG, OUTPUT);
  pinMode(PIN_US_FRONT_ECHO, INPUT);
  updateSensors();

  //testing
  go(1000);
  stop();
  delay(500);
  goBack(1000);
  stop();
  delay(500);
  turnLeft();
  delay(500);
  turnLeft();
  turnRight();
  delay(500);
  turnRight();
  stop();
}

void loop() {
  //loop more like poop
}

/*
void navToExit(){
  //while not in goal site
  while (y < 3.4){
    while (!obstacleDetected){
      updateSensors();
      go();
    }

    //back up for a sec
    goBack();
    delay(1000);
    turnLeft();
    updateSensors();
    
    int count = 0;
    //tries left
    while (!obstacleDetected){
      updateSensors();
      go();
      delay(1000);
      turnRight();
      go();
      delay(1000);
      //will it break here if one is detected?
      turnLeft();
      delay(2000);
      turnRight();
      delay(1000);

      count++;
    }

    updateSensors();
    if (abs(theta - PI/2) < 0.05){
      goBack();
      delay(1000*count);

      //tries right
      while (!obstacleDetected){
        updateSensors();
        go();
        delay(1000);
        turnLeft();
        go();
        delay(1000);

        count++;
      }
    }
  }
}
*/

void updateSensors(){
  //turns it off for a bit to make sure it's ready
  digitalWrite(PIN_US_FRONT_TRIG, LOW);
  delayMicroseconds(2);
  //fires it
  digitalWrite(PIN_US_FRONT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_US_FRONT_TRIG, LOW);
  // measures it when it comes back and calculates
  float duration = pulseIn(PIN_US_FRONT_ECHO, HIGH, 30000);     
  float distance = (duration*.0343)/2;

  if (distance < collision_tolerance){
    obstacleDetected = true;
  } else {
    obstacleDetected = false;
  }

  theta = Enes100.getTheta();
  y = Enes100.getY();
}

void go(int ms){
  Tank.setRightMotorPWM(255);
  Tank.setLeftMotorPWM(255);
  delay(ms);
}

void goBack(int ms){
  Tank.setRightMotorPWM(-255);
  Tank.setLeftMotorPWM(-255);
  delay(ms);
}

void stop(){
  Tank.setRightMotorPWM(0);
  Tank.setLeftMotorPWM(0);
}

void turnLeft() {
  updateSensors();
  float target = theta + (PI/2);

  while (abs(atan2(sin(target - theta), cos(target - theta))) > 0.05) {
updateSensors();
    Tank.setLeftMotorPWM(-255);
    Tank.setRightMotorPWM(255);
  }
  stop();
}

void turnRight() {
  updateSensors();
  float target = theta - (PI/2);

  while (abs(atan2(sin(target - theta), cos(target - theta))) > 0.05) {
    updateSensors();
    Tank.setLeftMotorPWM(255);
    Tank.setRightMotorPWM(-255);
  }
  stop();
}