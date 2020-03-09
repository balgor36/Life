FLAGS=-Wall -lncurses -pg -g
TARGET=life

.PHONY: clean

all: life obj bot food
	g++ $(FLAGS) life.o obj.o bot.o food.o -o $(TARGET)

life: life.cpp
	g++ $(FLAGS) -c -o life.o life.cpp

obj: obj.cpp
	g++ $(FLAGS) -c -o obj.o obj.cpp

bot: bot.cpp
	g++ $(FLAGS) -c -o bot.o bot.cpp

food: food.cpp
	g++ $(FLAGS) -c -o food.o food.cpp

clean:
	rm -rf *.o $(TARGET)
