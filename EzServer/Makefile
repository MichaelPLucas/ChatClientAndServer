OUTPUT := server

CXX := g++
INCDIRS := -I.
CXXFLAGS := -std=c++11 -Wall -Wextra

SRCFILES := $(wildcard *.cpp)
OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
DEPFILES := $(patsubst %.cpp,%.d,$(SRCFILES))

$(OUTPUT): $(OBJFILES)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

%.d: %.cpp
	$(CXX) $(INCDIRS) -MM $< > $@

-include $(DEPFILES)

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(DEPFILES) $(OUTPUT)
