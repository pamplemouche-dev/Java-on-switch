include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
DEPS        := $(CURDIR)/deps

# Flags pour ARM64 (Switch) avec support PIE
ARCH    := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -fPIE
export CFLAGS   := $(ARCH) -O3 -fno-plt -I$(DEPS)/include -I$(DEPS)/include/linux
export CXXFLAGS := $(CFLAGS)

# On lie libjvm.so qui est maintenant dans tes deps pour éviter l'erreur de 10:59
LDFLAGS := -specs=$(DEPS)/specs/switch.specs -g $(ARCH) -Wl,-z,nocopyreloc -L$(DEPS)/lib
LIBS    := -ljvm -lnx -lcurl -lz -lm

all: $(TARGET).nro

$(TARGET).nro: $(TARGET).elf

$(TARGET).elf: main.o
	$(CXX) $(LDFLAGS) main.o $(LIBS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o *.elf *.nro
