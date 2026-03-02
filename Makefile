include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
SOURCES     := .
PORTLIBS    := $(DEVKITPRO)/portlibs/switch

# Options de compilation cruciales pour éviter "undefined reference to __tls"
export CFLAGS   := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -O2 -ffunction-sections
export CXXFLAGS := $(CFLAGS)

LIBDIRS     := -L$(DEVKITPRO)/libnx/lib -L$(PORTLIBS)/lib
LIBS        := -lcurl -lmbedtls -lmbedx509 -lmbedcrypto -lz -lnx

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) -g $(CXXFLAGS) main.o $(LIBDIRS) $(LIBS) -o $@
