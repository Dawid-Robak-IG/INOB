#include "Cube.hh"

Cube::Cube(): _shift({0,0,0}), 
          _scale({1,1,1}), 
          _rot_xyz_deg({0,0,0}), 
          _trans_m({0,0,0}), 
          _rgb({128,128,128}),
          _name("ERROR"){}


bool Cube::setShift(std::istringstream &stream){
    stream >> _shift;
    if (stream.fail()) {
        std::cerr << " Blad!!!" << std::endl;
        return false;
    } else {
        std::cout << " Czytanie wartosci OK!!!" << std::endl;
        std::cout << _shift << std::endl;
    }
    return true;
}
bool Cube::setScale(std::istringstream &stream){
    stream >> _scale;
    if (stream.fail()) {
        std::cerr << " Blad!!!" << std::endl;
        return false;
    } else {
        std::cout << " Czytanie wartosci OK!!!" << std::endl;
        std::cout << _scale << std::endl;
    }
    return true;
}
bool Cube::setRot(std::istringstream &stream){
    stream >> _rot_xyz_deg;
    if (stream.fail()) {
        std::cerr << " Blad!!!" << std::endl;
        return false;
    } else {
        std::cout << " Czytanie wartosci OK!!!" << std::endl;
        std::cout << _rot_xyz_deg << std::endl;
    }
    return true;
}
bool Cube::setTransM(std::istringstream &stream){
    stream >> _trans_m;
    if (stream.fail()) {
        std::cerr << " Blad!!!" << std::endl;
        return false;
    } else {
        std::cout << " Czytanie wartosci OK!!!" << std::endl;
        std::cout << _trans_m << std::endl;
    }
    return true;
}
bool Cube::setRGB(std::istringstream &stream){
    stream >> _rgb;
    if (stream.fail()) {
        std::cerr << " Blad!!!" << std::endl;
        return false;
    } else {
        std::cout << " Czytanie wartosci OK!!!" << std::endl;
        std::cout << _rgb << std::endl;
    }
    return true;
}
bool Cube::print(){
    if(!strcmp(_name.c_str(),"ERRO")){
        std::cerr << "Name wasn't set for cube\n";
        return false;
    }
    std::cout << " Atrybuty Cube:" << std::endl
      << "     Name = \"" << _name << "\"" << std::endl
      << "     Shift = \"" << _shift << "\"" << std::endl
      << "     Scale = \"" << _scale << "\"" << std::endl  
      << "     Rot = \"" << _rot_xyz_deg << "\"" << std::endl  
      << "     Trans_m = \"" << _trans_m << "\"" << std::endl   
      << "     RGB = \"" << _rgb << "\"" << std::endl    
      << std::endl;
      return true;
}
std::string Cube::get_cmd(){
    std::string res = "AddObj Name=" + _name
      + " RGB="+bracket(_rgb)
      + " Scale="+bracket(_scale)
      + " RotXYZ_deg"+bracket(_rot_xyz_deg)
      + " Trans_m="+bracket(_trans_m)+"\n";
    return res;
}