NAME = rpmsg_echo

CROSS ?= aarch64-linux-gnu-
CFLAGS = -mcpu=cortex-a72 -std=gnu99 -O2 -Wall -Wextra -I$(INCLUDEPATH1) -I$(INCLUDEPATH2) -I$(INCLUDEPATH3) -g3

INCLUDEPATH1 ?= /usr/local/include
INCLUDEPATH2 = ../../../../open-amp/apps/machine/raspi4
INCLUDEPATH3 = ../../../common

# From ../src
OBJS = objs/main.o 
OBJS +=objs/helper.o

# From ../../../../open-amp/apps/machine/raspi4
OBJS +=objs/platform_info.o
OBJS +=objs/raspi4_a72_rproc.o

# From ../../../common
OBJS +=objs/interrupt.o

OBJDIR =./objs

.PHONY: all clean

all : objdir $(NAME)

objdir : | $(OBJDIR)

$(OBJDIR) :
	mkdir $@

clean :
	rm -rf $(OBJDIR)
	rm -f $(NAME)

$(NAME) : $(OBJS)
	$(CROSS)gcc -std=gnu99 -o $@ -O2 $(OBJS) -L/usr/local/lib -lmetal -lopen_amp 

objs/%.o : ../src/%.c
	$(CROSS)gcc $(CFLAGS) -c -o $@ $<

objs/%.o : ../../../../open-amp/apps/machine/raspi4/%.c
	$(CROSS)gcc $(CFLAGS) -c -o $@ $<

objs/%.o : ../../../common/%.c
	$(CROSS)gcc $(CFLAGS) -c -o $@ $<
