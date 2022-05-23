SOURCES=test.cpp i2cComms.cpp writeToFile.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/,$(SOURCES:.cpp=.d))
EXE=prog
CXXFLAGS=-I. -pthread

CXX=arm-rpizw-g++
BUILD_DIR=build/arm
BIN_DIR=bin/arm


ifeq (${ARCH},g++)
CXX=g++
BUILD_DIR=build/x86-64
BIN_DIR=bin/x86-64
endif


$(BIN_DIR)/$(EXE): $(DEPS) $(OBJECTS) $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)
	
$(BUILD_DIR)/%.o: %.cpp $(BUILD_DIR)
	$(CXX) -c $< -o $@

$(BUILD_DIR)/%.d: %.cpp $(BUILD_DIR)
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
	
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean: 
	@rm -r bin/
	@rm -r build/

ifneq ($(filter-out clean format tidy,$(MAKECMDGOALS)),clean)
-include $(DEPS)
endif

format: $(SOURCES:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format -i $<
	@echo "" > $@

tidy: $(SOURCES:.cpp=.tidy)
%.tidy: %.cpp
	@echo "Tidying file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@	
