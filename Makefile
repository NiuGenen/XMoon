
cc = gcc
CFLAGS= -lX11

DEMO_TARGET=demo
DEMO_SOURCE=xm.h xm-print.h xm-event.h demo.c xm-event.c xm-print.c xm.c

DEMO_DIV=demo_div
DEMO_DIV_SOURCE=xm.h demo_div.c xm.c

DEMO_MUL=demo_mul
DEMO_MUL_SOURCE=xm.h demo_mul.c xm.c

TARGET_ALL=${DEMO_TARGET} ${DEMO_DIV} ${DEMO_MUL}

all:${TARGET_ALL}

${DEMO_TARGET}: ${DEMO_SOURCE}
	cc -o ${DEMO_TARGET} ${DEMO_SOURCE} ${CFLAGS}

${DEMO_DIV}: ${DEMO_DIV_SOURCE}
	cc -o ${DEMO_DIV} ${DEMO_DIV_SOURCE} ${CFLAGS}

${DEMO_MUL}: ${DEMO_MUL_SOURCE}
	cc -o ${DEMO_MUL} ${DEMO_MUL_SOURCE} ${CFLAGS}
	
clean:
	rm -rf ${TARGET_ALL}
