CFLAGS = -std=gnu11 -Wall -Wextra 
LDFLAGS = -Wl,--as-needed

ifeq ($(DEBUG), 1)
	CFLAGS += -Og -g
else
	CFLAGS += -O2
endif

INSTALL = install -Dm755

prefix = /usr/local
bindir = $(prefix)/bin

all:
	@echo 'Error, target not specified.'
	@make --no-print-directory help

help:
	@echo 'Usage:'
	@echo '	To compile <filename>.c	`make <filename>`'
	@echo '	To install <filename>	`make target=<filename> install`'
	@echo '	To uninstall <filename>	`make target=<filename> uninstall`'
	@echo '	To clean up		`make clean`'

$(DESTDIR)$(bindir)/%: %
	$(INSTALL) $^ $(DESTDIR)$(bindir)/$(target)

install: $(DESTDIR)$(bindir)/$(target)

uninstall:
	$(RM) "$(DESTDIR)$(bindir)/$(target)"

clean:
	find . -mindepth 1 -maxdepth 1 -executable -type f ! -name "prefix_header" -delete

-include *.mk

.PHONY : all install uninstall clean
