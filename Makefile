CFLAGS = -O3 -lm
BIGFLAGS = -DSXVE
all: mat lmat
mat: mat.o
	$(CC) $(CFLAGS) -o $@ $<
lmat: mat.c
	$(CC) $(CFLAGS) $(BIGFLAGS) -o $@ $< 
clean:
	/bin/rm -f mat lmat amat apmat alpmat ftrace.out mat.o 
