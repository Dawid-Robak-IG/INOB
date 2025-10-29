__start__: obj __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall




interp: obj/main.o obj/Cube.o obj/Configuration.o obj/xmlinterp.o obj/ExecPreprocesor.o obj/LibInterface.o obj/Set4LibInterfaces.o obj/ProgramInterpreter.o
	g++ ${LDFLAGS} -o interp  obj/main.o obj/Cube.o obj/Configuration.o obj/xmlinterp.o obj/LibInterface.o obj/ExecPreprocesor.o\
	 obj/Set4LibInterfaces.o obj/ProgramInterpreter.o -ldl -lxerces-c

obj/main.o: src/main.cpp inc/AbstractInterp4Command.hh inc/AbstractScene.hh\
            inc/AbstractComChannel.hh inc/ExecPreprocesor.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/ProgramInterpreter.o: src/ProgramInterpreter.cpp inc/ProgramInterpreter.hh
	g++ -c $(CPPFLAGS) -o obj/ProgramInterpreter.o src/ProgramInterpreter.cpp

obj/Set4LibInterfaces.o: src/Set4LibInterfaces.cpp inc/Set4LibInterfaces.hh
	g++ -c $(CPPFLAGS) -o obj/Set4LibInterfaces.o src/Set4LibInterfaces.cpp

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh
	g++ -c $(CPPFLAGS) -o obj/LibInterface.o src/LibInterface.cpp

obj/ExecPreprocesor.o: src/ExecPreprocesor.cpp inc/ExecPreprocesor.hh
	g++ -c $(CPPFLAGS) -o obj/ExecPreprocesor.o src/ExecPreprocesor.cpp

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh
	g++ -c $(CPPFLAGS) -o obj/xmlinterp.o src/xmlinterp.cpp

obj/Configuration.o: src/Configuration.cpp inc/Configuration.hh
	g++ -c $(CPPFLAGS) -o obj/Configuration.o src/Configuration.cpp

obj/Cube.o: src/Cube.cpp inc/Cube.hh
	g++ -c $(CPPFLAGS) -o obj/Cube.o src/Cube.cpp

doc:
	cd dox; make

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
