#ifndef		__GRAPHICAL_MAP_H__
#define		__GRAPHICAL_MAP_H__

#include	"Displayable.h"
#include	"Map.h"

class		GraphicalMap : public Displayable
{
  char		*itsImage;
  int		itsImageSize;
  int		itsImagePosition;		
  
 public:
  GraphicalMap(Map *map);
  char *getImage();
  int	getImageSize();
  int	getImagePosition();
};

#endif		/*__GRAPHICAL_MAP_H__*/
