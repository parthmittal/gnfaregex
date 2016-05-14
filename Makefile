CXX=g++
CXXFLAGS=--std=c++11

BUILDDIR=build

.PHONY: clean

all: $(BUILDDIR)/gnfa.o | $(BUILDDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/gnfa.o: gnfa.cpp gnfa.h | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c gnfa.cpp -o $(BUILDDIR)/gnfa.o

clean:
	rm -rf $(BUILDDIR)
