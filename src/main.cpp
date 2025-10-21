#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "AbstractInterp4Command.hh"
#include "ExecPreprocesor.hh"
#include "LibInterface.hh"

using namespace std;

void test_exec_pp();
int test_movePlugin();
int test_setPlugin();
int zalazek();

int main()
{
  // return test_movePlugin();
  return test_setPlugin();
}

void test_exec_pp(){
  const char* file="test1.txt";
  istringstream string_stream;
  execPreprocesor(file, string_stream);
  std::cout<<string_stream.str()<<'\n';
}
int zalazek(){
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

  return 0;
}
int test_movePlugin(){
  LibInterface libInterface("libInterp4Move.so");
  AbstractInterp4Command* cmd = libInterface._pCreateCmd();
  cout << endl;
  cout << cmd->GetCmdName() << endl;
  cout << endl;
  cmd->PrintSyntax();
  cout << endl;
  cmd->PrintCmd();
  cout << endl;

  std::istringstream Stream;
  execPreprocesor("moveTest.txt",Stream);
  cout << Stream.str() << endl;
  cmd->ReadParams(Stream);
  cmd->PrintCmd();
  cout << endl;

  return 0;
}
int test_setPlugin(){
  LibInterface libInterface("libInterp4Set.so");
  AbstractInterp4Command* cmd = libInterface._pCreateCmd();

  cout << endl;
  cout << cmd->GetCmdName() << endl;
  cout << endl;
  cmd->PrintSyntax();
  cout << endl;
  cmd->PrintCmd();
  cout << endl;

  std::istringstream Stream;
  execPreprocesor("setTest.txt",Stream);
  cout << Stream.str() << endl;
  cmd->ReadParams(Stream);
  cmd->PrintCmd();
  cout << endl;

  return 0;
}