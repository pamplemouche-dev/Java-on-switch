include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
SOURCES     := .
PORTLIBS    := $(DEVKITPRO)/portlibs/switch

# Options de compilation cruciales pour corriger l'erreur __tls_align
export CFLAGS   := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -O2 -ffunction-sections
export CXXFLAGS := $(CFLAGS)

# On inclut libnx ET les portlibs dans les chemins de recherche
LIBDIRS     := -L$(DEVKITPRO)/libnx/lib -L$(PORTLIBS)/lib
LIBS        := -lcurl -lmbedtls -lmbedx509 -lmbedcrypto -lz -lnx

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) -g $(CXXFLAGS) main.o $(LIBDIRS) $(LIBS) -o $@
