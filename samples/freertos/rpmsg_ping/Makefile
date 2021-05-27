CROSS ?= aarch64-none-elf-

LIBMETAL_PATH ?= ${RPMSG_TOP}/libmetal
OPENAMP_PATH ?= ${RPMSG_TOP}/open-amp

LIB_PATH = -L$(LIBMETAL_PATH)/build/lib \
           -L$(OPENAMP_PATH)/build/lib

LIBS = -lmetal -lopen_amp

CFLAGS = -mcpu=cortex-a72 \
         -fPIC \
         -ffreestanding \
         -std=gnu99 \
         -O2 \
         -Wall \
         -Wextra \
         -DGUEST \
         -D__LINUX__ \
         -I$(INCLUDEPATH1) \
         -I$(INCLUDEPATH2) \
         -I$(INCLUDEPATH3) \
         -I$(INCLUDEPATH4) \
         -I$(INCLUDEPATH5) \
         -I$(INCLUDEPATH6) \
         -I$(INCLUDEPATH7) \
         -I$(INCLUDEPATH8)
BUILTIN_OPS = -fno-builtin-memset
ASMFLAGS = -mcpu=cortex-a72

INCLUDEPATH1 ?= ./src
INCLUDEPATH2 ?= ../musl_libc
INCLUDEPATH3 ?= ../mmu
INCLUDEPATH4 ?= ../../../Source/include
INCLUDEPATH5 ?= ../../../Source/portable/GCC/ARM_CA72_64_BIT
INCLUDEPATH6 ?= $(LIBMETAL_PATH)/build/lib/include
INCLUDEPATH7 ?= $(OPENAMP_PATH)/lib/include
INCLUDEPATH8 ?= $(OPENAMP_PATH)/apps/machine/raspi4

# From ./src
OBJS = build/startup.o 
OBJS +=build/FreeRTOS_asm_vector.o
OBJS +=build/FreeRTOS_tick_config.o
OBJS +=build/helper.o
OBJS +=build/interrupt.o
OBJS +=build/main.o
OBJS +=build/mmu_cfg.o
OBJS +=build/printf.o
OBJS +=build/rpmsg-ping.o
OBJS +=build/uart.o

# From ../mmu
OBJS +=build/mmu.o

# From ../cache
OBJS +=build/cache.o

# From ../musl_libc
OBJS +=build/memset.o
OBJS +=build/memcpy.o

# From $(OPENAMP_PATH)/apps/machine/raspi4
OBJS +=build/platform_info.o
OBJS +=build/raspi4_a72_rproc.o
OBJS +=build/rsc_table.o

# From ../../../Source
OBJS +=build/list.o
OBJS +=build/queue.o
OBJS +=build/tasks.o
OBJS +=build/timers.o

# From ../../../Source/portable/GCC/ARM_CA72_64_BIT
OBJS +=build/port.o
OBJS +=build/portASM.o

# From ../../../Source/portable/MemMang
OBJS +=build/heap_1.o

rpmsg.elf : src/raspberrypi4.ld $(OBJS)
	$(CROSS)gcc -Wl,--build-id=none -std=gnu99 -T src/raspberrypi4.ld -o $@ -ffreestanding --specs=rdimon.specs $(BUILTIN_OPS) $(OBJS) $(LIB_PATH) $(LIBS)
	$(CROSS)objdump -d rpmsg.elf > rpmsg.list

build/%.o : src/%.S
	$(CROSS)as $(ASMFLAGS) -c -o $@ $<
	
build/%.o : src/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : ../mmu/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : ../cache/%.S
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : ../musl_libc/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : $(OPENAMP_PATH)/apps/machine/raspi4/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : ../../../Source/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : ../../../Source/portable/GCC/ARM_CA72_64_BIT/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : ../../../Source/portable/GCC/ARM_CA72_64_BIT/%.S
	$(CROSS)as $(ASMFLAGS) -c -o $@ $<

build/%.o : ../../../Source/portable/MemMang/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

clean :
	rm -f build/*.o
	rm -f *.elf
	rm -f *.list

