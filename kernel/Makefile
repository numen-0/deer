DEFAULT_HOST?=i386
HOST?=DEFAULT_HOST
HOSTARCH?=i386

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
BUILDDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

BUILDDIR := $(BUILDDIR)/kernel

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
$(patsubst %.asm,$(BUILDDIR)/%.o,$(wildcard kernel/*.asm)) \

KERNEL_OBJS:=\
$(filter-out $(BUILDDIR)/kernel/kernel.o, $(KERNEL_OBJS))
KERNEL_OBJS:=\
$(filter-out $(BUILDDIR)/kernel/kernel_entry.o, $(KERNEL_OBJS))

OBJS=\
$(KERNEL_ARCH_OBJS) \
$(KERNEL_OBJS) \

LINK_LIST=\
$(LDFLAGS) \
$(OBJS) \
$(LIBS) \

TARGET_FOOT := deer.kernel.foot
TARGET_GRUB := deer.kernel.grub

.PHONY: clean install-foot install-grub install-headers
.SUFFIXES: .o .c .S

$(BUILDDIR)/$(TARGET_FOOT): $(BUILDDIR)/kernel/kernel_entry.o $(BUILDDIR)/kernel/kernel.o
	$(LD) -m elf_i386 -o $@ -Ttext 0x1000 $^ \
		--entry=_kernel_start --oformat binary

# ugly stuff, I hate myself
$(BUILDDIR)/$(TARGET_GRUB): $(BUILDDIR)/kernel/kernel.o $(BUILDDIR)/kernel/kernel_entry.o $(OBJS)
	@mkdir -pv $(dir $@)
	$(CC) -T $(ARCHDIR)/grub_linker.ld -o $@ $(CFLAGS) $(LINK_LIST) \
		$< $(BUILDDIR)/../bootloader/grub/grub_boot_loader.o
	@mkdir -pv $(DESTDIR)$(BOOTDIR)
	@cp -v $@ $(DESTDIR)$(BOOTDIR)/deer.kernel

$(BUILDDIR)/%.o: %.c
	@mkdir -pv $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: %.asm
	@mkdir -pv $(dir $@)
	$(AS) -f elf32 -w+all -D__is_kernel -Iinclude -o $@ $<

clean:
	rm -fr $(BUILDDIR)/*

install-foot: install-headers $(BUILDDIR)/$(TARGET_FOOT)

install-grub: install-headers $(BUILDDIR)/$(TARGET_GRUB)

install-headers:
	@mkdir -vp $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

.FORCE: ;

-include $(OBJS:.o=.d)
