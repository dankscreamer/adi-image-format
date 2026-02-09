CC = clang
CFLAGS = -Wall -Wextra -std=c17

OBJS = write_adi.o read_adi.o test_adi.o

test_adi: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test_adi

%.o: %.c adi.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test_adi

