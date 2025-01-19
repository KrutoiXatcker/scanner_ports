TARGET = scanner_ports
CC = g++ -Wall -g
PREF_SRC = ./src/
PREF_OBJ = ./obj/
PREF_LIB = ./lib/
PREF_BIN = ./bin/


SRC = $(wildcard $(PREF_SRC)/*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp,$(PREF_OBJ)%.o,$(SRC))


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(PREF_BIN)$(TARGET) -lscanner_ports -L./$(PREF_LIB)
	

$(PREF_OBJ)%.o: $(PREF_SRC)%.cpp
	$(CC) -c $< -o $@


clean:
	rm -f $(PREF_BIN)$(TARGET) $(PREF_OBJ)*.o

