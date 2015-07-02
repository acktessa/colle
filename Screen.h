#ifndef		__SCREEN_H__
#define		__SCREEN_H__

#include	"Displayer.h"

class		Screen : public Displayer
{
  int		itsSize;
  char		*itsImage;

 public:
  Screen(int size);
  void		draw(Displayable *d);
  void		display();
  void		clear();
};

#endif		/*__SCREEN_H__*/
