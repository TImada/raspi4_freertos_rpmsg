# How to build (Linux)

## 1. Clone FreeRTOS RPMSG sample

```
$ cd ${RASPI4_BASE}
$ git clone --recursive https://github.com/TImada/raspi4_freertos_rpmsg
$ ls ./
raspi4_freertos_rpmsg
```

## 2. Compile libmetal and open-amp libraries

This step should be done on 64-bit Ubuntu/Debian Linux running on Raspberry Pi 4B.

At first, you should insall `gcc`, `make`, `cmake` and `libsysfs-dev`.

```
$ sudo apt-get install gcc make cmake libsysfs-dev
```

Then, move to the libmetal directory and install libmetal.

```
$ cd raspi4_freertos_rpmsg/libmetal
$ mkdir build && cd build
$ cmake ..
$ make VERBOSE=1
$ sudo make VERBOSE=1 install
```

(libmetal will be installed into `/usr/local/lib`)

At last, move to the open-amp directory and install open-amp.

```
$ cd raspi4_freertos_rpmsg/libmetal
$ mkdir build && cd build
$ cmake .. -DCMAKE_INCLUDE_PATH=/usr/local/include -DCMAKE_LIBRARY_PATH=/usr/local/lib
$ make VERBOSE=1
$ sudo make VERBOSE=1 install
```

(libopen_amp will be installed into `/usr/local/lib`)

## 3. Compile Linux RPMSG sample

```
cd raspi4_freertos_rpmsg/samples/linux/rpmsg_echo/build
make
```

(`rpmsg_echo` will be created in the samle build directory)
