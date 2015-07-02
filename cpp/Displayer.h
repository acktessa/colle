#ifndef		__DISPLAYER_H__
#define		__DISPLAYER_H__

#include	"Displayable.h"

class		Displayer
{
 public:
  virtual ~Displayer(){};
  virtual void	draw(Displayable *d) = 0;
  virtual void	display() = 0;
};

#endif		/*__DISPLAYER_H__*/
