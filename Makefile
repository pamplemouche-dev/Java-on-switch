include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
DEPS        := $(CURDIR)/deps

ARCH    := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -fPIE
export CFLAGS   := $(ARCH) -O3 -fno-plt -I$(DEPS)/include -I$(DEPS)/include/linux
export CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

# LDFLAGS : L'ordre ici est CRITIQUE. On lie compat.o en premier.
LDFLAGS := -specs=$(DEPS)/specs/switch.specs -g $(ARCH) -Wl,-z,nocopyreloc -L$(DEPS)/lib

# LIBS : On ajoute -lpthread car Java le demande partout
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

clean:
	rm -f *.o *.elf *.nro
