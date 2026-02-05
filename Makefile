CC = clang
CFLAGS = -Wall -Wextra -std=c17

%: %.c
	$(CC) $(CFLAGS) $< -o $@
