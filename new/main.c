#include	<string.h>
#include	<unistd.h>
#include	<assert.h>
#include	<stdlib.h>

#define		RIGHT	1
#define		LEFT	0

#define		STAR_MOVE_RIGHT	0
#define		STAR_MOVE_LEFT	1
#define		STAR_HIT_SOMETHING_AND_MOVE_LEFT 2
#define		STAR_HIT_SOMETHING_AND_MOVE_RIGHT 3
#define		STAR_DO_NOT_MOVE 4
#define		STAR_SPAWN_RIGHT 5
#define		STAR_SPAWN_LEFT 6

#define		TEXT_DO_NOT_MOVE 0
#define		TEXT_MOVE_RIGHT	1
#define		TEXT_MOVE_LEFT	2
#define		TEXT_DROP_LAST_CHARACTER 3
#define		TEXT_DROP_FIRST_CHARACTER 4

int		starPosition;
int		starDirection;
int		textPosition;
int		textLength;
char		*textContent;
int		mapSize;
int		starMovePrediction;
int		textMovePrediction;
char		*state;

int		starIsGoingRight()
{
  return (starDirection == RIGHT);
}

int		starIsTouchingRightWall()
{
  return (starPosition == mapSize);
}

int		starIsTouchingLeftWall()
{
  return (starPosition == 1);
}

int		starIsTouchingTextLeft()
{
  return (starPosition + 1 == textPosition);
}

int		starIsTouchingTextRight()
{
  return (textPosition + textLength == starPosition);
}

int		starIsBlockedOnLeftSide()
{
  return (starPosition == 1 
	  && textPosition == 2);
}

int		starIsBlockedOnRightSide()
{
  return (starPosition == mapSize 
	   && textPosition + textLength == starPosition);
}

int		starIsBlocked()
{
  return (starIsBlockedOnLeftSide()
	  || starIsBlockedOnRightSide());
}

int		textIsTouchingRightWall()
{
  return (textPosition + textLength - 1 == mapSize);
}

int		textIsTouchingLeftWall()
{
  return (textPosition == 1);
}

void		predictMoveForStarTouchingTextLeft()
{
  if (textIsTouchingRightWall())
    {
      starMovePrediction = STAR_SPAWN_RIGHT;
    }
  else
    {
      starMovePrediction = STAR_HIT_SOMETHING_AND_MOVE_LEFT;
    }
}

void		predictMoveForStarGoingRight()
{
  if (starIsTouchingTextLeft())
    {
      predictMoveForStarTouchingTextLeft();
    }
  else if (starIsTouchingRightWall())
    {
      starMovePrediction = STAR_HIT_SOMETHING_AND_MOVE_LEFT;
    }
  else
    {
      starMovePrediction = STAR_MOVE_RIGHT;
    }
}

void		predictMoveForStarTouchingTextRight()
{
  if (textIsTouchingLeftWall())
    {
      starMovePrediction = STAR_SPAWN_LEFT;
    }
  else
    {
      starMovePrediction = STAR_HIT_SOMETHING_AND_MOVE_RIGHT;
    }
}

void		predictMoveForStarGoingLeft()
{
  if (starIsTouchingTextRight())
    {
      predictMoveForStarTouchingTextRight();
    }
  else if (starIsTouchingLeftWall())
    {
      starMovePrediction = STAR_HIT_SOMETHING_AND_MOVE_RIGHT;
    }
  else
    {
      starMovePrediction = STAR_MOVE_LEFT;
    }
}

void		predictorPredictStarMove()
{
  if (starIsBlocked())     
    {
      starMovePrediction = STAR_DO_NOT_MOVE;
    }
  else if (starIsGoingRight())
    {
      predictMoveForStarGoingRight();
    }
  else
    {
      predictMoveForStarGoingLeft();
    }
}

int		starIsGoingLeft()
{
  return (!starIsGoingRight());
}

int		starHitTextLeft()
{
  return (starIsGoingRight()
	  && starIsTouchingTextLeft());
}

