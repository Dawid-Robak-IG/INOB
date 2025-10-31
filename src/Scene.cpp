#include "Scene.hh"


std::shared_ptr<AbstractMobileObj> Scene::FindMobileObj(const char *sName){
    auto obj = _Set_MobileObjts.find(sName);
    if(obj == _Set_MobileObjts.end()){
        return nullptr;
    }
    return obj->second;
}
void Scene::AddMobileObj(std::shared_ptr<AbstractMobileObj> pMobObj){
    try{
        _Set_MobileObjts.emplace(pMobObj->GetName(),pMobObj);
    } catch(const std::exception &e) {
        std::cerr << "Failed to add object to scene " << e.what() << '\n';
    }
}
void Scene::AddMobileObjs(std::vector<Cube> &cubes){
    for(auto cube: cubes){
        auto obj = MakeCube(cube);
        AddMobileObj(obj);
    }
}

std::shared_ptr<AbstractMobileObj> Scene::MakeCube(const Cube &cube)
{
    Vector3D base = {0, 0, 0};
    Vector3D shifted = base + cube._shift;
    Vector3D scaled = normal_multi(shifted,cube._scale);
    Vector3D rotated = RotateVector(scaled, cube._rot_xyz_deg);
    Vector3D final_pos = rotated + cube._trans_m;

    auto new_obj = std::make_shared<CubeObj>();
    new_obj->SetName(cube._name.c_str());
    new_obj->SetPosition_m(final_pos);
    new_obj->SetRPY(cube._rot_xyz_deg);

    return std::static_pointer_cast<AbstractMobileObj>(new_obj);
}