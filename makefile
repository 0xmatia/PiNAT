# Usage:
# make			# compile everything
# make clean 	# remove all binaries and objects

.PHONY: all setup clean cleanall debug install

COMP = g++
ODIR = obj
SDIR = src/cpp
BDIR = bin
EDIR = externals

BIN := ${BDIR}/pynat.so
SRC = sniffer.cpp pySniffer.cpp pynat.cpp packetPool.cpp coreFunctions.cpp packet.cpp pyCoreFunctions.cpp
SRC := ${SRC:%=${SDIR}/%}

DBIN := ${BDIR}/sniffer
DSRC = packet.cpp packetPool.cpp coreFunctions.cpp sniffer.cpp main.cpp
DOBJ := ${DSRC:%.cpp=${ODIR}/%.o}

all: setup ${BIN}

debug: setup ${DBIN}

setup: ${SDIR}/
	@if [ ! -d "${ODIR}" ]; then mkdir ${ODIR}; fi
	@if [ ! -d "${BDIR}" ]; then mkdir ${BDIR}; fi

${BIN}: ${SRC}
	CC=g++ python3 setup.py build --build-temp=${ODIR} --build-lib=${BDIR} && \
	mv ${BDIR}/pynat.cpython* ${BDIR}/pynat.so

${ODIR}/%.o: ${SDIR}/%.cpp
	${COMP} -c $< -o $@ -I${EDIR}

${DBIN}: ${DOBJ}
	${COMP} -o $@ $^ -L${EDIR} -ltins

clean:
	@rm -rvf ${ODIR}
	@rm -rvf __pycache__

cleanall:
	@rm -rvf ${ODIR}
	@rm -rvf ${BDIR}
	@rm -rvf __pycache__

install:
	cp ${EDIR}/libtins.so /usr/lib/
	ln -s /usr/lib/libtins.so /usr/lib/libtins.so.4.3