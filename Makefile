include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
DEPS        := $(CURDIR)/deps

# ARCH & FLAGS
ARCH    := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -fPIE
export CFLAGS   := $(ARCH) -O3 -fno-plt -I$(DEPS)/include -I$(DEPS)/include/linux
export CXXFLAGS := $(CFLAGS)

# LDFLAGS : On force le lien statique avec le nouveau libjvm.so ARM64
LDFLAGS := -specs=$(DEPS)/specs/switch.specs -g $(ARCH) -Wl,-z,nocopyreloc -L$(DEPS)/lib

LIBS    := -ljvm -lnx -lcurl -lz -lm

all: $(TARGET).nro

# Cette règle est cruciale pour transformer l'exécutable en fichier Switch
$(TARGET).nro: $(TARGET).elf

$(TARGET).elf: main.o
	$(CXX) $(LDFLAGS) main.o $(LIBS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
