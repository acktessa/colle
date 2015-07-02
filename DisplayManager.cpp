#include	"DisplayManager.h"

DisplayManager::DisplayManager(Displayer *displayer)
{
  itsDisplayer = displayer;
}

void		DisplayManager::addItem(Displayable *d)
{
  itsItemsToDisplay.push_back(d);
}

void		DisplayManager::manageDisplay()
{
  std::vector<Displayable *>::iterator it = itsItemsToDisplay.begin();
  for (it = itsItemsToDisplay.begin(); it != itsItemsToDisplay.end(); ++it)
    {
      itsDisplayer->draw(*it);
    }
  itsDisplayer->display();
}
