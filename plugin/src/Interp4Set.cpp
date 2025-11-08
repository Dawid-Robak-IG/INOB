#include <iostream>
#include "Interp4Set.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _x(0), _y(0), _z(0), _OX(0), _OY(0), _OZ(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << ' ' <<_ObjName << ' ' << _x << ' ' << _y << ' ' << _z << ' ' << _OX << ' ' << _OY << ' ' << _OZ << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}
bool Interp4Set::ExecCmd(std::shared_ptr<AbstractMobileObj> pObMob, std::shared_ptr<AccessControl> pAccCtrl){ return true;};     
bool Interp4Set::ExecCmd(AbstractScene &scene, std::shared_ptr<AccessControl> pAccCtrl){
  std::shared_ptr<AbstractMobileObj> obj = scene.FindMobileObj(_ObjName.c_str());
  if (obj == nullptr) {
      std::cerr << "Error: object: " << this->GetCmdName() << " wasn't found\n";
      return false;
  }

  Vector3D new_pos = Vector3D({_x,_y,_z});
  Vector3D new_rot = Vector3D({_OX,_OY,_OZ});

  pAccCtrl->LockAccess();
  obj->SetPosition_m(new_pos);
  obj->SetRPY(new_rot);
  Send(pAccCtrl->GetSocket(),make_cmd(obj).c_str());
  std::cout << "Set sent cmd: " << make_cmd(obj);
  pAccCtrl->UnlockAccess();

  return true;
}; 

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >>_ObjName >> _x >> _y >> _z >> _OX >> _OY >> _OZ;

  if (Strm_CmdsList.fail()) {
        std::cerr << "!!! ERROR: couldn't get params for Set." << std::endl;
        return false;
    }

  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  x[m] y[m] z[m] OX[°] OY[°] OZ[°]" << endl;
}
std::string Interp4Set::make_cmd(std::shared_ptr<AbstractMobileObj> obj){
  Vector3D pos = obj->GetPositoin_m();
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(3);
  oss << "UpdateObj Name=" << obj->GetName()
      << " Trans_m=(" << pos[0] << "," << pos[1] << "," << pos[2] << ")"
      << " RotXYZ_deg=(" << obj->GetAng_Roll_deg() << "," << obj->GetAng_Pitch_deg() << "," << obj->GetAng_Yaw_deg() << ")\n";
  return oss.str();
}