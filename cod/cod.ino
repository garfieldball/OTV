#include "Arduino.h"
#include "Enes100.h"
#include "Tank.h"

float tol = 0.025;
//todo: all turns have course correction and slow down near the turn
//course correction for straight lines
//require multiple checks before stopping
//it's NOT gonna make it through the side.
//what if it gets stuck?

void setup() {
  Enes100.begin("Green Simulator", HYDROGEN, 3, 1116, 8, 9);
  Tank.begin();
  
  //navigation to mission site
if (Enes100.getY() < 1){
  //starting spot 1 (bottom)
  turnTo(PI/2);
} else {
  //top
  turnTo(-PI/2);
}
  
  //go until it detects a collision (runs into the mission site)
  while(Tank.readDistanceSensor(1) > 0.1 || Tank.readDistanceSensor(1) == -1){
    goForever();
  }
  stop();
  //do tasks
  goBack(500);
  stop();
  //yay! you did the first part!
  
  //turn outta here
  turnTo(0);
  go(1000);
  int obstacleCount;
  if(Enes100.getY() < 1.5){
    obstacleCount = 3;
  } else {
    obstacleCount = 1;
  }
  
  //navigation out of mission site!!!!!!!!!!!!!!!!! (the hard part)
  //goes until it's right in front of the bar/log
  while(Enes100.getX() < 3){
    if (obstacleCount == 3){
      //go back to obstacle 1
      turnTo(PI/2);
      while(abs(1.5 - Enes100.getY()) > tol){
        goForever();
      }
      turnTo(0);
      stop();
      obstacleCount = 1;
    }

    while ((Tank.readDistanceSensor(1) > 0.1 || Tank.readDistanceSensor(1) == -1) && (Enes100.getX() < 3)){
      goForever();
    }
    
    stop();
    //if you won
    if (Enes100.getX() > 2.5){
      break;
    }

    //obstacle :(
    goBack(500);
    turnRight();
    go(1250);
    turnLeft();
    obstacleCount++;
  }

  //you made it to just before the bar!!! yay!!!!!!!!!!!!
  stop();
  
  //align to bar
  if (obstacleCount > 1){
    turnTo(PI/2);
    while(Enes100.getY() < 1.5){
      goForever();
    }
    turnRight();
    stop();
  }
  
  while(Enes100.getX() < 3.75){
    goForever();
  }
  stop();
  //yay you win!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void loop() {
    delay(100);
    //loop more like poop 2
}

//functionssssssssssssssssssssssssssssssssssssssssssssssss start here

void go(int ms){ 
  Tank.setRightMotorPWM(255);
  Tank.setLeftMotorPWM(255);
  delay(ms);
  stop();
}

void goForever(){ 
  Tank.setRightMotorPWM(255);
  Tank.setLeftMotorPWM(255);
}

void goBack(int ms){
  Tank.setRightMotorPWM(-255);
  Tank.setLeftMotorPWM(-255);
  delay(ms);
  stop();
}

//I'm aware that using time to turn is a BAD idea but like... the distance sensor is worse
void turnLeft(){
    Tank.setRightMotorPWM(255);
    Tank.setLeftMotorPWM(-255);
    delay(878);
    stop();
}

void turnRight(){
    Tank.setRightMotorPWM(-255);
    Tank.setLeftMotorPWM(255);
    delay(878);
    stop();
}

//It just turns left until it reaches it (BAD)
void turnTo(float target){
  while(abs(target - Enes100.getTheta()) > tol){
    Tank.setRightMotorPWM(255);
    Tank.setLeftMotorPWM(-255);
  }
  stop();
}

void stop(){
  Tank.turnOffMotors();
}