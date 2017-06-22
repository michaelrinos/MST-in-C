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
CLIBFLAGS =	-lm -z muldefs


########## End of flags from header.mak


CPP_FILES =	
C_FILES =	Minimum_Spanning_Tree.c Node.c Maze.c hash.c table.c Edge.c Heap.c
PS_FILES =	
S_FILES =	
H_FILES =	Node.h Maze.h hash.h table.h Edge.h Heap.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES = hash.o Maze.o Node.o table.o Edge.o Heap.o
	
#
# Main targets
#

all:	MST test_table test_node test_heap test_edge test_maze

MST: 	Minimum_Spanning_Tree.o $(OBJFILES)
	$(CC) $(CFLAGS) -o MST Minimum_Spanning_Tree.o $(OBJFILES) $(CLIBFLAGS)

test_table: test_table.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test_table test_table.o $(OBJFILES) $(CLIBFLAGS)

test_node: test_node.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test_node test_node.o $(OBJFILES) $(CLIBFLAGS)

test_heap: test_heap.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test_heap test_heap.o $(OBJFILES) $(CLIBFLAGS)

test_maze: test_maze.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test_maze test_maze.o $(OBJFILES) $(CLIBFLAGS)

test_edge: test_edge.o $(OBJFILES)
	$(CC) $(CFLAGS) -o test_edge test_edge.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

hash.o:     hash.h Node.h
Maze.o:     Maze.h hash.h
Node.o:     Node.h table.h
Heap.o:     Heap.h Node.h table.h
Edge.o:     Edge.h
table.o:    table.h
test_heap.o:    Heap.h
test_maze.o:    Maze.h
test_edge.o:    Edge.h
test_node.o:    hash.h Node.h
test_table.o:   hash.h table.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) Minimum_Spanning_Tree.o test_node.o test_table.o test_heap.o test_edge.o test_maze.o

realclean:        clean
	-/bin/rm -f MST Hashtable test_table test_node test_heap test_edge test_maze





