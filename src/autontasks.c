#include "main.h"

#define OK_TO_BRAKE 10
extern int operation;
extern int liftdist;
extern int lmp;
extern int armdist;
extern int amp;
int speed = 0;
int status = 0;
void movelift()
{
  if (lmp < 0)
  {
    if (encoderGet(LiftEncoder) >= liftdist)
    {
      motorSet(LIFT_MOTOR,lmp);
      delay(30);
    }
    else
    {
      motorSet(LIFT_MOTOR,20);
    }

  }
  else if (lmp > 0)
     {
       if (encoderGet(LiftEncoder) <= liftdist)
       {
         motorSet(LIFT_MOTOR,lmp);
         delay(30);
       }

       else
       {
         motorSet(LIFT_MOTOR,20);
       }
    }
}
void movearm()
{
if (encoderGet(ArmEncoder) <= armdist)
{
  motorSet(ARM_MOTOR,amp);
  delay(30);
}
else
{
  motorSet(ARM_MOTOR,0);
}

}

void decelerate(int counts)
{
  int mp = 0;
  while( (encoderGet(LeftDriveEncoder) < counts-375) )
  {
  //speed =
    if (speed > OK_TO_BRAKE)
    {
    //char buf[17];
      mp = -2 * (speed / 4.5);
    }
    motorLeftDriveSet(mp);
    motorRightDriveSet(mp);
  }


  mp = 20;
  motorLeftDriveSet(mp);
  motorRightDriveSet(mp);

  while( encoderGet(LeftDriveEncoder) < counts ){delay(20);}
  motorLeftDriveSet(0);
  motorRightDriveSet(0);
}

void decelerateBack(int counts)
{
  int mp = 0;
  while( (encoderGet(LeftDriveEncoder) > -counts+375) )
  {
  //speed =
    if (speed < -OK_TO_BRAKE)
    {
    //char buf[17];
      mp = 2 * (speed / 4.5);
    }
    motorLeftDriveSet(mp);
    motorRightDriveSet(mp);
  }

  mp = -20;
  motorLeftDriveSet(mp);
  motorRightDriveSet(mp);

  while( encoderGet(LeftDriveEncoder) > -counts ){delay(20);}
  motorLeftDriveSet(0);
  motorRightDriveSet(0);
}


void getSpeed()
{
  static int lastcounts = 0;
  int a = encoderGet(LeftDriveEncoder);
  speed = encoderGet(LeftDriveEncoder) - lastcounts;
  lastcounts = a;
}


void autoMobileGoal()
{
  status = readmgs();
  switch(status)
  {
    case 0:
            break;
    case 1:
            motorSet(MOBILE_GOAL_MOTOR,-127);
            if(analogRead(MOBILE_GOAL_POT) < 1515){}
            else
            {
                motorSet(MOBILE_GOAL_MOTOR,0);
                status=0;
            }
            break;
    case 2:
            if(analogRead(MOBILE_GOAL_POT) > 15) {motorSet(MOBILE_GOAL_MOTOR,127); }
            else
            {
              motorSet(MOBILE_GOAL_MOTOR,0);
             status=0;
            }
            break;

  }
}

void intake()
{
  switch(operation)
  {
    case 0:
          motorSet(CLAW_MOTOR,0);
          break;
    case 1:
          motorSet(CLAW_MOTOR,-120);
          delay(250);
          motorSet(CLAW_MOTOR,-20);
          break;
    case 2:
          motorSet(CLAW_MOTOR,120);
          delay(400);
          operation = 0;
          break;
  }
}
