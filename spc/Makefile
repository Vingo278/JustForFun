CXX=g++
FLAG=-std=c++11
FLAG+=-Wall
SPC_LIB=spc.cc
SPC_LINK=spc.o
MAIN=main.cc
OUT=spc-run

all:
	$(CXX) -c $(SPC_LIB)
	$(CXX) $(FLAG) -o $(OUT) $(MAIN) $(SPC_LINK)
	-./build_rootfs.sh

clean:
	-rm *.o $(OUT)
	-rm -rf ./rootfs
