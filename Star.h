#ifndef		__STAR_H__
#define		__STAR_H__

#include	"Movable.h"

class		Star : public Movable
{
  int		itsPosition;
  
 public:
  Star();
  int		getPosition();
  void		setPosition(int position);
  void		moveRight();
};

#endif		/*__STAR_H__*/
