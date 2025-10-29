#pragma once

#include <iostream>
#include <sstream>
#include <cstring>
#include <Vector3D.hh>

#include "AbstractMobileObj.hh"

class Cube: public AbstractMobileObj{
  std::string _name;
  Vector3D _shift;
  Vector3D _scale;
  Vector3D _rot_xyz_deg;
  Vector3D _trans_m;
  Vector3D _rgb;
public:
  Cube();
  bool setShift(std::istringstream &stream);
  bool setScale(std::istringstream &stream);
  bool setRot(std::istringstream &stream);
  bool setTransM(std::istringstream &stream);
  bool setRGB(std::istringstream &stream);
  bool print();

  double GetAng_Roll_deg() const override {return _rot_xyz_deg[0];}
  double GetAng_Pitch_deg() const override {return _rot_xyz_deg[1];}
  double GetAng_Yaw_deg() const override {return _rot_xyz_deg[2];}
  void SetAng_Roll_deg(double Ang_Roll_deg) override {_rot_xyz_deg[2] = Ang_Roll_deg;}
  void SetAng_Pitch_deg(double Ang_Pitch_deg) override {_rot_xyz_deg[0] = Ang_Pitch_deg;}
  void SetAng_Yaw_deg(double Ang_Yaw_deg) override {_rot_xyz_deg[1] = Ang_Yaw_deg;}
  const Vector3D & GetPositoin_m() const override {return _trans_m;}
  void SetPosition_m(const Vector3D &rPos) override {_trans_m = rPos;}
  void SetName(const char* sName) override {_name = sName;}
  const std::string & GetName() const override {return _name;}
};
