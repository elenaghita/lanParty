all: lanParty

lanParty: main.o competition.o team.o node.o queue.o
	gcc -o lanParty main.o competition.o team.o node.o queue.o

main.o: main.c competition.h queue.h
	gcc -c main.c -std=c99 -Wall -g

competition.o: competition.c competition.h
	gcc -c competition.c -std=c99 -Wall -g

team.o: team.c team.h
	gcc -c team.c -std=c99 -Wall -g

node.o: node.c node.h player.h
	gcc -c node.c -std=c99 -Wall -g

queue.o: queue.c queue.h team.h
	gcc -c queue.c -std=c99 -Wall -g

clean:
	rm *.o lanParty
