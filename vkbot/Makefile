
CXX=g++
CXXFLAGS= -g -O2

#VKFS=vkfske
VKFS=main

#STDC= -lstdc++
#PTHREAD= -lpthread
#CURL=-lcurl
#CURLPP=`pkg-config curlpp --cflags --libs` # -lcurl
#CRYPTO=`pkg-config libcrypto --cflags --libs` # -lcrypto
# EXIF=`pkg-config libexif --cflags --libs` # -lexif
# JSON_GLIB=`pkg-config json-glib-1.0 --cflags --libs`
# JSONC=`pkg-config json-c --cflags --libs`
# GLIB20=`pkg-config glib-2.0 --cflags --libs`
# XMLPP=`pkg-config libxml++-2.6 --cflags --libs`
# FUSE=`pkg-config fuse --cflags --libs` # -lfuse
# WEBKIT10=`pkg-config webkit-1.0 --cflags --libs`
# GTKP20=`pkg-config gtk+-2.0 --cflags --libs`
BOOST=`pkg-config ./boost.pc --cflags --libs`

# VKFSLIBS = $(PTHREAD)\
# $(CRYPTO)\
# $(EXIF)\
# $(JSONC)\
# $(CURL)\
# $(FUSE)

# VKFSOBJS = obj/exif.o\
# obj/vkfske.o\
# obj/vklib.o\
# obj/loglib.o\
# obj/vkfslib.o\
# obj/conv.o\
# obj/cach.o\
# obj/files.o\
# obj/dos.o
LIBS=$(BOOST)

OBJS=main.o




all: $(VKFS)
	echo "All Done"
	git add .
	git commit . -m 'Autobuild (make) by Sublime Text'
     
$(VKFS): $(OBJS)
	$(CXX) $(CXXFLAGS) -w $(OBJS) -o $(VKFS) $(LIBS)

main.o: main-new.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@
      
# obj/vkfske.o: vkfske/vkfske.cpp
# 	$(CXX) $(CXXFLAGS) $(VKFSLIBS) -w -c $< -o $@
    
# obj/vklib.o: vklib/vklib.cpp vklib/vklib.hpp
# 	$(CXX) $(CXXFLAGS) $(VKFSLIBS) -w -c $< -o $@
    
# obj/vkfslib.o: vkfslib/vkfslib.cpp vkfslib/vkfslib.hpp
# 	$(CXX) $(CXXFLAGS) $(VKFSLIBS) -w -c $< -o $@
    
# obj/loglib.o: loglib/log.cpp loglib/log.hpp
# 	$(CXX) $(CXXFLAGS) $(VKFSLIBS) -w -c $< -o $@
	    
# obj/conv.o: conv/conv.cpp conv/conv.hpp
# 	$(CXX) $(CXXFLAGS) $(VKFSLIBS) -w -c $< -o $@
	    
# obj/cach.o: cach/cach.cpp cach/cach.hpp
# 	$(CXX) $(CXXFLAGS) $(VKFSLIBS) -w -c $< -o $@
	    
# obj/dos.o: dos/dos.cpp dos/dos.hpp
# 	$(CXX) $(CXXFLAGS) $(VKFSLIBS) -w -c $< -o $@
	
# obj/exif.o: exif/exif.cpp exif/exif.hpp
# 	$(CXX) $(CXXFLAGS) $(VKFSLIBS) -w -c $< -o $@
    	  
# obj/files.o: files/files.cpp files/files.hpp
# 	$(CXX) $(CXXFLAGS) $(VKFSLIBS) -w -c $< -o $@


# clean:
# 	rm -f obj/*o bin/$(VKFS) 
	
# install:
# 	cp bin/$(VKFS)            "$(DESTDIR)/usr/bin/$(VKFS)"
# 	cp bin/vkfskemount.sh     "$(DESTDIR)/usr/bin/vkfskemount.sh"
# 	cp bin/vkfskeumount.sh    "$(DESTDIR)/usr/bin/vkfskeumount.sh"
# 	cp vkfskeauth.py          "$(DESTDIR)/usr/bin/vkfskeauth.py"
# 	cp vkfske.png             "$(DESTDIR)/usr/share/icons/hicolor/256x256/apps/vkfske.png"
# 	cp vkfske.desktop         "$(DESTDIR)/usr/share/applications/vkfske.desktop"	
# 	cp vkfskecaptchaisneed.py "$(DESTDIR)/usr/bin/vkfskecaptchaisneed.py"

# uninstall:
# 	rm "$(DESTDIR)/usr/bin/$(VKFS)"
# 	rm "$(DESTDIR)/usr/bin/vkfskemount.sh"
# 	rm "$(DESTDIR)/usr/bin/vkfskeumount.sh"
# 	rm "$(DESTDIR)/usr/bin/vkfskeauth.py"
# 	rm "$(DESTDIR)/usr/share/icons/hicolor/256x256/apps/vkfske.png"
# 	rm "$(DESTDIR)/usr/share/applications/vkfske.desktop"
# 	rm "$(DESTDIR)/usr/bin/vkfskecaptchaisneed.py"


