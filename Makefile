SRC=src/receiver.c
SRC2=src/sender.c

all: receiver producer

CFLAGS=`pkg-config libmlm --cflags`
LDFLAGS=`pkg-config libmlm --libs`

receiver: $(SRC)
	gcc -g -o receiver $(SRC) $(CFLAGS) $(LDFLAGS)

producer: $(SRC2)
	gcc -g -o producer $(SRC2) $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf receiver producer *.o
