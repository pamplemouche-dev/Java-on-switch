include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
SOURCES     := .

# On force le chemin vers les bibliothèques portées
PORTLIBS := $(DEVKITPRO)/portlibs/switch

# On définit explicitement les répertoires de recherche
export INCLUDE := -I$(CURDIR) -I$(PORTLIBS)/include
export LIBDIRS := -L$(PORTLIBS)/lib

# On liste les libs
LIBS := -lcurl -lmbedtls -lmbedx509 -lmbedcrypto -lz -lnx

APP_TITLE   := JavaSwitch
APP_AUTHOR  := Pamplemouche
APP_VERSION := 1.0.0
NACPFLAGS   := --control=assets/control.nacp

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) -g $(CXXFLAGS) main.o $(LIBDIRS) $(LIBS) -o $@
