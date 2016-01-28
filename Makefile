SRC=src/receiver.c
SRC2=src/sender.c
SRC3=src/dynamic_broker.c

all: receiver producer dynamic_broker

CFLAGS=`pkg-config libmlm libzyre --cflags`
LDFLAGS=`pkg-config libmlm libzyre --libs`

receiver: $(SRC)
	gcc -g -o receiver $(SRC) $(CFLAGS) $(LDFLAGS)

producer: $(SRC2)
	gcc -g -o producer $(SRC2) $(CFLAGS) $(LDFLAGS)

dynamic_broker: $(SRC3)
	gcc -g -o dynamic_broker $(SRC3) $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf receiver producer dynamic_broker *.o
