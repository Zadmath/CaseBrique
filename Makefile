# Nom du binaire à générer
TARGET = CasseBrique

# Compilateur à utiliser
CC = g++

# Options de compilation
CFLAGS = -Wall -Wextra -std=c++17 -O2
# Chemins d'inclusion pour les headers
INCLUDES = -Iinclude -I/usr/include/SDL2 -lSDL2_ttf
# Options de lien
LDFLAGS = -lSDL2 -lSDL2_ttf

# Dossiers de sources et objets
SRCDIR = src
OBJDIR = obj
INCDIR = include

# Trouver les fichiers source (.cpp) et définir les fichiers objet correspondants (.o)
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Règle par défaut
all: $(TARGET)

# Lien des fichiers objet en exécutable
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compilation des fichiers source en fichiers objet
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


# Nettoyage des fichiers générés
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

# Pour reconstruire entièrement le projet
rebuild: clean all

# Ne considérez pas all, clean et rebuild comme des fichiers
.PHONY: all clean rebuild
