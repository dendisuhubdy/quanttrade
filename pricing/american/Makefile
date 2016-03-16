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
TARGETS = american_option_fdm 

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

# Automatically-generated dependencies list:
BoundaryCondition.o: BoundaryCondition.cpp BoundaryCondition.h
BoundaryConditionCall.o: BoundaryConditionCall.cpp \
  BoundaryConditionCall.h BoundaryCondition.h
BoundaryConditionPut.o: BoundaryConditionPut.cpp BoundaryConditionPut.h \
  BoundaryCondition.h
CrankNicolson.o: CrankNicolson.cpp CrankNicolson.h \
  FiniteDifferenceScheme.h BoundaryCondition.h
ExplicitFiniteDifference.o: ExplicitFiniteDifference.cpp \
  ExplicitFiniteDifference.h FiniteDifferenceScheme.h
FiniteDifferenceScheme.o: FiniteDifferenceScheme.cpp \
  FiniteDifferenceScheme.h
FiniteDifferences.o: FiniteDifferences.cpp FiniteDifferences.h \
  FiniteDifferenceScheme.h StepCondition.h
ImplicitFiniteDifference.o: ImplicitFiniteDifference.cpp \
  ImplicitFiniteDifference.h FiniteDifferenceScheme.h
PayOff.o: PayOff.cpp PayOff.h
PayOffCall.o: PayOffCall.cpp PayOffCall.h PayOff.h
PayOffPut.o: PayOffPut.cpp PayOffPut.h PayOff.h
StepCondition.o: StepCondition.cpp StepCondition.h
StepConditionAmerican.o: StepConditionAmerican.cpp \
  StepConditionAmerican.h StepCondition.h
StepConditionNull.o: StepConditionNull.cpp StepConditionNull.h \
  StepCondition.h
TridiagonalOperator.o: TridiagonalOperator.cpp TridiagonalOperator.h
