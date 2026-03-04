TARGET      := javaswitch
DEPS        := $(CURDIR)/deps

# On n'utilise plus les chemins système, mais tes fichiers importés
LDFLAGS     := -specs=$(DEPS)/specs/switch.specs -L$(DEPS)/lib -Wl,-rpath,/opt/java/lib

# On lie libjvm.so qui est maintenant dans tes deps
LIBS        := -ljvm -lnx -lcurl -lz

# Inclusion des headers Java importés
INCLUDES    := -I$(DEPS)/include -I$(DEPS)/include/linux

all: $(TARGET).nro

$(TARGET).elf: main.o
	$(CXX) $(LDFLAGS) main.o $(LIBS) -o $@

main.o: main.cpp
	$(CXX) $(INCLUDES) -c main.cpp -o main.o
