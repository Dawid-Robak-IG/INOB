#pragma once

#include "AbstractMobileObj.hh"

class CubeObj: public AbstractMobileObj{
public:
    CubeObj() {}
    double GetAng_Roll_deg() const{ return _rpy[0];}
    double GetAng_Pitch_deg() const{return _rpy[1];}
    double GetAng_Yaw_deg() const{return _rpy[2];}
    void SetAng_Roll_deg(double Ang_Roll_deg){_rpy[0]=Ang_Roll_deg;}
    void SetAng_Pitch_deg(double Ang_Pitch_deg){_rpy[1]=Ang_Pitch_deg;}
    void SetAng_Yaw_deg(double Ang_Yaw_deg){_rpy[2]=Ang_Yaw_deg;}
    const Vector3D & GetPositoin_m() const{return _position;}
    void SetPosition_m(const Vector3D &rPos){_position=rPos;}
    void SetName(const char* sName) {_name = sName;}
    const std::string & GetName() const{return _name;}
    void SetRPY(Vector3D rpy){_rpy = rpy;}
};