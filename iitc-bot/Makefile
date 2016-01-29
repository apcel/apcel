CXX=g++
CXXFLAGS= -g -std=c++11 -O2
# INGRESS_INTEL_BOT-CPP=`pkg-config ./tgbot-cpp.pc --cflags --libs`

INGRESS_INTEL_BOT=iitc-bin
LIBS=-lpthread\
	-lssl\
	-lcrypto\
	-lcpr\
	-lcurl

	# -lboost_system\
	# $(TGdBOT-CPP)\

OBJS=main.o

all: clean $(INGRESS_INTEL_BOT)

$(INGRESS_INTEL_BOT): $(OBJS)
	$(CXX) $(CXXFLAGS) -w $(OBJS) -o $(INGRESS_INTEL_BOT) $(LIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) -w -c $< -o $@

clean:
	rm -f $(INGRESS_INTEL_BOT) $(OBJS)