# Inclusion des règles officielles devkitPro pour la Switch
include $(DEVKITPRO)/libnx/switch_rules

# Nom de l'exécutable final
TARGET      := javaswitch
DEPS        := $(CURDIR)/deps
JAVA_HOME   := /usr/lib/jvm/java-17-openjdk-amd64

# Configuration de l'architecture ARM64 de la Switch
# -fPIE est indispensable pour éviter les erreurs de "relocation"
ARCH    := -march=armv8-a+crc+crypto -mtune=cortex-a57 -mtls-dialect=desc -fPIE

# Options de compilation (C et C++)
export CFLAGS   := $(ARCH) -O3 -fno-plt \
                   -I$(DEPS)/include \
                   -I$(DEPS)/include/linux \
                   -I$(JAVA_HOME)/include \
                   -I$(JAVA_HOME)/include/linux

export CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions

# Options du Linker (LDFLAGS)
# On ajoute -L$(DEPS)/lib pour que le linker trouve ton libjvm.so importé
LDFLAGS := -specs=$(DEPS)/specs/switch.specs -g $(ARCH) -Wl,-z,nocopyreloc \
           -L$(DEPS)/lib -L$(JAVA_HOME)/lib/server

# Liste des bibliothèques à lier
# L'ordre est important : Java d'abord, puis les fonctions Switch
LIBS    := -ljvm -lnx -lcurl -lz -lm

# Liste des fichiers objets à créer
# On ajoute compat.o pour corriger les erreurs GLIBC de ta capture
OBJS    := main.o compat.o

# Règle principale
all: $(TARGET).nro

# Transformation du fichier ELF en fichier NRO (format Switch)
$(TARGET).nro: $(TARGET).elf

# Création de l'exécutable ELF
$(TARGET).elf: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

# Compilation du code principal
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilation du pont de compatibilité (pour les erreurs 13:18)
compat.o: compat.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage du projet
clean:
	rm -f *.o *.elf *.nro
