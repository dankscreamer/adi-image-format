CC = clang
CFLAGS = -Wall -Wextra -std=c17

LIB_OBJS = write_adi.o read_adi.o
IMPORT_OBJS = adi_import.o $(LIB_OBJS)
TEST_OBJS = test_adi.o $(LIB_OBJS)

all: adi_import test_adi

adi_import: $(IMPORT_OBJS)
	$(CC) $(CFLAGS) $(IMPORT_OBJS) -o adi_import

test_adi: $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o test_adi

%.o: %.c adi.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o adi_import test_adi


