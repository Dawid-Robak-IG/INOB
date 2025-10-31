#include "Configuration.hh"



bool Configuration::addLib(const char* name){
    try {
        _libsNames.emplace_back(name);
        std::cout << "Added new lib to config: " << _libsNames.back() << '\n';
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to add lib to config: " << e.what() << '\n';
        return false;
    }
}
bool Configuration::addCube(Cube &cube){
    try {
        _cubes.emplace_back(cube);
        std::cout << "Added new cube to config: " << _cubes.back() << '\n';
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to add cube to config: " << e.what() << '\n';
        return false;
    }
}
std::vector<std::string>& Configuration::getLibs() {
    return _libsNames;
}
std::string Configuration::GetObjCmds(){
    std::string res;
    for(auto &cube: _cubes){
        res += cube.get_cmd();
    }
    return res;
}