/* Autonomous Car Code
 *  
 *  This code was written for the Sparkfun AVC competition
  Chaitanya.Sanghadia@gmail.com "Chai"
  matt.chandlerAZ@gmail.com "Matt"

 */

void GoStraight(int feet, int velocity)
{
  // Throttle for = 25 Count is ~ 2500 mSec
  for (int i = 0 ; i < 25 ; i++) {
    drive.writeMicroseconds(CRUISESPEED);
    delay(100);
  }
}
//============================================================================================
void TurnLeft()
{
  // Turn Left and delay
  steering.write(STEER_LEFT);
  delay(DELAYAFTERLEFT);
}
//============================================================================================
void StartupAndAlign()
{
  // Set the steering to go straight
  steering.write(STRAIGHT);
  delay(STARTUP_DELAY_MS);
}
void TurnEngineOff()
{
  //TODO
}
//============================================================================================
void TurnRight()
{
  // Turn Right and delay
  steering.write(STEER_RIGHT);
  delay(DELAYAFTERRIGHT);
}
//============================================================================================
void Backup(int feet)
{}
//============================================================================================
void StartupThrottleEngine(int iSpeed)
{
  // Write to the drive servo and add delay to get the THROTTLE going and to avoid timing issues
  // related to XL5 Motor Controller
  //============================================================================================
  drive.writeMicroseconds(current_speed);
  delay(iSpeed);
}
void NavigationRecheck(int leg)
{
}


