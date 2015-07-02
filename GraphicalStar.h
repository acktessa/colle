#ifndef		__GRAPHICAL_STAR__
#define		__GRAPHICAL_STAR__

#include	"Displayable.h"
#include	"Star.h"	

class		GraphicalStar : public Displayable
{
  char		*itsImage;
  int		itsImageSize;
  int		itsImagePosition;		
  Star		*itsStar;

 public:
  GraphicalStar(Star *star);
  char *getImage();
  int	getImageSize();
  int	getImagePosition();
};

#endif		/*__GRAPHICAL_STAR__*/
