SOURCES=picoJSON.cpp JSON.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CXX=g++
LIB=picoJSON.a
TEST_SOURCES=tester.cpp
TEST=tester

all: lib
lib: $(LIB)
$(OBJECTS): $(SOURCES)
	$(CXX) -c -o $@ $<

$(LIB): $(OBJECTS)
	ar rcs $@ $^
	ranlib $@

test: $(TEST)
$(TEST): $(TEST_SOURCES)
	$(CXX) -o $@ $^ -g

clean: clean_lib clean_test
clean_lib:
	@rm $(LIB) *.o

clean_test:
	@rm $(TEST)
