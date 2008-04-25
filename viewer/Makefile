DEFINES =
LIBS = OGRE
CXX = g++
#CXXFLAGS = $(shell pkg-config --cflags $(LIBS)) $(DEFINES)
CXXFLAGS = -L /Developer -logre -lcegui
LD = g++
#LDFLAGS = $(shell pkg-config --libs $(LIBS))
LDFLAGS =  -L /Developer -logre -lcegui

INCLUDES = -I/Library/OgreSDK/Dependencies/include -I/Library/OgreSDK/Dependencies/Ogre.framework/Headers -I/Library/OgreSDK/Samples/include -I/Library/OgreSDK/Dependencies/Ogre.framework/Versions/A/Headers

OBJS = "ViewerApplication.o"

all: viewer
		$(LD) $(LDFLAGS) $(OBJS) -o viewer

ViewerApplication.o: ViewerApplication.cpp
		$(CXX) -c $(INCLUDES) -F /Library/OgreSDK/Dependencies ViewerApplication.cpp

viewer: ViewerApplication.o

clean:
		rm -f viewer *.o
