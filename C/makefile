#
# Created by gmakemake (Ubuntu Jul 25 2014) on Thu Mar  5 22:16:14 2015
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak


# any warning will be considered a compiler error.
CFLAGS =	-ggdb -std=c99 -Wall -Wextra -pedantic -Werror
CLIBFLAGS =	-lm -lbsd


########## End of flags from header.mak


CPP_FILES =	
C_FILES =	Minimum_Spanning_Tree.c Node.c Maze.c hash.c
PS_FILES =	
S_FILES =	
H_FILES =	Node.h Maze.h hash.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES = hash.o Maze.o Node.o
	
#
# Main targets
#

all:	MST

MST: 	Minimum_Spanning_Tree.o $(OBJFILES)
	$(CC) $(CFLAGS) -o MST Minimum_Spanning_Tree.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

Minimum_Spanning_Tree.o: Maze.h
hash.o:     hash.h Node.h
Maze.o:     Maze.h
Node.o:     Node.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) MST.o Hashtable.o

realclean:        clean
	-/bin/rm -f MST Hashtable
