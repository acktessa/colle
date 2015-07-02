#ifndef		__UPDATE_MANAGER_H__
#define		__UPDATE_MANAGER_H__

#include	"Movable.h"

class		UpdateManager
{
  Movable	*itsItemToMove;

 public:
  UpdateManager(Movable *movable);
  void		manageUpdate();
};

#endif		/*__UPDATE_MANAGER_H__*/
