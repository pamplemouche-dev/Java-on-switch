include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
DEPS        := $(CURDIR)/deps

ARCH    := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -fPIE
export CFLAGS   := $(ARCH) -O3 -fno-plt -I$(DEPS)/include -I$(DEPS)/include/linux
export CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

# LDFLAGS : On force le linker à ignorer les erreurs de symboles non résolus au début
LDFLAGS := -specs=$(DEPS)/specs/switch.specs -g $(ARCH) -Wl,-z,nocopyreloc -L$(DEPS)/lib

# LIBS : L'ordre pour Java 17 + OpenGL
LIBS    := -ljvm -lnx -lcurl -lz -lm -lpthread

OBJS    := compat.o main.o

all: $(TARGET).nro

$(TARGET).nro: $(TARGET).elf

$(TARGET).elf: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

compat.o: compat.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
