BUILDDIR?=

BUILDDIR := $(BUILDDIR)/bootloader

BUILDDIR_FOOT := $(BUILDDIR)/foot
BUILDDIR_GRUB := $(BUILDDIR)/grub

SRCS = $(wildcard foot/*/*.asm)

TARGET_FOOT := foot_boot_loader.bin
TARGET_GRUB := grub_boot_loader.o

.PHONY: clean install-grub install-foot
.SUFFIXES: .o .asm

$(BUILDDIR_FOOT)/$(TARGET_FOOT): foot/boot_loader.asm $(SRCS)
	mkdir -p $(BUILDDIR_FOOT)
	$(AS) $< -f bin -o $@

$(BUILDDIR_GRUB)/$(TARGET_GRUB): grub/boot_loader.asm
	mkdir -p $(BUILDDIR_GRUB)
	$(AS) -felf32 $< -o $@

install-foot: $(BUILDDIR_FOOT)/$(TARGET_FOOT)

install-grub: $(BUILDDIR_GRUB)/$(TARGET_GRUB)

clean:
	rm -fr $(BUILDDIR)/*

