DEBUG?=0
ifeq ($(DEBUG), 0)
	BUILD:=-O3
else
	BUILD:=-g
endif

LIBS:=

.PHONY: all install uninstall
all: exe/mxkbc

exe/%: src/%.cpp
	g++ -pedantic -Wall -Wextra $(LIBS) $(BUILD) $^ -o $@

install: exe/mxkbc
	chmod 0755 exe/mxkbc
	chmod 0644 doc/mxkbc.1
	cp exe/mxkbc /usr/bin
	cp doc/mxkbc.1 /usr/share/man/man1

uninstall:
	rm /usr/bin/mxkbc
	rm /usr/share/man/man1/mxkbc.1
