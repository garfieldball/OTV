//setup
#include <string>

//variables
int collision_tolerance = 15
bool obstacleDetected = false


//main stuff
void setup() {
  std::string orientation = detectLocation();

  navToMission();
  completeMission();
  if (orientation = 1){
    //turn right
  } else {
    //turn left
  }

  navToGoal();

}

//runs all the time
void loop() {
  //distance = get distance from the sensor (convert to mm)
  x = Enes100.getX()
  y = Enes100.getY()

}

//Custom functions start here!!!!!!!!!!!!!!!!!!!

//1 is the site closest to the bottom, 2 is the other one (north)
//orients the OTV towards the mission site and detects which starting point it's in
int detectLocation(){
  //figure out how to get aruco info
  if (){
    location = 1;
  } else {
    location = 2;
  }

  return location;
}

//docks with the mission site
void navToMission(){
  
}

//completes mission tasks
void completeMission(){

}

//procedural navigation to get to the goal!
void navToGoal(){
  //while not in goal site
  while (y < 3400)
    while (distance >= collision_tolerance){
      //move forward
    }

    //back up a lil
    //turn left (scanning) (find peaks in a graph of distance vs time?)
    obstacleDetected = scan();
    if (obstacleDetected = true){
      //move left
      //turn right
    } else {
      //turn back to normal
    }

    //turn RIGHT (scanning) (find peaks in a graph of distance vs time?)
    if (obstacleDetected = true){
      //move left
      //turn right
    } else {
      //turn back to normal
    }
    
  } 
}