int		starHitTextRight()
{
  return (starIsGoingLeft()
	  && starIsTouchingTextRight());
}

void		predictorPredictTextMove()
{
  if (starHitTextLeft())
    {
      if (textIsTouchingRightWall())
	{
	  textMovePrediction = TEXT_DROP_LAST_CHARACTER;
	}
      else
	{
	  textMovePrediction = TEXT_MOVE_RIGHT;
	}
    }
  else if (starHitTextRight())
    {
      if (textIsTouchingLeftWall())
	{
	  textMovePrediction = TEXT_DROP_FIRST_CHARACTER;
	}
      else
	{
	  textMovePrediction = TEXT_MOVE_LEFT;
	}
    }
  else
    {
      textMovePrediction = TEXT_DO_NOT_MOVE;
    }
}

typedef struct	
{
  char		*testDescription;
  int		starPosition;
  int		starDirection;
  int		textPosition;
  int		textLength;
  int		mapSize;
  int		expectedPrediction;
}		StarMovePredictionTestCase;

StarMovePredictionTestCase	starPredictions[] = {
  {(char*) "should predict star move right.", 1, RIGHT, 4, 2, 10, STAR_MOVE_RIGHT},
  {(char*) "should predict star move left.", 2, LEFT, 4, 2, 10, STAR_MOVE_LEFT},
  {(char*) "should predict star hit right wall and move left.", 10, RIGHT, 3, 2, 10, STAR_HIT_SOMETHING_AND_MOVE_LEFT},
  {(char*) "should predict star hit left wall and move right.", 1, LEFT, 4, 2, 10, STAR_HIT_SOMETHING_AND_MOVE_RIGHT},
  {(char*) "should predict star hit text left and move left.", 2, RIGHT, 3, 2, 10, STAR_HIT_SOMETHING_AND_MOVE_LEFT},
  {(char*) "should predict star hit text right and move right.", 6, LEFT, 4, 2, 10, STAR_HIT_SOMETHING_AND_MOVE_RIGHT},
  {(char*) "should predict star is blocked on the left side.", 1, LEFT, 2, 2, 10, STAR_DO_NOT_MOVE},
  {(char*) "should predict star is blocked on the right side.", 10, LEFT, 8, 2, 10, STAR_DO_NOT_MOVE},
  {(char*) "should predict star will spawn on the right side.", 8, RIGHT, 9, 2, 10, STAR_SPAWN_RIGHT},
  {(char*) "should predict star will spawn on the left side.", 3, LEFT, 1, 2, 10, STAR_SPAWN_LEFT},
};

#define		STAR_PREDICTIONS_COUNT	sizeof(starPredictions) / sizeof(StarMovePredictionTestCase)

void		setupStarMovePredictionTest(StarMovePredictionTestCase testCase)
{
  starPosition = testCase.starPosition;
  starDirection = testCase.starDirection;
  textPosition = testCase.textPosition;
  textLength = testCase.textLength;
  mapSize = testCase.mapSize;
}

int		length(char *str)
{
  return (strlen(str));
}

void		displayTestDescription(StarMovePredictionTestCase testCase)
{
  char		*description;

  description = testCase.testDescription;
  write(1, description, length(description)); 
  write(1, "\n", 1);
}

void		testAllStarMovePredictions()
{
  int		i;
  StarMovePredictionTestCase	testCase;

  for (i = 0; i < STAR_PREDICTIONS_COUNT; i++)
    {
      testCase = starPredictions[i];
      displayTestDescription(testCase);
      setupStarMovePredictionTest(testCase);
      predictorPredictStarMove();
      assert(starMovePrediction == testCase.expectedPrediction);
    }
}

void		predictorShouldPredictTextDoNotMove()
{
  starPosition = 1;
  textPosition = 3;
  predictorPredictTextMove();
  assert(textMovePrediction == TEXT_DO_NOT_MOVE);
}

