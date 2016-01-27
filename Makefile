SRC=src/receiver.c
SRC2=src/sender.c

all: receiver producer

receiver: $(SRC)
	gcc -g -o receiver $(SRC) -lmlm -lczmq

producer: $(SRC2)
	gcc -g -o producer $(SRC2) -lmlm -lczmq
