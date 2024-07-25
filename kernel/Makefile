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
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include
BUILDDIR=../build/kernel

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(patsubst %.c,$(BUILDDIR)/%.o,$(wildcard kernel/*.c)) \
$(patsubst %.S,$(BUILDDIR)/%.o,$(wildcard kernel/*.S))

OBJS=\
$(KERNEL_ARCH_OBJS) \
$(KERNEL_OBJS) \

LINK_LIST=\
$(LDFLAGS) \
$(OBJS) \
$(LIBS) \

TARGET := deer.kernel

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(TARGET): $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(ARCHDIR)/crtbegin.o $(BUILDDIR)/$(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: %.S
	@mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -fr $(BUILDDIR)/*

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: $(BUILDDIR)/$(TARGET)
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $(BUILDDIR)/$(TARGET) $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
