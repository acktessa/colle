#ifndef		__DISPLAY_MANAGER__
#define		__DISPLAY_MANAGER__

#include	<vector>
#include	"Displayable.h"
#include	"Displayer.h"

class		DisplayManager
{
  Displayer	*itsDisplayer;
  std::vector<Displayable *>	itsItemsToDisplay;

 public:
  DisplayManager(Displayer *displayer);
  void		addItem(Displayable *d);
  void		manageDisplay();
};

#endif		/*__DISPLAY_MANAGER__*/