void		predictorShouldPredictTextMoveRight()
{
  starPosition = 1;
  starDirection = RIGHT;
  textPosition = 2;
  textLength = 2;
  mapSize = 10;
  predictorPredictTextMove();
  assert(textMovePrediction == TEXT_MOVE_RIGHT);
}

void		predictorShouldPredictTextMoveLeft()
{
  starPosition = 5;
  starDirection = LEFT;
  textPosition = 3;
  textLength = 2;
  mapSize = 10;
  predictorPredictTextMove();
  assert(textMovePrediction == TEXT_MOVE_LEFT);
}

void		predictorShouldPredictTextDropsLastCharacter()
{
  starPosition = 8;
  starDirection = RIGHT;
  textPosition = 9;
  textLength = 2;
  mapSize = 10;
  predictorPredictTextMove();
  assert(textMovePrediction == TEXT_DROP_LAST_CHARACTER);
}

void		predictorShouldPredictTextDropsFirstCharacter()
{
  starPosition = 3;
  starDirection = LEFT;
  textPosition = 1;
  textLength = 2;
  predictorPredictTextMove();
  assert(textMovePrediction == TEXT_DROP_FIRST_CHARACTER);
}

typedef		void (*action)();

action		starActions[7];
action		textActions[5];

void		starMoveRight()
{
  starPosition++;
}

void		starMoveLeft()
{
  starPosition--;
}

void		starHitSomethingAndMoveLeft()
{
  starDirection = LEFT;
  starMoveLeft();
}

void		starHitSomethingAndMoveRight()
{
  starDirection = RIGHT;
  starMoveRight();
}

void		starDoNotMove()
{
}

void		starSpawnRight()
{
  starDirection = LEFT;
  starPosition = mapSize;
}

void		starSpawnLeft()
{
  starDirection = RIGHT;
  starPosition = 1;
}

void		textDoNotMove()
{
}

void		textMoveRight()
{
  textPosition++;
}

void		textMoveLeft()
{
  textPosition--;
}

void		textDropLastCharacter()
{
  textLength--;
  textContent = strndup(textContent, textLength);
}

void		textDropFirstCharacter()
{
  textLength--;
  textContent = strndup(textContent + 1, textLength);
  textPosition = 2;
}  
					  
void		controllerPrepareStarActions()
{
  starActions[STAR_MOVE_RIGHT] = starMoveRight;
  starActions[STAR_MOVE_LEFT] = starMoveLeft;
  starActions[STAR_HIT_SOMETHING_AND_MOVE_LEFT] = starHitSomethingAndMoveLeft;
  starActions[STAR_HIT_SOMETHING_AND_MOVE_RIGHT] = starHitSomethingAndMoveRight;
  starActions[STAR_DO_NOT_MOVE] = starDoNotMove;
  starActions[STAR_SPAWN_RIGHT] = starSpawnRight;
  starActions[STAR_SPAWN_LEFT] = starSpawnLeft;
}

void		controllerPrepareTextActions()
{
  textActions[TEXT_DO_NOT_MOVE] = textDoNotMove;
  textActions[TEXT_MOVE_RIGHT] = textMoveRight;
  textActions[TEXT_MOVE_LEFT] = textMoveLeft;
  textActions[TEXT_DROP_LAST_CHARACTER] = textDropLastCharacter;
  textActions[TEXT_DROP_FIRST_CHARACTER] = textDropFirstCharacter;
}

void		controllerExecuteStarPrediction()
{
  action	starAction;

  starAction = starActions[starMovePrediction];
  starAction();
}

void		controllerExecuteTextPrediction()
{
  action	textAction;

  textAction = textActions[textMovePrediction];
  textAction();
}

void		controllerShouldPrepareStarActions()
{
  controllerPrepareStarActions();
  assert(starActions[STAR_MOVE_RIGHT] == starMoveRight);
  assert(starActions[STAR_MOVE_LEFT] == starMoveLeft);
  assert(starActions[STAR_HIT_SOMETHING_AND_MOVE_LEFT] == starHitSomethingAndMoveLeft);
  assert(starActions[STAR_HIT_SOMETHING_AND_MOVE_RIGHT] == starHitSomethingAndMoveRight);
  assert(starActions[STAR_DO_NOT_MOVE] == starDoNotMove);
  assert(starActions[STAR_SPAWN_RIGHT] == starSpawnRight);
  assert(starActions[STAR_SPAWN_LEFT] == starSpawnLeft);
}

