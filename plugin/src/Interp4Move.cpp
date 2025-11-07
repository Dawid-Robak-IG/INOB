#include <iostream>
#include "Interp4Move.hh"


using std::cout;
using std::endl;


extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _Speed_mmS(0), _road(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ObjName << " " << _Speed_mmS << " " << _road << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Move::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}
bool Interp4Move::ExecCmd(std::shared_ptr<AbstractMobileObj> pObMob, std::shared_ptr<AccessControl> pAccCtrl){return true;};     
bool Interp4Move::ExecCmd(AbstractScene &scene, std::shared_ptr<AccessControl> pAccCtrl){
  std::shared_ptr<AbstractMobileObj> obj = scene.FindMobileObj(_ObjName.c_str());
  if (obj == nullptr) {
      std::cerr << "Error: object: " << this->GetCmdName() << " wasn't found\n";
      return false;
  }

  double delta_t = 0.1;
  std::cout << "Going with speed: " << _Speed_mmS << '\n';
  double delta_d = abs(_Speed_mmS) * delta_t;
  int dir = (_Speed_mmS >= 0 ? 1 : -1);
  Vector3D d = Vector3D({1,0,0}) * delta_d * dir;
  std::cout << "Delta d for move: " << d << '\n';

  do{
    _road = _road - delta_d;
    std::cout << "Dist to go: " << _road << '\n';
    pAccCtrl->LockAccess();
    obj->SetPosition_m(obj->GetPositoin_m() + d);
    Send(pAccCtrl->GetSocket(),make_cmd(obj).c_str());
    std::cout<<"Move: " << make_cmd(obj);
    pAccCtrl->UnlockAccess();
    usleep(delta_t * 1000000);
  } while(_road > 0);

  return true;
}; 

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >>_ObjName >> _Speed_mmS >> _road;

  if (Strm_CmdsList.fail()) {
        std::cerr << "!!! ERROR: couldn't get params for Set." << std::endl;
        return false;
    }
  return true;
}


/*!
 *
 */
AbstractInterp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
std::string Interp4Move::make_cmd(std::shared_ptr<AbstractMobileObj> obj) {
    Vector3D pos = obj->GetPositoin_m();
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "UpdateObj Name=" << obj->GetName()
        << " Trans_m=(" << pos[0] << "," << pos[1] << "," << pos[2] << ")\n";
    return oss.str();
}

