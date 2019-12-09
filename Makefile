CCFLAGS=-std=c++11 -Wall
BUILD_DIR=./build
TARGET=ims-simul

all: _build_dir _link

_link: ${BUILD_DIR}/main.o \
			 ${BUILD_DIR}/Patch.o \
			 ${BUILD_DIR}/Plantation.o \
			 ${BUILD_DIR}/PlantationPatch.o \
			 ${BUILD_DIR}/RainforestPatch.o \
			 ${BUILD_DIR}/RandomGenerator.o \
			 ${BUILD_DIR}/Simulation.o \
			 ${BUILD_DIR}/WoodStorage.o \
			 
	g++ -o ${BUILD_DIR}/${TARGET} $^
	
libs:
	echo ${LIBS}

_build_dir:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}/main.o: src/main.cpp
	g++ ${CFLAGS} $^ -c -o $@
	
${BUILD_DIR}/Patch.o: src/Patch.cpp
	g++ ${CFLAGS} $^ -c -o $@
	
${BUILD_DIR}/Plantation.o: src/Plantation.cpp
	g++ ${CFLAGS} $^ -c -o $@
	
${BUILD_DIR}/PlantationPatch.o: src/PlantationPatch.cpp
	g++ ${CFLAGS} $^ -c -o $@
	
${BUILD_DIR}/RainforestPatch.o: src/RainforestPatch.cpp
	g++ ${CFLAGS} $^ -c -o $@
	
${BUILD_DIR}/RandomGenerator.o: src/RandomGenerator.cpp
	g++ ${CFLAGS} $^ -c -o $@

${BUILD_DIR}/Simulation.o: src/Simulation.cpp
	g++ ${CFLAGS} $^ -c -o $@
	
${BUILD_DIR}/WoodStorage.o: src/WoodStorage.cpp
	g++ ${CFLAGS} $^ -c -o $@
	
clean:
	cd ${BUILD_DIR} && rm *.o && rm ${TARGET}
