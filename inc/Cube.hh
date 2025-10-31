#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <Vector3D.hh>


class Cube{
public:
  Vector3D _shift;
  Vector3D _scale;
  Vector3D _rot_xyz_deg;
  Vector3D _trans_m;
  Vector3D _rgb;
  std::string _name;
  Cube();
  bool setShift(std::istringstream &stream);
  bool setScale(std::istringstream &stream);
  bool setRot(std::istringstream &stream);
  bool setTransM(std::istringstream &stream);
  bool setRGB(std::istringstream &stream);
  bool print();
  friend std::ostream& operator<<(std::ostream &stream, const Cube &cube){
    return stream << cube._name << ' ' << cube._shift << ' ' << cube._scale << ' ' << cube._rot_xyz_deg << ' ' << cube._rot_xyz_deg 
                  << ' ' << cube._trans_m << ' ' << cube._rgb;
  }
  std::string get_cmd();
};
