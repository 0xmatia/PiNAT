# Usage:
# make			# compile everything
# make clean 	# remove all binaries and objects

.PHONY: all setup clean cleanall debug

COMP = g++
ODIR = obj
SDIR = src
BDIR = bin

BIN := ${BDIR}/pynat.so
SRC = sniffer.cpp pySniffer.cpp pynat.cpp
SRC := ${SRC:%=${SDIR}/%}

DBIN := ${BDIR}/sniffer
DSRC = main.cpp sniffer.cpp
DOBJ := ${DSRC:%.cpp=${ODIR}/%.o}

all: setup ${BIN}

debug: setup ${DBIN}

setup: ${SDIR}/
	@if [ ! -d "${ODIR}" ]; then mkdir ${ODIR}; fi
	@if [ ! -d "${BDIR}" ]; then mkdir ${BDIR}; fi

${BIN}: ${SRC}
	CC=g++ python3 setup.py build --build-temp=${ODIR} && \
	cp build/lib.linux-x86_64-3.6/pynat.cpython-36m-x86_64-linux-gnu.so ${BDIR}/pynat.so && \
	rm -rf build

${ODIR}/%.o: ${SDIR}/%.cpp
	${COMP} -c $< -o $@

${DBIN}: ${DOBJ}
	${COMP} -o $@ $^ -ltins

clean:
	@rm -rvf ${ODIR}

cleanall:
	@rm -rvf ${ODIR}
	@rm -rvf ${BDIR}