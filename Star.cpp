#include	"Star.h"

Star::Star()
{
  itsPosition = 0;
}

int		Star::getPosition()
{
  return (itsPosition);
}

void		Star::setPosition(int position)
{
  itsPosition = position;
}

void		Star::moveRight()
{
  itsPosition++;
}
