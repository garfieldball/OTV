//setup
#include <string>

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

}