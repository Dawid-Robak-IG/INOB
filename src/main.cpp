#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <unordered_map>
#include "AbstractInterp4Command.hh"
#include "ExecPreprocesor.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include "ProgramInterpreter.hh"

using namespace std;

void test_exec_pp();
int zalazek();
int test_plugin(string plugin, string test_file);
int test_RCmd4Lib(std::unordered_map<std::string,std::string> &Cmd4Lib,string test_file); 
// int test_set4lib();

int main()
{
  // std::unordered_map<std::string,std::string> Cmd4Lib = {
  //   {"Move","libInterp4Move.so"},
  //   {"Set","libInterp4Set.so"},
  //   {"Rotate","libInterp4Rotate.so"},
  //   {"Pause","libInterp4Pause.so"}
  // };

  // test_exec_pp();
  // test_plugin("libInterp4Move.so","moveTest.txt");
  // test_plugin("libInterp4Set.so","setTest.txt");
  // test_plugin("libInterp4Rotate.so","rotateTest.txt");
  // test_plugin("libInterp4Pause.so","pauseTest.txt");
  // test_RCmd4Lib(Cmd4Lib,"test1.txt");
  
  ProgramInterpreter pr_int;
  pr_int.Read_XML_Config("config/config.xml");
  pr_int.ExecProgram("to_config.txt");
  
  return 0;
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
int test_plugin(string plugin, string test_file){
  LibInterface libInterface(plugin);
  AbstractInterp4Command* cmd = libInterface._pCreateCmd();

  cout << endl;
  cout << cmd->GetCmdName() << endl;
  cout << endl;
  cmd->PrintSyntax();
  cout << endl;
  cmd->PrintCmd();
  cout << endl;

  std::istringstream Stream;
  execPreprocesor(test_file.c_str(),Stream);
  cout << "Preprocesor streamout: " << Stream.str() << endl;
  std::string tmp;
  Stream >> tmp;
  cmd->ReadParams(Stream);
  cmd->PrintCmd();
  cout << endl;

  return 0;
}
int test_RCmd4Lib(std::unordered_map<std::string,std::string> &Cmd4Lib,string test_file){
  std::istringstream Stream;
  execPreprocesor(test_file.c_str(),Stream);
  cout << "Preprocesor streamout: " << endl << Stream.str() << endl;
  cout << "======" << endl;
  string cmd_name;
  while(Stream >> cmd_name){
    cout << Cmd4Lib[cmd_name] << ' ';
  }

  return 0;
}
// int test_set4lib(){
//   Set4LibInterfaces set4interfaces;

//   set4interfaces.execFileCmds("test1.txt");
//   return 0;
// }