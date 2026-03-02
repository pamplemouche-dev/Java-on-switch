include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
SOURCES     := .
PORTLIBS    := $(DEVKITPRO)/portlibs/switch

# On définit les options pour corriger les erreurs rouges __tls_align
export CFLAGS   := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -O2 -ffunction-sections -I$(DEVKITPRO)/libnx/include -I$(PORTLIBS)/include
export CXXFLAGS := $(CFLAGS)

# Chemins des bibliothèques
LIBDIRS     := -L$(DEVKITPRO)/libnx/lib -L$(PORTLIBS)/lib
LIBS        := -lcurl -lmbedtls -lmbedx509 -lmbedcrypto -lz -lnx

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) -g $(CXXFLAGS) main.o $(LIBDIRS) $(LIBS) -o $@
