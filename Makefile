CC = g++ -O6 -Wall -std=c++11

SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = test

SRCS = ImageCorrelation.cpp 
OBJS = ImageCorrelation.o 

INCFLAGS = -Iinclude `pkg-config opencv --cflags`

LIBFLAGS = `pkg-config opencv --libs`

TRGT = testImageCorrelation

all : $(TRGT)

$(TRGT) : $(OBJDIR)/$(OBJS)
	$(CC) $(TESTDIR)/$(TRGT).cpp $^ -o $(BINDIR)/$@ $(INCFLAGS) $(LIBFLAGS)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) -c $< $(INCFLAGS) -o $@


clean:
	rm -rf $(OBJDIR)/* $(BINDIR)/$(TRGT)
