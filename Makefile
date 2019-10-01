
cc = gcc
CFLAGS= -lX11

DEMO_TARGET=demo
DEMO_SOURCE=xm.h xm-print.h xm-event.h demo.c xm-event.c xm-print.c xm.c

DEMO_DIV=demo_div
DEMO_DIV_SOURCE=xm.h demo_div.c xm.c

TARGET_ALL=${DEMO_TARGET} ${DEMO_DIV}

all:${TARGET_ALL}

${DEMO_TARGET}: ${DEMO_SOURCE}
	cc -o ${DEMO_TARGET} ${DEMO_SOURCE} ${CFLAGS}

${DEMO_DIV}: ${DEMO_DIV_SOURCE}
	cc -o ${DEMO_DIV} ${DEMO_DIV_SOURCE} ${CFLAGS}

clean:
	rm -rf ${TARGET_ALL}
