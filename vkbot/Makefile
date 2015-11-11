
CXX=g++
CXXFLAGS= -g -O2

VKFS=bin/main

BOOST=`pkg-config ./boost.pc --cflags --libs`


LIBS=$(BOOST)

OBJS=obj/main.o
DIRS=obj\
	bin
#######################################################################
#######################################################################

all: clean folders $(VKFS)
	echo "All Done"
	(git add .; git commit . -m 'Autobuild (make) by Sublime Text'; exit 0)

$(VKFS): $(OBJS)
	$(CXX) $(CXXFLAGS) -w $(OBJS) -o $(VKFS) $(LIBS)

obj/main.o: main-new.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@
#######################################################################
folders: $(DIRS)
$(DIRS):
	mkdir -p $(DIRS)

#######################################################################
clean:
	rm -f obj/*.o bin/$(VKFS)

