PROJECT=mpss

ELF=$(PROJECT).elf
HEX=$(PROJECT).hex
LST=$(PROJECT).lst
SIZ=$(PROJECT).siz

CROSS_COMPILE=arm-none-eabi-

CC=$(CROSS_COMPILE)gcc
CPP=$(CROSS_COMPILE)g++
LD=$(CROSS_COMPILE)g++
AS=$(CROSS_COMPILE)gcc
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump
SIZE=$(CROSS_COMPILE)size

#FAMILY=STM32F10X_MD_VL 	#STM32F100
FAMILY=STM32F10X_MD		#STM32F103
SPL=USE_STDPERIPH_DRIVER

LD_SCRIPT=stm32f103c8.ld

LTO="-flto=2 -ffat-lto-objects -flto-partition=1to1"

#CFLAGS=-pipe -mcpu=cortex-m3 -mthumb -O2 -Wall -Werror -D$(FAMILY) -D$(SPL) -ffunction-sections -fdata-sections
CFLAGS=-pipe -mcpu=cortex-m3 -mthumb -O2 -ggdb -Wall -D$(FAMILY) -D$(SPL) -ffunction-sections -fdata-sections
CXXFLAGS=$(CFLAGS) -std=c++1z -fno-exceptions -fno-rtti -fno-unwind-tables
LDFLAGS=$(CXXFLAGS) -T$(LD_SCRIPT) -nostartfiles -nodefaultlibs -Xlinker --gc-sections

STM32F10x_INC_PATH=spl/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
SPL_INC_PATH=spl/spl/inc
CM3_INC_PATH=spl/Libraries/CMSIS/Include
GML_INC_PATH=gml/inc
INCDIRS=-I${STM32F10x_INC_PATH} -I${SPL_INC_PATH} -I${CM3_INC_PATH} -I${GML_INC_PATH} -Iinc

vpath %.c spl/spl/src

CPP_SRCS = $(wildcard src/*.cpp) $(wildcard gml/src/*.cpp)
#A_SRCS = STM32F10x_SPL/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_md_vl.s
A_SRCS = $(wildcard *.s)
C_SRCS = $(wildcard src/*.c) $(wildcard spl/spl/src/*.c) $(wildcard gml/src/*.c)
OBJS = $(patsubst %.c,%.o,$(C_SRCS)) $(patsubst %.s,%.o,$(A_SRCS)) $(patsubst %.cpp,%.o,$(CPP_SRCS))

all: $(HEX) $(LST) $(SIZ)

%.o: %.s
	$(AS) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) ${INCDIRS} -c $< -o $@

%.o: %.cpp
	$(CPP) $(CXXFLAGS) ${INCDIRS} -c $< -o $@

$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(LST): $(ELF)
	$(OBJDUMP) -h -S $< > $@

$(SIZ): $(ELF)
	$(SIZE) --format=berkeley $<

clean:
	rm -f $(OBJS) $(ELF) $(LST) $(HEX)
