# How to build (Linux)

This application building should be done on 64-bit Ubuntu/Debian Linux running on top of your Raspberry Pi 4B.

## 1. Clone FreeRTOS RPMSG sample

You should have a newly cloned repository of `raspi4_freertos_rpmsg` which is not used to build the FreeRTOS application described in "[How to build (FreeRTOS)](./freertos_build.md)".

```bash
$ export ${RASPI4_BASE}=${PWD}
$ cd ${RASPI4_BASE}
$ git clone --recursive https://github.com/TImada/raspi4_freertos_rpmsg
$ ls ./
raspi4_freertos_rpmsg
```

## 2. Compile libmetal and open-amp libraries

At first, you should insall `gcc`, `make`, `cmake` and `libsysfs-dev`.

```bash
$ sudo apt-get install gcc make cmake libsysfs-dev
```

Then, move to the libmetal directory and install libmetal.

```bash
$ cd ${RASPI4_BASE}/raspi4_freertos_rpmsg/libmetal
$ mkdir build && cd build
$ cmake ..
$ make VERBOSE=1
$ sudo make VERBOSE=1 install
```

(libmetal will be installed into `/usr/local/lib` as well)

At last, move to the open-amp directory and install open-amp.

```bash
$ cd ${RASPI4_BASE}/raspi4_freertos_rpmsg/open-amp
$ mkdir build && cd build
$ cmake .. -DCMAKE_INCLUDE_PATH=/usr/local/include -DCMAKE_LIBRARY_PATH=/usr/local/lib
$ make VERBOSE=1
$ sudo make VERBOSE=1 install
```

(libopen_amp will be installed into `/usr/local/lib`)

**Do not forget to add `/usr/local/lib` to the `${LD_LIBRARY_PATH}` variable on your shell!**

## 3. Compile Linux RPMSG sample

```bash
$ cd ${RASPI4_BASE}/raspi4_freertos_rpmsg/samples/linux/rpmsg_echo/build
$ make
```

(`rpmsg_echo` will be created in the samle build directory)
