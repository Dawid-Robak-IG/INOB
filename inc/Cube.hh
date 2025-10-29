#pragma once

#include <iostream>
#include <sstream>
#include <cstring>

struct Vector3D_d{
  double x, y, z;

  Vector3D_d(double _x=0, double _y=0, double _z=0): x(_x), y(_y), z(_z) {}

  friend std::istream &operator>>(std::istream &stream, Vector3D_d &v){
    return stream >> v.x >> v.y >> v.z;
  }
  friend std::ostream &operator<<(std::ostream &stream, Vector3D_d &v){
    return stream << v.x << ' ' << v.y << ' ' << v.z;
  }
};
struct Vector3D_i{
  int x, y, z;

  Vector3D_i(double _x=0, double _y=0, double _z=0): x(_x), y(_y), z(_z) {}

  friend std::istream &operator>>(std::istream &stream, Vector3D_i &v){
    return stream >> v.x >> v.y >> v.z;
  }
  friend std::ostream &operator<<(std::ostream &stream, Vector3D_i &v){
    return stream << v.x << ' ' << v.y << ' ' << v.z;
  }
};


class Cube{
public:
  std::string _name;
  Vector3D_d _shift;
  Vector3D_d _scale;
  Vector3D_i _rot_xyz_deg;
  Vector3D_d _trans_m;
  Vector3D_i _rgb;
  Cube();
  bool setShift(std::istringstream &stream);
  bool setScale(std::istringstream &stream);
  bool setRot(std::istringstream &stream);
  bool setTransM(std::istringstream &stream);
  bool setRGB(std::istringstream &stream);
  bool print();
};
