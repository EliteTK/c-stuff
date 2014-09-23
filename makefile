CFLAGS = -O2 -std=c11

all:
	echo "You did it wrong, you're supposed to give me a file to compile."

% : %.c
	$(CC) $(CFLAGS) -o $@ $^
