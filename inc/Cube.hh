#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <Vector3D.hh>

class Cube{
public:
  std::string _name;
  Vector3D _shift;
  Vector3D _scale;
  Vector3D _rot_xyz_deg;
  Vector3D _trans_m;
  Vector3D _rgb;
  Cube();
  bool setShift(std::istringstream &stream);
  bool setScale(std::istringstream &stream);
  bool setRot(std::istringstream &stream);
  bool setTransM(std::istringstream &stream);
  bool setRGB(std::istringstream &stream);
  bool print();
};
