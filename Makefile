XX = g++
CXXFLAGS = -I/usr/include -Wall -g
LDFLAGS = -L/usr/local/lib

vpath %.h %.cpp

all : net_420 net_527
.PHONY : all

a_1 : net_427.obj
	$(CXX) $(LDFLAGS) -o net_420 net_420.obj

a_2 : net_527.obj 
	$(CXX) $(LDFLAGS) -o net_527 net_527.obj


net_420.obj : net.h net_420.cpp
	$(CXX) $(CXXFLAGS) -c net_420.cpp -o net_420.obj

net_527.obj : net.h net_527.cpp
	$(CXX) $(CXXFLAGS) -c net_527.cpp -o net_527.obj

clean:
	@rm -rf *.obj
	@rm -rf net_420
	@rm -rf net_527
