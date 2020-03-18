CXX = g++
CXXFLAGS = -Wall -g
LIBS = 

OBJS = main.o a.o B.o
DEPS = a.h B.h

.PHONY: all
all: example

example : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)
	
%.o : %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	-rm *.o example
	-del *.o example.exe