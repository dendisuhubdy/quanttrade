#Suffix Rule
.SUFFIXES :
.SUFFIXES : .o .cpp
.cpp.o :
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $<

SELF = basic.mk

CC = g++
#DEBUG = -O2 -Wall
DEBUG = -Wall
CFLAGS = $(DEBUG)
INC_FLAGS = -I./

SDE_WA_SRC =  $(wildcard *.cpp)
SDE_WA_OBJS =  $(SDE_WA_SRC:.cpp=.o)
TARGETS = european_option 

.PHONY: all
all: $(TARGETS)

$(TARGETS): $(SDE_WA_OBJS)
	$(CC) $(SDE_WA_OBJS) -o $@

Makefile : $(SELF)
	rm -f $@
	cp $(SELF) $@
	chmod +w $@
	echo '# Automatically-generated dependencies list:' >>$@
	$(CC) ${CFLAGS} ${INC_FLAGS} -MM	\
	${SDE_WA_SRC}	\
	>> $@
	chmod -w $@

.PHONY: clean
clean :
	rm -f *.o $(TARGETS)

