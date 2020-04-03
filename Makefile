# budwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c budwm.c util.c
OBJ = ${SRC:.c=.o}

all: options budwm

options:
	@echo budwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.mk config.h bud.c

budwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f budwm ${OBJ} budwm-${VERSION}.tar.gz

dist: clean
	mkdir -p budwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		budwm.1 drw.h util.h ${SRC} budwm.png transient.c budwm-${VERSION}
	tar -cf budwm-${VERSION}.tar budwm-${VERSION}
	gzip budwm-${VERSION}.tar
	rm -rf budwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f budwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/budwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < budwm.1 > ${DESTDIR}${MANPREFIX}/man1/budwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/budwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/budwm\
		${DESTDIR}${MANPREFIX}/man1/budwm.1

.PHONY: all options clean dist install uninstall
