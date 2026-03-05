include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
DEPS        := $(CURDIR)/deps
# Le chemin vers le Java téléchargé par le workflow
JAVA_TEMP   := $(CURDIR)/external_java

ARCH    := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -fPIE
export CFLAGS   := $(ARCH) -O3 -fno-plt -I$(DEPS)/include -I$(DEPS)/include/linux -I$(JAVA_TEMP)/include -I$(JAVA_TEMP)/include/linux
export CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

LDFLAGS := -specs=$(DEPS)/specs/switch.specs -g $(ARCH) -Wl,-z,nocopyreloc -L$(DEPS)/lib
LIBS    := -ljvm -lnx -lcurl -lz -lm -lpthread

OBJS    := compat.o main.o

all: $(TARGET).nro

$(TARGET).nro: $(TARGET).elf
$(TARGET).elf: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
