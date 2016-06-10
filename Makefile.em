libs=lib/libjseast.a
targets=$(libs)
objs=jsobj/expression_node.o jsobj/operator_info.o jsobj/parser.o jsobj/tokenizer.o jsobj/east_exceptions.o
CXX=em++
CXXFLAGS=-std=c++11 -I include/ -g
LDFLAGS=-L lib/ -least

all:$(targets)

jsobj/east_exceptions.o:src/east_exceptions.cpp
	mkdir -p jsobj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

jsobj/expression_node.o:src/expression_node.cpp
	mkdir -p jsobj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

jsobj/operator_info.o:src/operator_info.cpp
	mkdir -p jsobj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

jsobj/parser.o:src/parser.cpp
	mkdir -p jsobj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

jsobj/tokenizer.o:src/tokenizer.cpp
	mkdir -p jsobj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

$(libs):$(objs)
	mkdir -p lib&& emar rv $(libs) $(objs)

jsobj/test.o :test/test.cpp
	mkdir -p jsobj&&$(CXX)  -c $(CXXFLAGS) $< -o $@ -O3

clean:
	rm -f jsobj/*.o
