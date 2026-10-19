#include <string>

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

void loop() {


}

//1 is the site closest to the bottom, 2 is the other one (north)
int detectLocation(){
  //go to office hours and talk about how the hell it gets info from the thing
  if (){
    location = 1;
  } else {
    location = 2;
  }
  
  return location;
}

//Custom functions start here!!!!!!!!!!!!!!!!!!!
void navToMission(){
  
}

void completeMission(){

}
