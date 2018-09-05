CFLAGS = -lm
all: mat
mat: mat.o
	$(CC) $(CFLAGS) -o $@ $@.o
