
CXX=g++
CXXFLAGS= -g -O2

VKFS=bin/main

BOOST=`pkg-config ./boost.pc --cflags --libs`
GLIB=`pkg-config glib-2.0 --cflags --libs`

LIBS=$(BOOST)\
	$(GLIB)

OBJS=obj/main.o\
	#obj/rcfile.o
DIRS=obj\
	bin
#######################################################################
#######################################################################

all: folders $(VKFS)
	echo "All Done"
	(git add .; git commit . -m 'Autobuild (make) by Sublime Text'; exit 0)

$(VKFS): $(OBJS)
	$(CXX) $(CXXFLAGS) -w $(OBJS) -o $(VKFS) $(LIBS)

obj/main.o: main-new.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@
obj/rcfile.o: rcfile.c
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@
#######################################################################
folders: $(DIRS)
$(DIRS):
	mkdir -p $(DIRS)

#######################################################################
clean:
	rm -f obj/*.o bin/$(VKFS)

