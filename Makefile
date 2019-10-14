
cc = gcc

CFLAGS = -lX11 -g
INCLUDE= -I.

common-obj = xm.o xm-event.o xm-print.o 

demo-obj =  demo.o
demo-obj += demo_div.o
demo-obj += demo_mul.o
demo-obj += demo_center.o

winmov-obj = xm-winmov.o

obj-all  = ${common-obj}
obj-all += ${demo-obj}

quiet-command = $(if $(V),$1,$(if $(2),@echo $2 && $1, @$1))

.PHONY: all demo winmov

all:${obj-all} demo winmov

%.o:%.c
	$(call quiet-command, ${cc} ${CFLAGS} ${INCLUDE} -c -o $@ $<, "  CC    $@")

demo:
	$(call quiet-command, ${cc} -o demo demo.o ${common-obj} ${CFLAGS}, "  LINK  $@")
	$(call quiet-command, ${cc} -o demo_div demo_div.o ${common-obj} ${CFLAGS}, "  LINK  $@_div")
	$(call quiet-command, ${cc} -o demo_mul demo_mul.o ${common-obj} ${CFLAGS}, "  LINK  $@_mul")
	$(call quiet-command, ${cc} -o demo_center demo_center.o ${common-obj} ${CFLAGS}, "  LINK  $@_center")

winmov:
	$(call quiet-command, ${cc} -o winmov xm-winmov.o ${common-obj} ${CFLAGS}, "  LINK  winmov")

clean:
	rm -rf ${obj-all}
	rm -rf demo demo_div demo_mul demo_center
	rm -rf winmov
