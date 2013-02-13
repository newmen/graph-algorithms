GCC_PATH	:= /usr
CXX		:= $(GCC_PATH)/bin/g++
CXXFLAGS	:= -Wall -O2 -I$(GCC_PATH)/include -L$(GCC_PATH)/lib

NAME		:= graph
SRC_DIR		:= cpp
OBJ_DIR		:= obj
SOURCE_FILES	:= $(wildcard $(SRC_DIR)/*.cc)
OBJECT_FILES	:= $(addprefix $(OBJ_DIR)/,$(notdir $(SOURCE_FILES:.cc=.o)))

$(NAME): $(OBJECT_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SRC_DIR)/main.cpp

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(NAME)

cleanall: clean
	rm -rf $(OBJ_DIR)
