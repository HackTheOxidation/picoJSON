SOURCES=src/*.cpp
CXX=clang++
CXXFLAGS = -fPIC -shared -I./include/ -pedantic -Wall
LIB=libpicoJSON.so
TEST_SOURCES=tests/tester.cpp
TEST=tester

all: lib
lib: $(LIB)

$(LIB): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

test: install $(TEST)
$(TEST): $(TEST_SOURCES)
	$(CXX) -o $@ $^ -g -lpicoJSON

install: $(LIB)
	sudo cp $(LIB) /usr/lib
	sudo mkdir -p /usr/include/picoJSON
	sudo cp include/*.hpp /usr/include/picoJSON/

uninstall:
	sudo rm /usr/lib/$(LIB)
	sudo rm -rf /usr/include/picoJSON/

format:
	clang-format -i src/*.cpp
	clang-format -i include/*.hpp
	clang-format -i tests/*.cpp

clean: clean_lib clean_test
clean_lib:
	@rm $(LIB)

clean_test:
	@rm $(TEST)
