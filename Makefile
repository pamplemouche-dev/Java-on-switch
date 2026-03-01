# Nom de l'application
TARGET := javaswitch

# Dossier des sources et des objets
SOURCES := src
BUILD := build
DATA := data
INCLUDES := include

# Configuration de l'application (Métadonnées)
APP_TITLE := JavaSwitch
APP_AUTHOR := Pamplemouche
APP_VERSION := 1.0.0
APP_ICON := assets/icon.jpg

# Utilisation de ton fichier NACP personnalisé
NACPFLAGS := --control=assets/control.nacp

# Bibliothèques nécessaires (CURL pour le réseau)
LIBS := -lcurl -lssl -lcrypto -lz -lnx

# --- Ne pas modifier en dessous (Standard devkitPro) ---
include $(DEVKITPRO)/libnx/switch_rules
