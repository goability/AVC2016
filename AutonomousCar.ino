/* Autonomous Car Code
 *  
 *  This code was written for the Sparkfun AVC competition
  Chaitanya.Sanghadia@gmail.com "Chai"
  matt.chandlerAZ@gmail.com "Matt"

 */
#include <Servo.h>
#include "constants.h"

#define DEBUG = true
#define SIMULATIONMODE = false

Servo steering;
Servo drive;

int current_speed = 0;

// timeDelay account using milliSec for future use
//==================================================
unsigned long previousMillis = 0;

//Setup course mapping arrays (index = Leg)
int MapDistance[COURSELEGS] = {LEG1,LEG2,LEG3,LEG4,LEG5,LEG6,LEG7,LEG8,LEG9};
  
int MapSpeed[COURSELEGS] = {FASTSPEED, CRUISESPEED, CRUISESPEED,CRUISESPEED,CRUISESPEED,SLOWSPEED,SLOWSPEED,SLOWSPEED,FASTSPEED};

char MapTurnsAtEndOfLeg[COURSELEGS] = {RIGHT, RIGHT, LEFT, RIGHT, RIGHT, LEFT, LEFT, RIGHT, RIGHT };

char MapOBSTACLES[COURSELEGS] = {OBSTACLENONE,OBSTACLENONE,OBSTACLEBARREL,OBSTACLEHOOP,OBSTACLERAMP,OBSTACLENONE,OBSTACLENONE,OBSTACLENONE,OBSTACLENONE};

bool offCourse = false; // Set separately via serial input, triggers to remap

void setup()
{
  //Start ESC
  drive.writeMicroseconds(0);
  delay(1000);
  drive.writeMicroseconds(NEUTRAL);
  delay(100);

  //Setup Steering
  steering.attach(PINSTEER);

  //Setup Drive
  drive.attach(PINDRIVE);
  current_speed = NEUTRAL;

}


//============================================================================================
//==============================  MAIN WORKING LOOP ==========================================
//============================================================================================   
void loop()
{
  StartupAndAlign();

  StartupThrottleEngine(STARTUP_DELAY_MS);

  

/* DESIGN:  For each leg of course: 
 *    - Go the direction and speed indicated
 *    - Take a turn and continue to next iteration
 *    ---> IF LEG HAS OBSTACLES, RAMP, HOOP, ETC ...
 *    [
 *       -- SLOW TO STOP, SCAN, REMAP and CONTINUE
 *    
 *    ]  
 *  
 */

  for (int i=0; i< COURSELEGS; i++)
  {
    GoStraight(MapDistance[i], MapSpeed[i]);
    
    switch(MapTurnsAtEndOfLeg[i])
    {
      case LEFT:
        TurnLeft();
      case RIGHT:
        TurnRight();
    }

    NavigationRecheck(i);
  }

  TurnEngineOff(); // THE END !!
  exit(1);

}


