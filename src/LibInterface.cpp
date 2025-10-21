#include "LibInterface.hh"

LibInterface::LibInterface(const std::string &libName): _LibHandler(nullptr), _CmdName(libName), _pCreateCmd(nullptr){
    if(!loadLib()){
        std::cout << "\033[31m"
              << "Couldn't load lib: "
              << libName
              << "\033[0m"
              << std::endl;
        exit(1);
    }

}
LibInterface::~LibInterface(){
    if(!unloadLib()){
        std::cout << "\033[31m"
              << "Couldn't unload lib: "
              << _CmdName
              << "\033[0m"
              << std::endl;
        exit(1);
    }
}

bool LibInterface::loadLib(){
    _LibHandler = dlopen(_CmdName.c_str(), RTLD_LAZY);
    if(!_LibHandler){
        return false;
    }

    _pCreateCmd = (AbstractInterp4Command*(*)(void))dlsym(_LibHandler, "CreateCmd");
    if(!_pCreateCmd){
        dlclose(_LibHandler);
        _LibHandler = nullptr;
        return false;
    }
    return true;
}
bool LibInterface::unloadLib(){
    if(_LibHandler){
        dlclose(_LibHandler);
        _LibHandler = nullptr;
        _pCreateCmd = nullptr;
        return true;
    }
    return false;
}
