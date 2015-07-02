#include	<assert.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>

#define		RIGHT	1
#define		LEFT	0

#define		MOVE_RIGHT	0
#define		MOVE_LEFT	1
#define	        HIT_SOMETHING_AND_MOVE_LEFT	2
#define		HIT_SOMETHING_AND_MOVE_RIGHT	3

int		starPosition;
int		starDirection;
int		mapSize;
int		prediction;
char		*state;

int		starTouchesRightWall()
{
  return (starPosition == mapSize);
}

int		starIsGoingRight()
{
  return (starDirection == RIGHT);
}

int		starTouchesLeftWall()
{
  return (starPosition == 1);
}

void		predictorPredictMove()
{
  if (starIsGoingRight())
    {
      if (starTouchesRightWall())
	{
	  prediction = HIT_SOMETHING_AND_MOVE_LEFT;
	}
      else
	{
	  prediction = MOVE_RIGHT;
	}
    }
  else
    {
      if (starTouchesLeftWall())
	{
	  prediction = HIT_SOMETHING_AND_MOVE_RIGHT;
	}
      else
	{
	  prediction = MOVE_LEFT;
	}
    }
}

void		controllerExecutePrediction()
{
  if (prediction == MOVE_RIGHT)
    {
      starPosition++;
    }
  else if (prediction == MOVE_LEFT)
    {
      starPosition--;
    }
  else if (prediction == HIT_SOMETHING_AND_MOVE_LEFT)
    {
      starDirection = LEFT;
      starPosition--;
    }
  else
    {
      starDirection = RIGHT;
      starPosition++;
    }
}

void		presenterPrepareState()
{
  int		i;
  
  state = (char *) malloc(mapSize + 2);
  
  for (i = 0; i < mapSize; i++)
    {
      state[i] = ' ';
    }
  state[mapSize] = '|';
  state[mapSize + 1] = '\0';
  state[starPosition - 1] = '*';
}

void		appPrepareTheAnimation(int size)
{
  starPosition = 1;
  starDirection = RIGHT;
  mapSize = 10;
}

void		predictorShouldPredictMoveRight()
{
  starPosition = 1;
  starDirection = RIGHT;
  mapSize = 10;
  predictorPredictMove();
  assert(prediction == MOVE_RIGHT);
}

void		predictorShouldPredictMoveLeft()
{
  starPosition = 9;
  starDirection = LEFT;
  mapSize = 10;
  predictorPredictMove();
  assert(prediction == MOVE_LEFT);
}

void		predictorShouldPredictMoveHitSomethingAndMoveLeft()
{
  starPosition = 10;
  starDirection = RIGHT;
  mapSize = 10;
  predictorPredictMove();
  assert(prediction == HIT_SOMETHING_AND_MOVE_LEFT);
}

void		predictorShouldPredictMoveHitSomethingAndMoveRight()
{
  starPosition = 1;
  starDirection = LEFT;
  mapSize = 10;
  predictorPredictMove();
  assert(prediction == HIT_SOMETHING_AND_MOVE_RIGHT);
}

void		controllerShouldMoveStarRight()
{
  starPosition = 1;
  prediction = MOVE_RIGHT;
  controllerExecutePrediction();
  assert(starPosition == 2);
}

void		controllerShouldMoveStarLeft()
{
  starPosition = 8;
  prediction = MOVE_LEFT;
  controllerExecutePrediction();
  assert(starPosition == 7);
}

void		controllerShouldMakeStarHitSomethingAndMoveLeft()
{
  starPosition = 9;
  prediction = HIT_SOMETHING_AND_MOVE_LEFT;
  controllerExecutePrediction();
  assert(starPosition == 8);
  assert(starDirection == LEFT);
}

void		controllerShouldMakeStarHitSomethingAndMoveRight()
{
  starPosition = 1;
  prediction = HIT_SOMETHING_AND_MOVE_RIGHT;
  controllerExecutePrediction();
  assert(starPosition == 2);
  assert(starDirection == RIGHT);
}

void		presenterShouldPrepareState()
{
  starPosition = 1;
  mapSize = 5;
  presenterPrepareState();
  assert(state[0] == '*');
  assert(state[1] == ' ');
  assert(state[2] == ' ');
  assert(state[3] == ' ');
  assert(state[4] == ' ');
  assert(state[5] == '|');
  assert(state[6] == '\0');
}

void		appShouldPrepareTheAnimation()
{
  appPrepareTheAnimation(10);
  assert(starPosition == 1);
  assert(starDirection == RIGHT);
  assert(mapSize == 10);
}

int		length(char *str)
{
  return (strlen(str));
}

void		waitALittleBit()
{
  sleep(1);
}

void		screenDisplayState()
{
  write(1, "\r", 1);
  write(1, state, length(state));
  waitALittleBit();
}

void		appMain()
{
  appPrepareTheAnimation(10);
  while (1)
    {
      presenterPrepareState();
      screenDisplayState();
      predictorPredictMove();
      controllerExecutePrediction();
    }
}

int		main()
{
  predictorShouldPredictMoveRight();
  predictorShouldPredictMoveLeft();
  predictorShouldPredictMoveHitSomethingAndMoveLeft();
  predictorShouldPredictMoveHitSomethingAndMoveRight();
  controllerShouldMoveStarRight();
  controllerShouldMoveStarLeft();
  controllerShouldMakeStarHitSomethingAndMoveLeft();
  controllerShouldMakeStarHitSomethingAndMoveRight();
  presenterShouldPrepareState();
  appShouldPrepareTheAnimation();
  appMain();
  return (0);
}
