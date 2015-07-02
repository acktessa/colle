#include	"Screen.h"
#include	"GraphicalMap.h"
#include	"GraphicalStar.h"
#include	"DisplayManager.h"
#include	"UpdateManager.h"
#include	"TimeManager.h"

int		main()
{
  
  Displayer	*scr = new Screen(100);
  
  //map
  Map		*m = new Map(10);
  Displayable	*gm = new GraphicalMap(m);

  //star
  Star		*s = new Star();
  Displayable	*gs1 = new GraphicalStar(s);

  Movable	*movable = s;
  movable->moveRight();
  Displayable	*gs2 = new GraphicalStar(s);

  //manager
  DisplayManager *dm = new DisplayManager(scr);
  UpdateManager	 *um = new UpdateManager(movable);
  TimeManager	*tm = new TimeManager();

  dm->addItem(gm);
  dm->addItem(gs1);
  dm->addItem(gs2);
  while (1)
    {
      dm->manageDisplay();
      um->manageUpdate();
      tm->manageTime();
    }
  return (0);
}
