# Makefile for nbench, December 11, 1997, Uwe F. Mayer <mayer@tux.org>
# Updated February 18, 2003

default: nbench

##########################################################################
#   If you are using gcc-2.7.2.3 or earlier:
#   The optimizer of gcc has a bug and in general you should not specify
#   -funroll-loops together with -O (or -O2, -O3, etc.)
#   This bug is supposed to be fixed with release 2.8 of gcc.
#
#   This bug does NOT seem to have an effect on the correct compilation
#   of this benchmark suite on my Linux box. However, it leads to
#   the dreaded "internal compiler error" message on our alpha
#   running DEC Unix 4.0b. The Linux-binary that was used to obtain
#   the baseline results was nevertheless compiled with
#   CFLAGS = -s -static -Wall -O3 -fomit-frame-pointer -funroll-loops
#
# You should leave -static in the CFLAGS so that your sysinfo can be
# compiled into the executable.

LLVM_PATH = #use your llvm path here
LLVM_BIN_PATH = $(LLVM_PATH)/build/bin
CFIHello_So_PATH = $(LLVM_PATH)/build/lib/LLVMCFIHello.so
CCA = $(LLVM_PATH)/build/bin/clang

CC2 = clang
CC1 = $(LLVM_PATH)/build/bin/clang

# generic options for gcc
CFLAGS2 = -s -static -Wall -O3
CFLAGS1 = -s -static -Wall -fPIC -fno-asynchronous-unwind-tables -fno-addrsig -mstackrealign -Xclang -load -Xclang $(CFIHello_So_PATH)

# if your gcc lets you do it, then try this one
#CFLAGS = -s -static -Wall -O3 -fomit-frame-pointer -funroll-loops

# for gcc on an older Pentium type processor you can try the following
#CFLAGS = -s -static -O3 -fomit-frame-pointer -Wall -m486 \
#	-fforce-addr -fforce-mem -falign-loops=2 -falign-functions=2 \
#	-falign-jumps=2 -funroll-loops

# for a newer gcc on a newer Pentium type processor you can try the following
#CFLAGS = -s -static -O3 -fomit-frame-pointer -Wall -march=i686 \
#	-fforce-addr -fforce-mem -falign-loops=2 -falign-functions=2 \
#	-falign-jumps=2 -funroll-loops

# for a newer gcc on an Athlon XP type processor you can try the following
#CFLAGS = -s -static -O3 -fomit-frame-pointer -Wall -march=athlon-xp \
#	-fforce-addr -fforce-mem -falign-loops=2 -falign-functions=2 \
#	-falign-jumps=2 -funroll-loops

# For debugging using gcc
#CFLAGS = -g -O3 -Wall -DDEBUG

##########################################################################
# For Linux machines with more than one binary format.
# The default binaries, depends on your system whether it's elf or aout.
MACHINE=
# a.out code for linux on an elf machine
#MACHINE= -bi486-linuxaout
# elf code for linux on an a.out machine
#MACHINE= -bi486-linuxelf
# if you want a different compiler version and different binaries, for example
#MACHINE= -V2.7.2 -bi486-linuxaout

##########################################################################
# Read the file README.nonlinux if you are not using Linux

# for DEC Unix using cc you can try
#CC = cc
#CFLAGS = -O3
#LINKFLAGS = -s -non_shared

# for SunOS using cc
#CC = cc
#CFLAGS = -O3 -s

# for DEC Ultrix using cc
#CC = cc
#CFLAGS = -O2
#LINKFLAGS = -s

# for a Mac with OsX and the Darwin environment
#CC = cc
#CFLAGS = -O3 -DOSX

# For debugging using cc
#CC = cc
#CFLAGS = -g -DDEBUG

##########################################################################
# If your system does not understand the system command "uname -s -r"
# then comment this out

# NO_UNAME= -DNO_UNAME

##########################################################################
# For any Unix flavor you need -DLINUX
# You also need -DLINUX to get the new indices

DEFINES= -DLINUX $(NO_UNAME)

##########################################################################
# For LINUX-like systems with gcc
sysinfoc.c: Makefile
	./sysinfo.sh $(CC2) $(MACHINE) $(DEFINES) $(CFLAGS2)

sysinfo.c: Makefile
	./sysinfo.sh $(CC2) $(MACHINE) $(DEFINES) $(CFLAGS2)

##########################################################################
# For non-LINUX systems
# Edit the files sysinfo.c and sysinfoc.c to include your system information
# and take sysinfo.c and sysinfoc.c out of the dependencies for nbench0.o

hardware.o: hardware.c hardware.h Makefile
	$(CC2) $(MACHINE) $(DEFINES) $(CFLAGS2)\
		-c hardware.c 

emfloat.o: emfloat.h emfloat.c nmglobal.h pointer.h Makefile
	$(CC2) $(MACHINE) $(DEFINES) $(CFLAGS2)\
		-c emfloat.c

pointer.h: pointer
	$(CC2) $(MACHINE) $(DEFINES) $(CFLAGS2)\
		-o pointer pointer.c
	rm -f pointer.h
	if [ "4" = `./pointer` ] ; then touch pointer.h ;\
	else echo "#define LONG64" >pointer.h ; fi

misc.o: misc.h misc.c Makefile
	$(CC2) $(MACHINE) $(DEFINES) $(CFLAGS2)\
		-c misc.c

sysspec.o: sysspec.h sysspec.c nmglobal.h pointer.h Makefile
	$(CC2) $(MACHINE) $(DEFINES) $(CFLAGS2)\
		-c sysspec.c

# nbench1.o: nbench1.h nbench1.c wordcat.h nmglobal.h pointer.h Makefile
# 	$(CC2) $(MACHINE) $(DEFINES) $(CFLAGS2)\
# 		-c nbench1.c

# nbench0.s: nbench0.h nbench0.c nmglobal.h pointer.h hardware.h\
# 	   Makefile sysinfo.c sysinfoc.c
# 	$(CC1) $(MACHINE) $(DEFINES) $(CFLAGS1)\
# 		-S nbench0.c

# nbench0.o: nbench0.s
# 	$(CC1) nbench0.s -c -o nbench0.o
# 	@fallocate -l 4M ssblob
# 	@objcopy --add-section .ssblob=ssblob --set-section-flags .ssblob=alloc,data,code nbench0.o

TARGET_NAME = mynbench1

mynbench.s: nbench0.h $(TARGET_NAME).c nmglobal.h pointer.h hardware.h\
	   Makefile sysinfo.c sysinfoc.c
	$(CC1) $(MACHINE) $(DEFINES) $(CFLAGS1)\
		-S $(TARGET_NAME).c -o mynbench.s

mynbench.o: mynbench.s
	$(CC2) mynbench.s -c -o mynbench.o
	@fallocate -l 4M ssblob
	@objcopy --add-section .ssblob=ssblob --set-section-flags .ssblob=alloc,data,code mynbench.o

nbench: emfloat.o misc.o mynbench.o sysspec.o hardware.o transactionBegin.o
	clang -c transactionBegin.s -o transactionBegin.o
	$(CC2) $(MACHINE) $(DEFINES) $(CFLAGS2) $(LINKFLAGS)\
		emfloat.o misc.o mynbench.o sysspec.o hardware.o transactionBegin.o shadowstack.lds\
		-o nbench -lm

##########################################################################

clean:
	- /bin/rm -f mynbench.s *.o *~ \#* core a.out hello sysinfo.c sysinfoc.c \
		 bug pointer pointer.h debugbit.dat

mrproper: clean
	- /bin/rm -f nbench
