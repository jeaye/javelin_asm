CXX = clang++
CXX_FLAGS += -std=c++1y -Iinclude -Ilib/jtl/include

OUT_DIR = bin
TARGET = jsm

all:
	mkdir -p ${OUT_DIR}
	${CXX} ${CXX_FLAGS} -o ${OUT_DIR}/${TARGET} src/main.cpp

.SILENT: 

.PHONY: all
