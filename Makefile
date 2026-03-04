include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
DEPS        := $(CURDIR)/deps

# Utilisation de l'architecture officielle Switch
ARCH    := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc

export CFLAGS   := $(ARCH) -O2 -I$(DEPS)/include
export CXXFLAGS := $(CFLAGS)

# Pointage direct sur le fichier importé dans deps
LDFLAGS := -specs=$(DEPS)/specs/switch.specs -L$(DEPS)/lib

LIBS    := -lcurl -lz -lnx

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) -g $(CXXFLAGS) main.o $(LDFLAGS) $(LIBS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
