# On charge les règles de base de devkitPro
include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
SOURCES     := .
PORTLIBS    := $(DEVKITPRO)/portlibs/switch

# On définit les chemins Java (JNI) pour Ubuntu
JAVA_HOME   := /usr/lib/jvm/java-17-openjdk-amd64
JAVA_INC    := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux

# RÉGLAGE FINAL : On force l'inclusion et le dialecte TLS
export CFLAGS   := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -O2 \
                   -I$(DEVKITPRO)/libnx/include -I$(PORTLIBS)/include $(JAVA_INC)
export CXXFLAGS := $(CFLAGS)

# On indique où sont les bibliothèques et le fameux crt0.o
LIBDIRS     := -L$(DEVKITPRO)/libnx/lib -L$(PORTLIBS)/lib
LIBS        := -lcurl -lmbedtls -lmbedx509 -lmbedcrypto -lz -lnx

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) -g $(CXXFLAGS) main.o $(LIBDIRS) $(LIBS) -o $@
