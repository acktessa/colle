#ifndef		__DISPLAYABLE_H__
#define		__DISPLAYABLE_H__

class		Displayable
{
 public:
  virtual ~Displayable(){};
  virtual char *getImage() = 0;
  virtual int	getImageSize() = 0;
  virtual int	getImagePosition() = 0;
};

#endif		/*__DISPLAYABLE_H__*/
