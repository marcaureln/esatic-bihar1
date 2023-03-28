APP_NAME = evenements
BUILD_DIR = bin
SRC_DIR = source

all: clean build run

build:
	@echo "⏳ Compilation de l'application..."
	@echo "🔍 Vérification des dépendances..."
	@if !(mysql_config --libs > /dev/null); then echo "Veuillez installer les librairies MySQL"; exit 1; fi
	@mkdir -p $(BUILD_DIR)
	@echo "🔧 Compilation des fichiers sources..."
	@gcc $(SRC_DIR)/*.c $$(mysql_config --libs) -I/usr/include/python3.10 -L/usr/lib/python3.10 -lpython3.10 -lm -g -o $(BUILD_DIR)/$(APP_NAME)
	@echo "📦 Compilation terminée."
	@echo ""

run:
	@$(BUILD_DIR)/$(APP_NAME) 172.18.0.2 root example evenements ignorer-initialisation

debug:
	@gdb --args $(BUILD_DIR)/$(APP_NAME) 172.18.0.2 root example evenements ignorer-initialisation

doc:
	@if !(doxygen --version > /dev/null); then echo "Veuillez installer Doxygen"; exit 1; fi
	@echo "📚 Génération de la documentation..."
	@doxygen -q Doxyfile
	@echo "📚 Documentation générée."
	@echo ""

clean:
	@rm -rf ./*/*.o
	@rm -rf ./*/*.out
	@rm -rf $(BUILD_DIR)
