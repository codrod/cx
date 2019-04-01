CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -Llib
LDLIBS = -lcx -lpthread

AR = ar
ARFLAGS = crv

INCLUDES = include/cxdef.h include/cxerr.h include/cxex.h include/cxrt.h include/cxrt_mutex.h include/cxui.h include/cxlib.h include/cxmem.h include/cxstring.h

OBJS = src/cxrt.o src/cxrt_stack.o src/cxrt_mutex_posix.o src/cxex.o src/cxmem.o src/cxmem_storage.o src/cxstring.o src/cxstring_iso.o src/cxui.o #src/cxui_strto_tostr_char.o

TESTS = test/1_cxrt.ct test/2_cxex.ct test/3_cxmem.ct test/4_cxstring.ct test/5_cxstring_iso.ct

%.h: ;

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS) $(LDLIBS)

%.ct: %.c lib/libcx.a
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LDLIBS)

lib/libcx.a: $(OBJS)
	$(AR) $(ARFLAGS) $@ $?

doc: $(INCLUDES)
	doxygen

test: $(TESTS)
	rm -f test.sh
	echo "#!/bin/sh" >> test.sh
	ls test/*.ct -1 >> test.sh
	chmod u+x test.sh

clean:
	rm -fr src/*.o test/*.ct doc/* lib/libcx.a test.sh
