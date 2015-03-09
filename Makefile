CFLAGS = -std=gnu11 -Wall -Wextra 
LDFLAGS = -Wl,--as-needed

ifeq ($(DEBUG), 1)
	CFLAGS += -Og -g
else
	CFLAGS += -O2
endif

INSTALL = install -m755

prefix = /usr/local
bindir = $(prefix)/bin

all:
	@echo 'Error, target not specified.'
	@echo '	To compile <filename>.c	`make <filename>`'
	@echo '	To install <filename>	`make target=<filename> install`'
	@echo '	To uninstall <filename>	`make target=<filename> uninstall`'


$(DESTDIR)$(bindir)/%: %
	$(INSTALL) $^ $(DESTDIR)$(bindir)

install: $(DESTDIR)$(bindir)/$(target)

uninstall:
	$(RM) "$(DESTDIR)$(bindir)/$(target)"

clean:
	find . -mindepth 1 -maxdepth 1 -executable -type f ! -name "prefix_header" -delete

.PHONY : all install uninstall clean
