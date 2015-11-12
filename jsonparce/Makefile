
CXX=g++
CXXFLAGS= -g -O2 -std=c++11
DIRS=obj\
	bin
LIBS=
OBJS=obj/main.o

GOAL=bin/main.out

all: folders $(GOAL)
	echo "All Done"

$(GOAL): $(OBJS)
	$(CXX) $(CXXFLAGS) -w $(OBJS) -o $(GOAL)
# $(LIBS)


obj/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@

folders: $(DIRS)
$(DIRS):
	mkdir -p $(DIRS)
clean:
	rm -f obj/*.o $(GOAL)
