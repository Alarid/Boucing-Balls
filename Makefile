export CC = g++
INCPATH = -I./ -I/home/yohann/Documents/Making/SFML/SFML-2.1-sources/include
LIBS = -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lGL -lGLU -lGLEW -lBox2D -L/home/yohann/Documents/Making/SFML/SFML-2.1/lib
export DEFINES =
export FLAGS = -g -std=c++0x $(INCPATH) $(LIBS) $(DEFINES)

export EXEC = Balloons

all: $(EXEC)

.cpp.o:
	$(CC) $(FLAGS) -o "$@" -c "$<" 

.c.o:
	$(CC) $(FLAGS) -o "$@" -c "$<"


$(EXEC) : main.cpp Balloon.o Balloon.hpp const.hpp
	$(CC) $^ $(FLAGS) -o $@


clean:
	@rm -f *.o
	@rm -f $(EXEC)
