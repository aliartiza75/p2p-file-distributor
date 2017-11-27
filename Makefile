CXXFLAGS =	-O2 -g -fmessage-length=0

OBJS =		 Client.o 

LIBS =

TARGET =	Client2

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
