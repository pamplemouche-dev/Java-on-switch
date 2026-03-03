# 1. Chargement des règles officielles devkitPro
include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
SOURCES     := .
PORTLIBS    := $(DEVKITPRO)/portlibs/switch

# 2. Chemins Java pour l'environnement GitHub (Ubuntu)
JAVA_HOME   := /usr/lib/jvm/java-17-openjdk-amd64
JAVA_INC    := -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux

# 3. FLAGS MAGIQUES : 
# -mtls-dialect=desc : Supprime les erreurs rouges "__tls_align"
# Les -I : Suppriment les erreurs "switch.h" et "jni.h"
export CFLAGS   := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -O2 \
                   -I$(DEVKITPRO)/libnx/include -I$(PORTLIBS)/include $(JAVA_INC)
export CXXFLAGS := $(CFLAGS)

# 4. Librairies nécessaires
LIBDIRS     := -L$(DEVKITPRO)/libnx/lib -L$(PORTLIBS)/lib
LIBS        := -lcurl -lmbedtls -lmbedx509 -lmbedcrypto -lz -lnx

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) -g $(CXXFLAGS) main.o $(LIBDIRS) $(LIBS) -o $@
