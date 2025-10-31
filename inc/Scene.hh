#pragma once

#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>

#include "AbstractScene.hh"
#include "CubeObj.hh"
#include "Cube.hh"


class Scene: AbstractScene{
    std::unordered_map<std::string, std::shared_ptr<AbstractMobileObj>> _Set_MobileObjts;
public:
    std::shared_ptr<AbstractMobileObj>  FindMobileObj(const char *sName) override;
    void AddMobileObj(std::shared_ptr<AbstractMobileObj> pMobObj) override;
    void AddMobileObjs(std::vector<Cube> &cubes);

    std::unordered_map<std::string, std::shared_ptr<AbstractMobileObj>> &GetObjs(){return _Set_MobileObjts;}
private:
    std::shared_ptr<AbstractMobileObj> MakeCube(const Cube &cube);
};