SIMUL = main.o 

C++ = c++ -Wall -Werror -O -Wshadow -D__MACOSX_CORE__


all: main

main: $(SIMUL)
	$(C++) -o simulation $(SIMUL) -lpthread


-include $(SIMUL:.o=.d)

%.o: %.cpp
	$(C++) -c $*.cpp -o $*.o -Wall -Wshadow -Werror -O
	$(C++) -MM $*.cpp > $*.d



