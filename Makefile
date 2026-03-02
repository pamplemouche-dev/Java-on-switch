include $(DEVKITPRO)/libnx/switch_rules

TARGET      := javaswitch
SOURCES     := .

# On liste les librairies Nintendo Switch nécessaires
LIBS        := -lcurl -lmbedtls -lmbedx509 -lmbedcrypto -lz -lnx

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) -g $(CXXFLAGS) main.o $(LDFLAGS) $(LIBS) -o $@
