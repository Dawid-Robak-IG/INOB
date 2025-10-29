#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces(){
    LibInterface *moveInt = new LibInterface("libInterp4Move.so");
    LibInterface *setInt = new LibInterface("libInterp4Set.so");
    LibInterface *pauseInt = new LibInterface("libInterp4Pause.so");
    LibInterface *rotInt = new LibInterface("libInterp4Rotate.so");

    _cmds.emplace(moveInt->_pCreateCmd()->GetCmdName(),moveInt);
    _cmds.emplace(setInt->_pCreateCmd()->GetCmdName(),setInt);
    _cmds.emplace(pauseInt->_pCreateCmd()->GetCmdName(),pauseInt);
    _cmds.emplace(rotInt->_pCreateCmd()->GetCmdName(),rotInt);
}

bool Set4LibInterfaces::execFileCmds(std::string fileName){
    std::istringstream Stream;
    execPreprocesor(fileName.c_str(),Stream);
    std::cout << "\033[44m" << "Preprocesor streamout: " << std::endl << Stream.str() << std::endl;
    std::cout << "======" << "\033[0m" << std::endl;
    std::string cmd_name;
    while(Stream >> cmd_name){
        std::cout << "\33[32m" << "Read cmd: " << cmd_name << "\33[0m" << std::endl;
        auto it = _cmds.find(cmd_name);
        AbstractInterp4Command *cmd;

        if(it == _cmds.end()){
            std::cout << "\33[31m" << "Couldn't find command" << "\33[0m" << std::endl;
            return false;
        } else{
            std::shared_ptr<LibInterface> lib = it->second;
            cmd = lib->_pCreateCmd();
        }
        cmd->ReadParams(Stream);
        cmd->PrintCmd();
        // cmd->ExecCmd();
        std::cout << std::endl;
    }
    return true;
}
