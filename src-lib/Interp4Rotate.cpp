#include <iostream>
#include "Interp4Rotate.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _axis("OX"), _speed(0), _length(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << ' ' <<_ObjName << ' ' << _axis << ' ' << _speed << ' ' << _length << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}
bool Interp4Rotate::ExecCmd(std::shared_ptr<AbstractMobileObj> pObMob, std::shared_ptr<AccessControl> pAccCtrl){return true;};     
bool Interp4Rotate::ExecCmd(AbstractScene &scene, std::shared_ptr<AccessControl> pAccCtrl){
  std::shared_ptr<AbstractMobileObj> obj = scene.FindMobileObj(_ObjName.c_str());
  if (obj == nullptr) {
      std::cerr << "Error: object: " << this->GetCmdName() << " wasn't found\n";
      return false;
  }

  double delta_t = 0.1;
  std::cout << "Going with speed: " << _speed << '\n';
  double delta_d = abs(_speed) * delta_t;
  int dir = (_speed >= 0 ? 1 : -1);
  double d = delta_d * dir;
  std::cout << "Delta d for move: " << d << '\n';

  do{
    _length = _length - delta_d;
    std::cout << "Len to go: " << _length << '\n';
    pAccCtrl->LockAccess();
    if(_axis == "OX") obj->SetAng_Roll_deg(obj->GetAng_Roll_deg() + d);
    else if(_axis == "OY") obj->SetAng_Pitch_deg(obj->GetAng_Pitch_deg() +d);
    else if(_axis == "OZ") obj->SetAng_Yaw_deg(obj->GetAng_Yaw_deg() +d);
    else{
      pAccCtrl->UnlockAccess();
      std::cerr << "Error: unrecognised axis\n";
      return false;
    }
    Send(pAccCtrl->GetSocket(),make_cmd(obj).c_str());
    std::cout<<"Rotate: " << make_cmd(obj);
    pAccCtrl->UnlockAccess();
    usleep(delta_t * 1000000);
  } while(_length > 0);

  return true;
}; 


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >>_ObjName >> _axis >> _speed >> _length;

  if (Strm_CmdsList.fail()) {
        std::cerr << "!!! ERROR: couldn't get params for Rotate." << std::endl;
        return false;
    }

  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  oś predkosc[m/s] dl.drogi[m]" << endl;
}
std::string Interp4Rotate::make_cmd(std::shared_ptr<AbstractMobileObj> obj) {
    double roll = obj->GetAng_Roll_deg();
    double pitch = obj->GetAng_Pitch_deg();
    double yaw = obj->GetAng_Yaw_deg();
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "UpdateObj Name=" << obj->GetName()
        << " RotXYZ_deg=(" << roll << "," << pitch << "," << yaw << ")\n";
    return oss.str();
}
