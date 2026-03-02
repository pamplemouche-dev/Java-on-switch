# On vérifie que devkitPRO est bien là
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment.")
endif

include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
SOURCES     := .
# On ajoute les chemins des bibliothèques (-L) et des inclusions (-I)
export INCLUDE := $(PORTLIBS)/include
export LIBPATHS := $(PORTLIBS)/lib

# Ordre précis des bibliothèques pour le linker
LIBS := -lcurl -lmbedtls -lmbedx509 -lmbedcrypto -lz -lnx

APP_TITLE   := JavaSwitch
APP_AUTHOR  := Pamplemouche
APP_VERSION := 1.0.0

NACPFLAGS   := --control=assets/control.nacp

all: $(TARGET).nro
