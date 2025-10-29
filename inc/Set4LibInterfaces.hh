#pragma once

#include <unordered_map>
#include <memory>
#include <iostream>

#include "ExecPreprocesor.hh"
#include "LibInterface.hh"

class Set4LibInterfaces{
    std::unordered_map<std::string, std::shared_ptr<LibInterface>> _cmds;
public:
    Set4LibInterfaces();
    bool execFileCmds(std::string fileName);
};