# Usage:
# make			# compile everything
# make clean 	# remove all binaries and objects

.PHONY: all setup clean cleanall

COMP = g++
ODIR = obj
SDIR = src
BDIR = bin

SRC := ${wildcard ${SDIR}/*.cpp}
OBJ := ${SRC:${SDIR}/%.cpp=${ODIR}/%.o}
BIN := ${BDIR}/sniffer

all: setup ${OBJ} ${BIN} 

setup: ${SDIR}/
	@if [ ! -d "${ODIR}" ]; then mkdir ${ODIR}; fi
	@if [ ! -d "${BDIR}" ]; then mkdir ${BDIR}; fi

${ODIR}/%.o: ${SDIR}/%.cpp
	${COMP} -c $< -o $@

${BDIR}/%: ${OBJ}
	${COMP} -o $@ $^ -ltins

clean:
	@rm -rvf ${ODIR}

cleanall:
	@rm -rvf ${ODIR}
	@rm -rvf ${BDIR}