CC=gcc
CGLAGS=-g
OBJS=hashmap
BIN=example
TEST=test/test

all: $(BIN)

test: $(TEST)
	./$(TEST)

%.o: %.c
	$(CC) $(CGLAGS) -c $< -o $@

$(BIN): $(BIN).o $(OBJS).o
	$(CC) $(CGLAGS) $^ -o $@

$(TEST): $(OBJS).o $(TEST).o
	$(CC) $(CGLAGS) $^ -o $@


clean:
	rm -f */*.o *.o $(BIN) $(TEST)