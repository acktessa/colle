#include	"GraphicalStar.h"

#include	<stdlib.h>

GraphicalStar::GraphicalStar(Star *star)
{
  itsImageSize = 1;
  itsImagePosition = star->getPosition();
  itsImage = (char *) malloc(1);
  itsImage[0] = '*';
  itsStar = star;
}

char		*GraphicalStar::getImage()
{
  return (itsImage);
}

int		GraphicalStar::getImageSize()
{
  return (itsImageSize);
}

int		GraphicalStar::getImagePosition()
{
  return (itsStar->getPosition());
}
