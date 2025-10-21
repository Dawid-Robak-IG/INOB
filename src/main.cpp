#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "AbstractInterp4Command.hh"
#include "ExecPreprocesor.hh"

using namespace std;

void test_exec_pp();

int main()
{
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  AbstractInterp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);


  AbstractInterp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Move);
}
void test_exec_pp(){
  const char* file="test1.txt";
  istringstream string_stream;
  execPreprocesor(file, string_stream);
  std::cout<<string_stream.str()<<'\n';
}