void		controllerShouldPrepareTextActions()
{
  controllerPrepareTextActions();
  assert(textActions[TEXT_DO_NOT_MOVE] == textDoNotMove);
  assert(textActions[TEXT_MOVE_RIGHT] == textMoveRight);
  assert(textActions[TEXT_MOVE_LEFT] == textMoveLeft);
  assert(textActions[TEXT_DROP_LAST_CHARACTER] == textDropLastCharacter);
  assert(textActions[TEXT_DROP_FIRST_CHARACTER] == textDropFirstCharacter);
}

void		controllerShouldMoveStarRight()
{
  starPosition = 1;
  starMovePrediction = STAR_MOVE_RIGHT;
  controllerExecuteStarPrediction();
  assert(starPosition == 2);
}

void		controllerShouldMoveStarLeft()
{
  starPosition = 2;
  starMovePrediction = STAR_MOVE_LEFT;
  controllerExecuteStarPrediction();
  assert(starPosition == 1);
}

void		controllerShouldMakeStarHitSomethingAndMoveLeft()
{
  starPosition = 3;
  starDirection = RIGHT;
  starMovePrediction = STAR_HIT_SOMETHING_AND_MOVE_LEFT;
  controllerExecuteStarPrediction();
  assert(starPosition == 2);
  assert(starDirection == LEFT);
}

void		controllerShouldMakeStarHitSomethingAndMoveRight()
{
  starPosition = 1;
  starDirection = LEFT;
  starMovePrediction = STAR_HIT_SOMETHING_AND_MOVE_RIGHT;
  controllerExecuteStarPrediction();
  assert(starPosition == 2);
  assert(starDirection == RIGHT);
}

void		controllerShouldNotMakeStarMove()
{
  starPosition = 1;
  starDirection = RIGHT;
  starMovePrediction = STAR_DO_NOT_MOVE;
  controllerExecuteStarPrediction();
  assert(starDirection == RIGHT);
  assert(starPosition == 1);
}

void		controllerShouldSpawnStarRight()
{
  starPosition = 1;
  starDirection = RIGHT;
  mapSize = 10;
  starMovePrediction = STAR_SPAWN_RIGHT;
  controllerExecuteStarPrediction();
  assert(starDirection == LEFT);
  assert(starPosition == 10);
}

void		controllerShouldSpawnStarLeft()
{
  starPosition = 7;
  starDirection = LEFT;
  starMovePrediction = STAR_SPAWN_LEFT;
  controllerExecuteStarPrediction();
  assert(starDirection == RIGHT);
  assert(starPosition == 1);
}

void		controllerShouldNotMakeTextMove()
{
  textPosition = 3;
  textMovePrediction = TEXT_DO_NOT_MOVE;
  controllerExecuteTextPrediction();
  assert(textPosition == 3);
}

void		controllerShouldMoveTextRight()
{
  textPosition = 5;
  textMovePrediction = TEXT_MOVE_RIGHT;
  controllerExecuteTextPrediction();
  assert(textPosition == 6);
}

void		controllerShouldMoveTextLeft()
{
  textPosition = 5;
  textMovePrediction = TEXT_MOVE_LEFT;
  controllerExecuteTextPrediction();
  assert(textPosition == 4);
}

int		sameText(char *t1, char *t2)
{
  return (t1 != NULL
	  && t2 != NULL
	  && !strcmp(t1,t2));
}

void		controllerShouldMakeTextDropLastCharacter()
{
  textContent = strdup("Arnaud");
  textLength = 6;
  textMovePrediction = TEXT_DROP_LAST_CHARACTER;
  controllerExecuteTextPrediction();
  assert(!strcmp(textContent, "Arnau"));
  assert(textLength == 5);
}

