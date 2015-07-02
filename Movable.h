#ifndef		__MOVABLE_H__
#define		__MOVABLE_H__

class		Movable
{
 public:
  virtual ~Movable(){};
  virtual void	moveRight() = 0;
};

#endif		/*__MOVABLE_H__*/
