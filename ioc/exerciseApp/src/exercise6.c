#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <dbEvent.h>
#include <dbDefs.h>
#include <dbCommon.h>
#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#define RED   75
#define BLUE 150
#define ND1  225
#define ND2  300

#if 0
#define RED_IN_BEAM  28   /* 1 1 1 0 0 */
#define BLUE_IN_BEAM 26   /* 1 1 0 1 0 */
#define ND1_IN_BEAM  22   /* 1 0 1 1 0 */
#define ND2_IN_BEAM  14   /* 0 1 1 1 0 */
#endif

#define RED_IN_BEAM  0
#define BLUE_IN_BEAM 1
#define ND1_IN_BEAM  2
#define ND2_IN_BEAM  3

/*
 * Inputs:
 * pasub->a = Demanded position  (DOUBLE)
 * pasub->b = Proportional Gain  (DOUBLE)
 * pasub->c = Integral Gain      (DOUBLE)
 * pasub->d = Derivative Gain    (DOUBLE)
 * pasub->e = Position Tolerance (DOUBLE)
 * pasub->f = velocity Tolerance (DOUBLE)
 *
 * Outputs:
 * pasub->vala = Current position (DOUBLE)
 * pasub->valb = Switch data      (LONG)
 * pasub->valc = Slide status     (STRING)
 *
 * Values stored between calls:
 * pasub->vald = Sum of error*deltaT (DOUBLE)
 * pasub->vale = Previous error      (DOUBLE)
 * pasub->valf = Previous position   (DOUBLE)
 *
 */

static long servo( aSubRecord *pasub )
{
  double currentPos;
  double demandPos;
  double P;
  double I;
  double D;
  double KP;
  double KI;
  double KD;
  double error;
  double sum;
  double deltaT;
  double prevError;
  double prevPos;
  long   switchData;
  double vel;
  double posTol;
  double velTol;

  currentPos = *(double *)pasub->vala;
  demandPos  = *(double *)pasub->a;
  KP         = *(double *)pasub->b;
  KI         = *(double *)pasub->c;
  KD         = *(double *)pasub->d;
  error      = demandPos - currentPos;
  deltaT     = 0.05;  /* 20 Hz */
  if( KI != 0.0 )
    sum = *(double *)pasub->vald + (error * deltaT);
  else
    sum = 0.0;
  prevError  = *(double *)pasub->vale;

  P = KP * error;
  I = KP * KI * sum;
  D = KP * KD * (error - prevError)/deltaT;

  /* Before overwriting the current position, save it */
  /* as the previous position                         */

  *(double *)pasub->valf = currentPos;

  currentPos += P + I + D;

  /* Now save important information for the next call */

  *(double *)pasub->vala = currentPos;
  *(double *)pasub->vald = sum;
  *(double *)pasub->vale = prevError;


 /* Calculate the switch data */

  posTol = *(double *)pasub->e;

  if( (currentPos >= RED-posTol) && (currentPos <= RED+posTol) )
    switchData = RED_IN_BEAM;
  else if( (currentPos >= BLUE-posTol) && (currentPos <= BLUE+posTol) )
    switchData = BLUE_IN_BEAM;
  else if( (currentPos >= ND1-posTol)  && (currentPos <= ND1+posTol) )
    switchData = ND1_IN_BEAM;
  else if( (currentPos >= ND2-posTol)  && (currentPos <= ND2+posTol) )
    switchData = ND2_IN_BEAM;
  else
    switchData = -1;

  *(long *)pasub->valb = switchData;


  /* Calculate the slide status: MOVING or STOPPED          */
  /* The condition for STOPPED is that the current position */
  /* must be within "posTol" of the demand position and the */
  /* absolute velocity must be less than "velTol"           */

  velTol = *(double *)pasub->f;

  prevPos = *(double *)pasub->valf;

  vel = (currentPos - prevPos)/deltaT;

  if( (currentPos >= demandPos-posTol) && (currentPos <= demandPos+posTol) )
  {
    if( fabs(vel) <= velTol )
      strcpy( pasub->valc, "STOPPED" );
    else
      strcpy( pasub->valc, "MOVING" );
  }
  else
    strcpy( pasub->valc, "MOVING" );

  return(0);
}

epicsRegisterFunction(servo);
