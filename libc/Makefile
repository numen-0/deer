DEFAULT_HOST?=i386
HOST?=DEFAULT_HOST
HOSTARCH?=i386

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib
BUILDDIR=../build/libc

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS=\
$(ARCH_FREEOBJS) \
$(patsubst %.c,$(BUILDDIR)/%.o,$(wildcard stdio/*.c)) \
$(patsubst %.c,$(BUILDDIR)/%.o,$(wildcard stdlib/*.c)) \
$(patsubst %.c,$(BUILDDIR)/%.o,$(wildcard string/*.c)) \

HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \

LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

#BINARIES=libc.a libk.a # Not ready for libc yet.
BINARIES=$(BUILDDIR)/libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .S

all: $(BINARIES)

$(BUILDDIR)/libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

$(BUILDDIR)/libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.libk.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

$(BUILDDIR)/%.libk.o: %.S
	@mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -rf $(BUILDDIR)/*

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
