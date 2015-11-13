
CXX=g++
CXXFLAGS= -g -O2 -std=c++11

VKFS=bin/main

#BOOST=`pkg-config ./boost.pc --cflags --libs`
#GLIB=`pkg-config glib-2.0 --cflags --libs`
CURL=`pkg-config libcurl --cflags --libs`
# JSON=`pkg-config json-c --cflags --libs`

LIBS=$(CURL)
	# $(JSON)

OBJS=obj/main.o\
	obj/https.o\
	obj/vkapi.o
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

obj/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@
# obj/rcfile.o: rcfile.c
# 	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@

obj/https.o: https.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@

obj/vkapi.o: vkapi.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@

#######################################################################
folders: $(DIRS)
$(DIRS):
	mkdir -p $(DIRS)

#######################################################################
clean:
	rm -f obj/*.o $(VKFS)

