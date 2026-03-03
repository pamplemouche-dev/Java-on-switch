include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
DEPS        := $(CURDIR)/deps

export CFLAGS   := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -O2 \
                   -I$(DEPS)/include
export CXXFLAGS := $(CFLAGS)

LDFLAGS     := -L$(DEPS)/lib
LIBS        := -lcurl -lz -lnx

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) -g $(CXXFLAGS) main.o $(LDFLAGS) $(LIBS) -o $@
