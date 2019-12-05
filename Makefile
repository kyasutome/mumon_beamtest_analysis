TARGET = make_ana_file
TARGET2 = make_ana_files
TARGET3 = waveform
TARGET4 = make_history_plots

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)

CXXFLAGS = $(ROOTFLAGS) -Wall -fPIC
CXXLIBS	= $(ROOTLIBS)
CC = g++

WORKDIR = ./
LIBS            = $(ROOTGLIBS) \

OBJDIR = $(WORKDIR)/obj
SRCDIR = $(WORKDIR)/src
OUTDIR = $(WORKDIR)/bin
INCDIR = -I$(WORKDIR)/include 

PROG := $(OUTDIR)/$(TARGET)
PROG2 := $(OUTDIR)/$(TARGET2)
PROG3 := $(OUTDIR)/$(TARGET3)
PROG4 := $(OUTDIR)/$(TARGET4)

all: $(PROG) $(PROG2) $(PROG3) $(PROG4)

#compile TARGET
SRCS := $(TARGET).cc
OBJS :=  $(OBJDIR)/$(SRCS:.cc=.o)

$(PROG): $(OBJS)
	$(CC) $(CXXLIBS) $(OBJS) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@[ -d $(OBJDIR) ]
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

#compile TARGET2
SRCS2 := $(TARGET2).cc
OBJS2 :=  $(OBJDIR)/$(SRCS2:.cc=.o)

$(PROG2): $(OBJS2)
	$(CC) $(CXXLIBS) $(OBJS2) -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@[ -d $(OBJDIR) ]
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

#compile TARGET3
SRCS3 := $(TARGET3).cc
OBJS3 :=  $(OBJDIR)/$(SRCS3:.cc=.o)

$(PROG3): $(OBJS3)
	$(CC) $(CXXLIBS) $(OBJS3) -o $@


$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@[ -d $(OBJDIR) ]
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<

#compile TARGET4
SRCS4 := $(TARGET4).cc
OBJS4 :=  $(OBJDIR)/$(SRCS4:.cc=.o)

$(PROG4): $(OBJS4)
	$(CC) $(CXXLIBS) $(OBJS4) -o $@


$(OBJDIR)/%.o : $(SRCDIR)/%.cc
	@[ -d $(OBJDIR) ]
	$(CC) $(CXXFLAGS) $(INCDIR) -o $@ -c $<


clean:
	rm -f $(OBJDIR)/*.o $(OUTDIR)/*
	@echo "Cleanup complete!"	