# How to build (FreeRTOS)

## 1. Create a dedicated directory

```
$ mkdir raspi4 && cd raspi4
$ export RASPI4_BASE=${PWD}
```

## 2. Clone FreeRTOS UART sample repository

Clone it on the dedicated directory. It also includes FreeRTOS kernel.

You should try this UART sample before you move to the next step. You can have your own environment for application building. :-)

At least, you need to finish [compiler setting and u-boot build](https://github.com/TImada/raspi4_freertos#2-prerequisites) at this point.

```
$ cd ${RASPI4_BASE}
$ git clone https://github.com/TImada/raspi4_freertos.git
```

## 3. Clone FreeRTOS RPMSG sample

Clone it on the dedicated directory too. Therefore, you should see both `raspi4_freertos` and `raspi4_freertos_rpmsg`.

```
$ cd ${RASPI4_BASE}
$ git clone --recursive https://github.com/TImada/raspi4_freertos_rpmsg
$ ls ./
raspi4_freertos raspi4_freertos_rpmsg
```

## 4. Compile libmetal and open-amp libraries

Make sure that your environment has `make` and `cmake` commands. Install them before you start compiling.

(For libmetal)
```
$ cd ${RASPI4_BASE}/libmetal
$ mkdir build && cd build
$ make ../ -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/raspi4-freertos.cmake -DCMAKE_C_FLAGS="-I${RASPI4_BASE}/raspi4_freertos/FreeRTOS/Source/include -I${RASPI4_BASE}/raspi4_freertos/FreeRTOS/Source/portable/GCC/ARM_CA72_64_BIT -I${RASPI4_BASE}/raspi4_freertos_rpmsg/samples/freertos/rpmsg_ping/src -O2 -g3"
$ make VERBOSE=1
```

(`CROSS_PREFIX` in `${RASPI4_BASE}/libmetal/cmakes/platforms/raspi4-freertos.cmake` must be changed depending on a compiler you installed)

(For open-amp)
```
$ cd ${RASPI4_BASE}/open-amp
$ mkdir build && cd build
$ cmake ../ -DCMAKE_TOOLCHAIN_FILE=../cmake/platforms/raspi4_a72_generic.cmake -DLIBMETAL_INCLUDE_DIR=../../libmetal/build/lib/include -DLIBMETAL_LIB=../../libmetal/build/lib/libmetal.a -DCMAKE_C_FLAGS="-I${RASPI4_BASE}/raspi4_freertos/FreeRTOS/Source/include -I${RASPI4_BASE}/raspi4_freertos/FreeRTOS/Source/portable/GCC/ARM_CA72_64_BIT -I${RASPI4_BASE}/raspi4_freertos_rpmsg/samples/freertos/rpmsg_ping/src -O2 -g3"
$ make VERBOSE=1
```

(`CROSS_PREFIX` in `${RASPI4_BASE}/open-amp/cmakes/platforms/raspi4_a72_generic.cmake` must be changed depending on a compiler you installed)

You can remove `-g3` option at the `cmake` execution if you don't need debug information.

## 5. Compile FreeRTOS RPMSG sample

```
$ cd ${RASPI4_BASE}/raspi4_freertos_rpmsg/samples/freertos/rpmsg_ping
$ make CROSS=aarch64-none-elf-
```

(`CROSS` must be changed depending on a compiler you installed)
