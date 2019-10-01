
cc = gcc
CFLAGS= -lX11

DEMO_TARGET=demo
DEMO_SOURCE=xm.h xm-print.h xm-event.h demo.c xm-event.c xm-print.c xm.c

TARGET_ALL=${DEMO_TARGET}

all:${TARGET_ALL}

${DEMO_TARGET}: ${DEMO_SOURCE}
	cc -o ${DEMO_TARGET} ${DEMO_SOURCE} ${CFLAGS}

clean:
	rm -rf ${DEMO_TARGET}
