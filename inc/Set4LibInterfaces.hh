#pragma once

#include <unordered_map>
#include <iostream>

#include "ExecPreprocesor.hh"
#include "LibInterface.hh"

class Set4LibInterfaces{
    std::unordered_map<std::string, void*> _cmds;
    std::string _fileName;
public:
    Set4LibInterfaces(std::string file_name);
    bool execFileCmds();
};