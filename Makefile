# See LICENSE file for copyright and license details.

include config.mk

SRC = calc.c stack.c
OBJ = ${SRC:.c=.o}

all: options calc

options:
	@echo calc build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

calc: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f calc ${OBJ}

install: all
	mkdir -p ${PREFIX}/bin
	cp -f calc ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/calc

uninstall:
	rm -f ${PREFIX}/bin/calc

.PHONY: all options clean install uninstall
