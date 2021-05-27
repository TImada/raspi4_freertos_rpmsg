CROSS ?= aarch64-none-elf-

COMMON_PATH     = ../../common
FREERTOS_PATH   = ../../../../raspi4_freertos/FreeRTOS
KERNEL_PATH     = $(FREERTOS_PATH)/Source
APP_PATH        = $(FREERTOS_PATH)/Demo/CORTEX_A72_64-bit_Raspberrypi4

LIBMETAL_PATH   = ../../../libmetal
OPENAMP_PATH    = ../../../open-amp

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
         -I$(INCLUDEPATH8) \
         -I$(INCLUDEPATH9)
BUILTIN_OPS = -fno-builtin-memset
ASMFLAGS = -mcpu=cortex-a72

INCLUDEPATH1 = ./src
INCLUDEPATH2 = $(COMMON_PATH)
INCLUDEPATH3 = $(APP_PATH)/musl_libc
INCLUDEPATH4 = $(APP_PATH)/mmu
INCLUDEPATH5 = $(KERNEL_PATH)/include
INCLUDEPATH6 = $(KERNEL_PATH)/portable/GCC/ARM_CA72_64_BIT
INCLUDEPATH7 = $(LIBMETAL_PATH)/build/lib/include
INCLUDEPATH8 = $(OPENAMP_PATH)/lib/include
INCLUDEPATH9 = $(OPENAMP_PATH)/apps/machine/raspi4

# From ./src
OBJS = build/startup.o 
OBJS +=build/FreeRTOS_asm_vector.o
OBJS +=build/FreeRTOS_tick_config.o
OBJS +=build/helper.o
OBJS +=build/main.o
OBJS +=build/mmu_cfg.o
OBJS +=build/printf.o
OBJS +=build/rpmsg-ping.o
OBJS +=build/uart.o

# From $(COMMON_PATH)
OBJS +=build/interrupt.o

# From $(APP_PATH)/mmu
OBJS +=build/mmu.o

# From $(APP_PATH)/cache
OBJS +=build/cache.o

# From $(APP_PATH)/musl_libc
OBJS +=build/memset.o
OBJS +=build/memcpy.o

# From $(OPENAMP_PATH)/apps/machine/raspi4
OBJS +=build/platform_info.o
OBJS +=build/raspi4_a72_rproc.o
OBJS +=build/rsc_table.o

# From $(KERNEL_PATH)/Source
OBJS +=build/list.o
OBJS +=build/queue.o
OBJS +=build/tasks.o
OBJS +=build/timers.o

# From $(KERNEL_PATH)/Source/portable/GCC/ARM_CA72_64_BIT
OBJS +=build/port.o
OBJS +=build/portASM.o

# From $(KERNEL_PATH)/Source/portable/MemMang
OBJS +=build/heap_1.o

rpmsg.elf : src/raspberrypi4.ld $(OBJS)
	$(CROSS)gcc -Wl,--build-id=none -std=gnu99 -T src/raspberrypi4.ld -o $@ -ffreestanding --specs=rdimon.specs $(BUILTIN_OPS) $(OBJS) $(LIB_PATH) $(LIBS)
	$(CROSS)objdump -d rpmsg.elf > rpmsg.list

build/%.o : src/%.S
	$(CROSS)as $(ASMFLAGS) -c -o $@ $<
	
build/%.o : src/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : $(COMMON_PATH)/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : $(APP_PATH)/mmu/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : $(APP_PATH)/cache/%.S
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : $(APP_PATH)/musl_libc/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : $(OPENAMP_PATH)/apps/machine/raspi4/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : $(KERNEL_PATH)/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : $(KERNEL_PATH)/portable/GCC/ARM_CA72_64_BIT/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

build/%.o : $(KERNEL_PATH)/portable/GCC/ARM_CA72_64_BIT/%.S
	$(CROSS)as $(ASMFLAGS) -c -o $@ $<

build/%.o : $(KERNEL_PATH)/portable/MemMang/%.c
	$(CROSS)gcc $(CFLAGS)  -c -o $@ $<

clean :
	rm -f build/*.o
	rm -f *.elf
	rm -f *.list

