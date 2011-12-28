SIMUL = simulation.o random.o interaction_data.o $(EXPERIMENT)
EXPERIMENT = Particle.o Detector.o Collimator.o Enclosure.o Source.o Experiment.o
PROCESS = processing.o 
CPPFLAGS = -I/usr/include/gsl
LDFLAGS = -lgsl
ROOTFLAGS = $(ROOT_INCLUDE) $(ROOT_LIB)
ROOT_INCLUDE = -I$(ROOTSYS)/include 
ROOT_LIB = -L$(ROOTSYS)/lib -lCore -lCint \
         -lGraf -lGraf3d -lHist -lHtml -lMatrix -lMinuit \
         -lPostscript -lProof -lTree \
         -lGpad -lGui -lGX11 -lRint 
C++ = c++ -Wall -O -Wshadow


all: simulation processing

simulation: $(SIMUL)
	$(C++) -o simulation $(SIMUL) $(CPPFLAGS) $(LDFLAGS) -lpthread

processing: $(PROCESS)
	$(C++) -o processing $(PROCESS) $(CPPFLAGS) $(LDFLAGS) $(ROOTFLAGS) -lpthread

clean:
	rm -f *.o

-include $(SIMUL:.o=.d)
-include $(EXPERIMENT:.o=.d)
-include $(PROCESS:.o=.d)


%.o: %.cpp
	$(C++) $(ROOT_INCLUDE) -c $*.cpp -o $*.o


