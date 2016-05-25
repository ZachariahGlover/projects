CURPATH=
SFMLPATH=$(CURPATH)SFML-2.2/
CFLAGS=-Wall
INCLUDEPATH=-I $(SFMLPATH)include
LIBPATH=-L $(SFMLPATH)lib
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
ALL=$(CFLAGS) $(INCLUDEPATH) $(LIBPATH) $(LIBS)

all: rebuild

object.o: src/object.cpp src/object.h src/utils.h
	g++ $(ALL) -c src/object.cpp

camera.o: src/camera.cpp src/camera.h
	g++ $(ALL) -c src/camera.cpp

utils.o: src/utils.cpp src/utils.h
	g++ $(ALL) -c src/utils.cpp

game.o: src/game.cpp src/game.h src/utils.h src/camera.h src/object.h
	g++ $(ALL) -c src/game.cpp

game: game.o utils.o camera.o object.o
	g++ *.o $(ALL) -o game

preclean:
	rm -f *.o game

postclean:
	rm -f *.o

rebuild: preclean game postclean