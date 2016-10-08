CC=g++
BIN=bin
INCLUDE=
CFLAGS=-c -pedantic -O3 -Wall -Wextra -Wno-unused-parameter -std=c++14 $(INCLUDE)
LDFLAGS=-std=c++14
SOURCES=$(wildcard tools/*.cpp) main.cpp
OBJECTS=$(addprefix $(BIN)/, $(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE=$(BIN)/main
vpath %.cpp includes:tools

all: $(EXECUTABLE)

$(BIN):
	mkdir -p $(BIN)

$(EXECUTABLE): $(BIN) $(OBJECTS)
	$(CC) $(LDFLAGS) $(LIB) $(OBJECTS) -o $@

-include $(BIN)/$(OBJECTS:.o=.d)

$(BIN)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $(BIN)/$*.o
	$(CC) -MM $(CFLAGS) $< > $(BIN)/$*.d 
	@mv -f $(BIN)/$*.d $(BIN)/$*.d.tmp
	@sed -e 's|.*:|$(BIN)/$*.o:|' < $(BIN)/$*.d.tmp > $(BIN)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BIN)/$*.d.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $(BIN)/$*.d
	@rm -f $(BIN)/$*.d.tmp

clean:
	rm -f $(BIN)/*.o $(BIN)/*.d $(EXECUTABLE)
