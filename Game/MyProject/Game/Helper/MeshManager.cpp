//-------------------------------------------------------------------------------
//-- MeshManager.cpp ------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "MeshManager.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @ MeshManager::GetMesh()
//-------------------------------------------------------------------------------
std::shared_ptr<Mesh>
MeshManager::GetMesh(const std::string& name)
{
    std::map<std::string,bool>::iterator iterator;
    iterator=createdMeshes.find(name);
    
    if(iterator==createdMeshes.end())
    {
        std::shared_ptr<Mesh> mesh;
        
        if(name=="box")
            mesh=HelperManager::CreateBoxMesh();
        else if(name=="quad")
            mesh=HelperManager::CreateQuadMesh();
        else if(name=="sphere")
            mesh=HelperManager::CreateSphereMesh();
        
        if(mesh!=nullptr)
        {
            meshes.insert(std::pair<std::string,std::shared_ptr<Mesh>>(name,mesh));
            createdMeshes.insert(std::pair<std::string, bool>(name,true));
        }
    }

    std::map<std::string,std::shared_ptr<Mesh>>::iterator it;
    it=meshes.find(name);

    if(it!=meshes.end())
        return it->second;
    else
        return nullptr;
}

