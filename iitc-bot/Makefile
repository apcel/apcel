CXX=g++
CXXFLAGS= -g -std=c++11 -O2 -DDEBUG
# INGRESS_INTEL_BOT-CPP=`pkg-config ./tgbot-cpp.pc --cflags --libs`

INGRESS_INTEL_BOT=iitc-bin
LIBS=-lpthread\
	-lssl\
	-lcrypto\
	-lcpr\
	-lcurl

	# -lboost_system\
	# $(TGdBOT-CPP)\

OBJS=main.o\
	iitc.o\
	portal.o

all: $(INGRESS_INTEL_BOT)

$(INGRESS_INTEL_BOT): $(OBJS)
	$(CXX) $(CXXFLAGS) -w $(OBJS) -o $(INGRESS_INTEL_BOT) $(LIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@
iitc.o: iitc.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@
portal.o: portal.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@





clean:
	rm -f $(INGRESS_INTEL_BOT) $(OBJS)