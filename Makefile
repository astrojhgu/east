libs=lib/libeast.a
tests=bin/test
targets=$(libs) $(tests)
objs=obj/expression_node.o obj/operator_info.o obj/parser.o obj/tokenizer.o obj/east_exceptions.o
CXX=clang++
CXXFLAGS=-std=c++11 -I include/ -g -fPIC
LDFLAGS=-L lib/ -least

all:$(targets)

obj/east_exceptions.o:src/east_exceptions.cpp
	mkdir -p obj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

obj/expression_node.o:src/expression_node.cpp
	mkdir -p obj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

obj/operator_info.o:src/operator_info.cpp
	mkdir -p obj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

obj/parser.o:src/parser.cpp
	mkdir -p obj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

obj/tokenizer.o:src/tokenizer.cpp
	mkdir -p obj&&$(CXX) -c $(CXXFLAGS) $< -o $@ -O3

$(libs):$(objs)
	mkdir -p lib&& ar rv $(libs) $(objs)

obj/test.o :test/test.cpp
	mkdir -p obj&&$(CXX)  -c $(CXXFLAGS) $< -o $@ -O3

bin/test:obj/test.o $(libs)
	mkdir -p bin&&$(CXX) $(CXXFLAGS) $< $(objs) -o $@ -O3 $(LDFLAGS)

clean:
	rm -f obj/*.o
