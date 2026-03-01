# Nom du projet (le fichier s'appellera javaswitch.nro)
TARGET := javaswitch

# On dit que les fichiers sources (.cpp) sont ici
SOURCES := .

# On liste les bibliothèques nécessaires
LIBS := -lcurl -lssl -lcrypto -lz -lnx

# Informations qui apparaîtront sur la Switch
APP_TITLE   := JavaSwitch
APP_AUTHOR  := Pamplemouche
APP_VERSION := 1.0.0

# Chemin vers ton fichier de config (généré via Cloud Shell)
NACPFLAGS := --control=assets/control.nacp

# Inclusion des règles officielles de devkitPro pour la Switch
# C'EST CETTE LIGNE QUI DÉFINIT LES "TARGETS"
include $(DEVKITPRO)/libnx/switch_rules
