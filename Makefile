all : 	main.cpp\
	Displayer.h\
	Screen.h\
	Map.h\
	Map.cpp\
	Displayable.h\
	GraphicalMap.h\
	GraphicalMap.cpp\
	DisplayManager.h\
	DisplayManager.cpp\
	Star.h\
	Star.cpp\
	GraphicalStar.h\
	GraphicalStar.cpp\
	Movable.h\
	UpdateManager.h\
	UpdateManager.cpp\
	TimeManager.h\
	TimeManager.cpp

	g++ main.cpp\
	Screen.cpp\
	Map.cpp\
	GraphicalMap.cpp\
	DisplayManager.cpp\
	Star.cpp\
	GraphicalStar.cpp\
	UpdateManager.cpp\
	TimeManager.cpp

clean :
	rm *~ *#

