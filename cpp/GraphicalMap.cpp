#include	<stdlib.h>
#include	"GraphicalMap.h"

GraphicalMap::GraphicalMap(Map *map)
{
  itsImageSize = map->getSize() + 2;
  itsImagePosition = 0;
  itsImage = (char *) malloc(itsImageSize);
  for (int i = 0; i < itsImageSize - 2; i++)
    {
      itsImage[i] = ' ';
    }
  itsImage[itsImageSize - 1] = '|';
  itsImage[itsImageSize] = '\0';
}

char *		GraphicalMap::getImage()
{
  return (itsImage);
}

int		GraphicalMap::getImageSize()
{
  return (itsImageSize);
}

int		GraphicalMap::getImagePosition()
{
  return (itsImagePosition);
}
