#pragma once
#include <string>
#include <dlfcn.h>
#include "AbstractInterp4Command.hh"


class LibInterface {
public:
    LibInterface(const std::string &libName);
    ~LibInterface();

    void* _LibHandler;
    std::string _CmdName;
    AbstractInterp4Command *(*_pCreateCmd)(void);

private:
    bool loadLib();
    bool unloadLib();
};