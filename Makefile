CC= g++
CFLAGS= -std=c++14 -Wall -w -O2
INCLUDE= -I include/
SFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
THREAD= -lpthread
SOURCE:= $(wildcard source/*.cpp)
EXE= Game

all:	$(EXE)
	./$(EXE)

$(EXE):	
	$(CC) -c $(CFLAGS) $(INCLUDE) $(SOURCE)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCE) -o $(EXE) $(SFML) $(THREAD)

clean:
	rm *.o
	rm $(EXE)
	clear