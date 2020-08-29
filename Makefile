CXX = g++
CXXFLAGS = -g -Wall
SRC_DIR = src
INC_DIR = inc
TEST_DIR = test

INCS += -I/usr/local/include
LIBS += -L/usr/local/lib -lpthread -lgtest_main -lgtest
TARGET = gtest_bign gtest_fraction gtest_sqrtn

all: $(TARGET)
.PHONY: all

gtest_bign: $(TEST_DIR)/gtest_bign.cpp $(SRC_DIR)/bign.cpp
	$(CXX) $^ -o $@ $(INCS) $(LIBS)

gtest_fraction: $(TEST_DIR)/gtest_fraction.cpp $(INC_DIR)/fraction.hpp
	$(CXX) $< -o $@ $(INCS) $(LIBS)

gtest_sqrtn: $(TEST_DIR)/gtest_sqrtn.cpp $(INC_DIR)/sqrtn.hpp $(INC_DIR)/fraction.hpp
	$(CXX) $< -o $@ $(INCS) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS)
.PHONY: clean