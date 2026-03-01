#---------------------------------------------------------------------------------
# Simple Makefile pour libnx
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPRO")
endif

include $(DEVKITPRO)/libnx/switch_rules

TARGET      :=  javaswitch
SOURCES     :=  .
LIBS        :=  -lcurl -lssl -lcrypto -lz -lnx

APP_TITLE   :=  JavaSwitch
APP_AUTHOR  :=  Pamplemouche
APP_VERSION :=  1.0.0

# On force la recherche du NACP
NACPFLAGS   :=  --control=assets/control.nacp

# On définit explicitement la cible par défaut
all: $(TARGET).nro
