CFLAGS = -O2 -std=C11

all:
	echo "You did it wrong, you're supposed to give me a file to compile."

% : %.c
	$(CC) $(CFLAGS) -o $@ $^
