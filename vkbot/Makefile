
CXX=g++
CXXFLAGS= -g -O2

VKFS=main

BOOST=`pkg-config ./boost.pc --cflags --libs`


LIBS=$(BOOST)

OBJS=obj/main.o
DIRS=obj\
	bin



all: folders $(VKFS)
	echo "All Done"
	git add .
	git commit . -m 'Autobuild (make) by Sublime Text'

$(VKFS): $(OBJS)
	$(CXX) $(CXXFLAGS) -w $(OBJS) -o $(VKFS) -I/usr/local/boost/include -L/usr/local/boost/lib -lboost_system 

obj/main.o: main-new.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@




folders: $(DIRS)
$(DIRS):
	mkdir -p $(DIRS)
# clean:
#  	rm -f obj/*.o bin/$(VKFS)

clean:
	rm -f obj/*.o bin/$(VKFS)

