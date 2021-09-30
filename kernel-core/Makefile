DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?=-O2 -g
CPPFLAGS?= -O2 -g
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS_NASM:=$(CFLAGS) -Wall
CPPFLAGS_NASM:=$(CPPFLAGS_NASM) -D__is_kernel -Iinclude
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR_INC=include/architecture/$(HOSTARCH)
ARCHDIR_SRC=src/architecture/$(HOSTARCH)

include $(ARCHDIR_INC)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)


include ./src/make.config

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
$(KERNEL_SRC_OBJS) \
src/kernel.o \


OBJS=\
$(ARCHDIR_INC)/crti.o \
$(ARCHDIR_INC)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR_INC)/crtend.o \
$(ARCHDIR_INC)/crtn.o \

LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR_INC)/crti.o \
$(ARCHDIR_INC)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCHDIR_INC)/crtend.o \
$(ARCHDIR_INC)/crtn.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S .asm

all: myos.kernel

myos.kernel: $(OBJS) $(ARCHDIR_INC)/linker.ld
	$(CC) -T $(ARCHDIR_INC)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot myos.kernel

$(ARCHDIR_INC)/crtbegin.o $(ARCHDIR_INC)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=c99 $(CFLAGS) $(CPPFLAGS)

.cpp.o:
	$(CC) -MD -c $< -o $@ -std=c99 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

.asm.o:
	nasm -f elf $< -o $@ $(CFLAGS_NASM)

clean:
	rm -f myos.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: myos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp myos.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)

