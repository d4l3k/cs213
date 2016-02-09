CFLAGS += -std=gnu11
EXES   =  stack p2
OBJS   =  stack.o p2.o list.o tree.o

all: $(EXES)

stack: stack.o
p2: p2.o list.o tree.o

clean:
	rm -f $(EXES) $(OBJS)
tidy:
	rm -f $(OBJS)