# Nom du fichier final
TARGET := javaswitch

# Configuration des dossiers
BUILD := build
SOURCES := .
DATA := data
INCLUDES := -I$(DEVKITPRO)/libnx/include

# Metadonnées pour le menu Switch
APP_TITLE   := JavaSwitch
APP_AUTHOR  := Pamplemouche
APP_VERSION := 1.0.0

# On utilise le fichier genere via Cloud Shell
NACPFLAGS := --control=assets/control.nacp

# Librairies : Reseau (curl) + System (nx)
LIBS := -lcurl -lssl -lcrypto -lz -lnx

# Regles de compilation standard libnx
include $(DEVKITPRO)/libnx/switch_rules
