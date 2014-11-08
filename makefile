CFLAGS = -Wall -Wextra -Wpedantic -O2 -std=gnu11

PREFIX = /usr
BINDIR = /bin
INSPATH = $(DESTDIR)$(PREFIX)$(BINDIR)

.PHONY : all install uninstall

all:
	@echo 'Error, target not specified.'
	@echo '	To compile <filename>.c	`make <filename>`'
	@echo '	To install <filename>	`make target=<filename> install`'
	@echo '	To uninstall <filename>	`make target=<filename> uninstall`'

% : %.c
	$(CC) $(CFLAGS) -o $@ $^

$(DESTDIR)$(PREFIX)$(BINDIR)/% : %
	install -Dm755 "$^" "$@"

install : $(DESTDIR)$(PREFIX)$(BINDIR)/$(target)

uninstall :
	rm "$(DESTDIR)$(PREFIX)$(BINDIR)/$(target)"

clean :
	find . -mindepth 1 -maxdepth 1 -executable -type f ! -name "prefix_header" -delete