void		controllerShouldMakeTextDropFirstCharacter()
{
  textContent = strdup("Arnaud");
  textLength = 6;
  textMovePrediction = TEXT_DROP_FIRST_CHARACTER;
  controllerExecuteTextPrediction();
  assert(!strcmp(textContent, "rnaud"));
  assert(textLength == 5);
  assert(textPosition == 2);
}

void		presenterPresentState()
{
  int		i;
  int		j;

  state = malloc(mapSize + 2);
  
  for (i = 0; i < mapSize; i++)
    {
      state[i] = ' ';
    }
  
  state[mapSize] = '|';
  state[mapSize + 1] = '\0';

  for (i = textPosition - 1, j = 0; j < textLength; i++, j++)
    {
      state[i] = textContent[j];
    }
  state[starPosition - 1] = '*';
}

void		presenterShouldPrepareState()
{
  starPosition = 1;
  textPosition = 3;
  textContent = strdup("Cedric");
  textLength = 6;
  mapSize = 10;
  presenterPresentState();
  assert(state[0] == '*');
  assert(state[1] == ' ');
  assert(state[2] == 'C');
  assert(state[3] == 'e');
  assert(state[4] == 'd');
  assert(state[5] == 'r');
  assert(state[6] == 'i');
  assert(state[7] == 'c');
  assert(state[8] == ' ');
  assert(state[9] == ' ');
  assert(state[10] == '|');
  assert(state[11] == '\0');
}

void		appPrepareTheAnimation(int size, char *text)
{
  starPosition = 1;
  starDirection = RIGHT;
  textContent = strdup(text);
  textLength = length(text);
  textPosition = 2;
  mapSize = size;
}

void		appShouldPrepareTheAnimation()
{
  appPrepareTheAnimation(10, "Kenfack");
  assert(starPosition == 1);
  assert(starDirection == RIGHT);
  assert(sameText(textContent, "Kenfack"));
  assert(textPosition == 2);
  assert(textLength == 7);
  assert(mapSize == 10);
}

void		waitALittleBit()
{
  usleep(10000);
}

void		screenDisplayState()
{
  write(1, "\r", 1);
  write(1, state, length(state));
  waitALittleBit();
}

void		predictorPredictMoves()
{
  predictorPredictStarMove();
  predictorPredictTextMove();
}

void		controllerExecuteMoves()
{
  controllerExecuteStarPrediction();
  controllerExecuteTextPrediction();
}

void		appMain()
{
  appPrepareTheAnimation(30, "LifeIsBeautiful");
  while (textLength)
    {
      presenterPresentState();
      screenDisplayState();
      predictorPredictMoves();
      controllerExecuteMoves();
    }
}

int		main()
{
  // predictor

  testAllStarMovePredictions();
  predictorShouldPredictTextDoNotMove();
  predictorShouldPredictTextMoveRight();
  predictorShouldPredictTextMoveLeft();
  predictorShouldPredictTextDropsLastCharacter();
  predictorShouldPredictTextDropsFirstCharacter();
  
  // controller 

  controllerShouldPrepareStarActions();
  controllerShouldPrepareTextActions();
  controllerShouldMoveStarRight();
  controllerShouldMoveStarLeft();
  controllerShouldMakeStarHitSomethingAndMoveLeft();
  controllerShouldMakeStarHitSomethingAndMoveRight();
  controllerShouldNotMakeStarMove();
  controllerShouldSpawnStarRight();
  controllerShouldSpawnStarLeft();
  controllerShouldNotMakeTextMove();
  controllerShouldMoveTextRight();
  controllerShouldMoveTextLeft();
  controllerShouldMakeTextDropLastCharacter();
  controllerShouldMakeTextDropFirstCharacter();

  // presenter
  
  presenterShouldPrepareState();

  // app

  appShouldPrepareTheAnimation();
  appMain();

  return (0);
}
