bin_PROGRAMS=interp4cmds
interp4cmds_SOURCES = main.cpp \
                     Configuration.cpp \
                     Cube.cpp \
                     ExecPreprocesor.cpp \
                     LibInterface.cpp \
                     ProgramInterpreter.cpp \
                     Scene.cpp \
                     Sender.cpp \
                     Set4LibInterfaces.cpp \
                     xmlinterp.cpp
interp4cmds_CXXFLAGS = -I../inc -I../../../inc -std=c++17
interp4cmds_LDFLAGS = -Wl,-rpath='$(libdir)' ${LIB_DLOPEN} -lxerces-c
