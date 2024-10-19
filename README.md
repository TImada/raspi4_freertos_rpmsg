# raspi4_freertos_rpmsg

This repository includes a FreeRTOS RPMSG sample application which can run on Raspberry Pi 4B.

## 1. Overview

This sample application is test implementation of ping-pong communication between FreeRTOS and Linux running on top of Raspberry Pi 4B.

FreeRTOS (CPU core#3) sends a message to Linux (CPU core#0), then Linux sends it back to FreeRTOS.

| CPU core # | OS        | Role |
|:----------:|:---------:|:----:|
| 0          | Linux     | Pong |
| 3          | FreeRTOS  | Ping |

A used communication protocol is [RPMSG](https://github.com/OpenAMP/open-amp/wiki/RPMsg-Communication-Flow) in [OpenAMP](https://github.com/OpenAMP/open-amp/wiki/OpenAMP-Overview), one of shared-memory based communication protocols between remote processors. This implementation uses one of ARM Mailboxes implemented in BCM2711 to generate interrupts between two CPU cores.

You can find Raspberry Pi 4B specific code at [libmetal](https://github.com/TImada/libmetal/tree/05e0e0511c0ac29ff658ff6d3a08a060e95ae7af/lib/system/freertos/raspi4) and [open-amp](https://github.com/TImada/open-amp/tree/a18533e2a45c93f4be15198527a16823d66c52d4/apps/machine/raspi4). Both the libraries are based on the tag `v2020.04.0`.

## 2. How to build

### FreeRTOS (rpmsg_ping)

Follow [this instruction](https://github.com/TImada/raspi4_freertos_rpmsg/blob/master/docs/freertos_build.md).

### Linux (rpmsg_echo)

Follow [this instruction](https://github.com/TImada/raspi4_freertos_rpmsg/blob/master/docs/linux_build.md).

## 3. How to run

Basically this step is quite similar to the step done for the FreeRTOS UART sample.

(1) Follow [Launching FreeRTOS and Linux](https://github.com/TImada/raspi4_freertos#5-launching-freertos-and-linux) for the UART sample. You must build and execute the RPMSG sample. So the target directory is `raspi4_freertos_rpmsg/samples/freertos/rpmsg_ping/` and you will obtain `rpmsg_ping.elf` (FreeRTOS RPMSG sample). :-)

(2) Make sure that Linux finishes booting up completely at this time.

(3) Make sure that the libmetal/open-amp library installtion path (`/usr/local/lib` in default) is configured on your Linux shell. Add it to `${LD_LIBRARY_PATH}` if it is missing.

```
$ echo ${LD_LIBRARY_PATH}
/usr/local/lib
```

(4) Then, move to the `rpmsg_echo` build directory on your Raspberry Pi 4B, then launch `rpmsg_echo.elf`.

```
$ cd raspi4_freertos_rpmsg/samples/linux/rpmsg_echo/build
$ sudo ./rpmsg_echo
```

You will see the FreeRTOS output at UART2 below.
```
Waiting until Linux starts booting up ...

****************************

   FreeRTOS RPMSG Sample

  (This sample uses UART2)

****************************
Successfully intialized remoteproc.
Calling mmap resource table.
Successfully mmap resource table.
Calling mmap shared memory.
Successfully mmap the buffer region.
Initialize remoteproc successfully.
creating remoteproc virtio
Initializing rpmsg vdev
 1 - Send data to remote core, retrieve the echo and validate its integrity ..
new endpoint notification is received.
RPMSG endpoint is binded with remote.
sending payload number 0 of size 17
echo test: sent : 17
received echo data number 0 of size 17

sending payload number 1 of size 18
echo test: sent : 18
received echo data number 1 of size 18

...
...
...

sending payload number 479 of size 496
echo test: sent : 496
received echo data number 479 of size 496

sending a message for shutdown
**********************************
 Test Results: Error count = 0
**********************************
Quitting application .. Echo test end
Stopping application...
```

You will also see the Linux output at UART1 below.

```
imada@ubuntu:~/raspi4_freertos_rpmsg/samples/linux/rpmsg_echo/build$ sudo ./rpmsg_echo
Starting application...
metal: info:      metal_uio_dev_open: No IRQ for device 40041000.gic_uio.
metal: info:      metal_uio_dev_open: No IRQ for device 20600000.shm.
Successfully intialized remoteproc.
Calling mmap resource table.
Successfully mmap resource table.
Calling mmap shared memory.
Successfully mmap the buffer region.
Initialize remoteproc successfully.
creating remoteproc virtio
Initializing rpmsg vdev
Try to create rpmsg endpoint.
Successfully created rpmsg endpoint.
received data from FreeRTOS over RPMSG, size = 17
echo message number 0

received data from FreeRTOS over RPMSG, size = 18
echo message number 1

...
...

received data from FreeRTOS over RPMSG, size = 496
echo message number 479

Received a shutdown message
Stopping application...
```

## 4. Debugging

Follow the [Debugging](https://github.com/TImada/raspi4_freertos#6-debugging) section for the FreeRTOS UART sample. You can use the same scheme to debug the FreeRTOS RPMSG sample.

For the Linux sample debugging, please use `gdb`!
