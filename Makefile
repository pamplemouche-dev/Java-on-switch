include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
DEPS        := $(CURDIR)/deps
JAVA_HOME   := /usr/lib/jvm/java-17-openjdk-amd64

# ARCH & FLAGS : Ajout de -fPIE pour régler l'erreur de relocation
ARCH    := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -fPIE

export CFLAGS   := $(ARCH) -O2 -fno-plt \
                   -I$(DEPS)/include \
                   -I$(JAVA_HOME)/include \
                   -I$(JAVA_HOME)/include/linux

export CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

# LDFLAGS : On s'assure que le linker sait qu'on fait un PIE
LDFLAGS := -specs=$(DEPS)/specs/switch.specs -g $(ARCH) -Wl,-z,nocopyreloc -L$(DEPS)/lib

LIBS    := -lcurl -lz -lnx

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) $(LDFLAGS) main.o $(LIBS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o *.elf *.nro
