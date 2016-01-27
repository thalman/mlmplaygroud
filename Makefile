SRC=src/receiver.c

receiver: $(SRC)
	gcc -g -o receiver $(SRC) -lmlm -lczmq
