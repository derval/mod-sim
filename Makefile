EXPERIMENT = Detector.o Collimator.o Enclosure.o Particle.o Source.o Experiment.o
SIMUL = simulation.o random.o interaction_data.o histo_maker.o file_maker.o $(EXPERIMENT)
SIMUL_LIB = $(patsubst %,$(LIB)/%,$(SIMUL))
PROCESS = processing.o
PROCESS_LIB = $(patsubst %,$(LIB)/%,$(PROCESS))
CPPFLAGS = -I/usr/include/gsl
LDFLAGS = -lgsl
ROOTFLAGS = $(ROOT_INCLUDE) $(ROOT_LIB)
ROOT_INCLUDE = -I$(ROOTSYS)/include 
ROOT_LIB = -L$(ROOTSYS)/lib -lCore -lCint \
         -lGraf -lGraf3d -lHist -lHtml -lMatrix -lMinuit \
         -lPostscript -lProof -lTree \
         -lGpad -lGui -lGX11 -lRint 
C++ = c++ -Wall -O -Wshadow

LIB = lib
SRC = src

all: simulation processing

simulation: $(SIMUL_LIB)
	$(C++) -o simulation $(SIMUL_LIB) $(CPPFLAGS) $(LDFLAGS) -lpthread

processing: $(PROCESS_LIB)
	$(C++) -o processing $(PROCESS_LIB) $(CPPFLAGS) $(LDFLAGS) $(ROOTFLAGS) -lpthread

clean:
	rm -f $(LIB)/*.o

-include $(SIMUL:.o=.d)
-include $(EXPERIMENT:.o=.d)
-include $(PROCESS:.o=.d)

$(LIB)/%.o: $(SRC)/%.cpp
	$(C++) $(ROOT_INCLUDE) -c $(SRC)/$*.cpp -o $(LIB)/$*.o



