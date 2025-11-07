#include "Set4LibInterfaces.hh"

Set4LibInterfaces::Set4LibInterfaces(){
}

// bool Set4LibInterfaces::execFileCmds(std::string fileName){
//     std::istringstream Stream;
//     execPreprocesor(fileName.c_str(),Stream);
//     std::cout << "\033[44m" << "Preprocesor streamout: " << std::endl << Stream.str() << std::endl;
//     std::cout << "======" << "\033[0m" << std::endl;
//     std::string cmd_name;
//     while(Stream >> cmd_name){
//         std::cout << "\33[32m" << "Read cmd: " << cmd_name << "\33[0m" << std::endl;
//         std::shared_ptr<AbstractInterp4Command> cmd;
//         cmd = find_cmd(cmd_name);
//         if(cmd == nullptr){
//             return false;
//         }
//         cmd->ReadParams(Stream);
//         cmd->PrintCmd();
//         // cmd->ExecCmd();
//         std::cout << std::endl;
//     }
//     return true;
// }

bool Set4LibInterfaces::addLibs(std::vector<std::string> &libNames){
    for(auto libName: libNames){
        std::shared_ptr<LibInterface> libInt = std::make_shared<LibInterface>(libName);
        try{
            _cmds.emplace(libInt->_pCreateCmd()->GetCmdName(),libInt);
            std::cout<<"Got new lib interface: " << libInt->_CmdName << '\n';
        }
        catch(const std::exception& e){
            std::cerr << "Failed to add lib: " << e.what() << '\n';
            return false;
        }
    }
    return true;
}
std::shared_ptr<AbstractInterp4Command> Set4LibInterfaces::find_cmd(std::string cmd_name){
        std::unordered_map<std::string, std::shared_ptr<LibInterface>>::iterator  it = _cmds.find(cmd_name);
        std::shared_ptr<AbstractInterp4Command> cmd;

        if(it == _cmds.end()){
            std::cout << "\33[31m" << "Couldn't find command: " << cmd_name << "\33[0m" << std::endl;
            return nullptr;
        } else{
            std::shared_ptr<LibInterface> lib = it->second;
            cmd = static_cast<std::shared_ptr<AbstractInterp4Command>>(lib->_pCreateCmd());
        }
        return cmd;
}