#include	"UpdateManager.h"

UpdateManager::UpdateManager(Movable *movable)
{
  itsItemToMove = movable;
}

void		UpdateManager::manageUpdate()
{
  itsItemToMove->moveRight();
}
