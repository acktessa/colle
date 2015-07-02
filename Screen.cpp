#include	<unistd.h>
#include	<stdlib.h>
#include	"Screen.h"

Screen::Screen(int size)
{
  itsSize = size;
  itsImage = (char *) malloc(size);
  for (int i = 0; i < size; i++)
    {
      itsImage[i] = '\0';
    }
}

void		Screen::draw(Displayable *d)
{
  char		*imageToDraw = d->getImage();
  int		imageSize = d->getImageSize();
  int		position = d->getImagePosition();
  int		sourceIndex = 0;
  int		destinationIndex = position;

  for (sourceIndex = 0; sourceIndex < imageSize; sourceIndex++)
    {
      itsImage[destinationIndex] = imageToDraw[sourceIndex];
      destinationIndex++;
    }
  
}

void		Screen::clear()
{
  write(1, "\r", 1);
}

void		Screen::display()
{
  clear();
  write(1, itsImage, itsSize);
}
