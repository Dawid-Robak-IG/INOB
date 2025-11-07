#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <iostream>
#include <vector>
#include "Cube.hh"

class Configuration {
  std::vector<std::string> _libsNames;
  std::vector<Cube> _cubes;

public:
  bool addLib(const char* name);
  bool addCube(Cube &cube);
  std::vector<std::string> &getLibs();
  std::string GetObjCmds();
  std::vector<Cube> &GetCubes();
};


#endif
