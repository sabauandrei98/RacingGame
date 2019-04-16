//-------------------------------------------------------------------------------
//-- TestHelper.h -------------------------------------------------------------
//-------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "../Helper/HelperManager.h"
#include "../Helper/HelperClass.h"
//-------------------------------------------------------------------------------
//-- Typedefs, Structs ----------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Classes --------------------------------------------------------------------
//-------------------------------------------------------------------------------
class TestHelper
{
  
public:
    //constructor/destructor
    TestHelper(){}
    ~TestHelper(){}
    void Setup();
    void Draw();
private:
    std::shared_ptr<HelperManager>                   helper;
    std::shared_ptr<HelperClass>                     helperClass;
    
    std::shared_ptr<Mesh>                            boxMesh;
    std::shared_ptr<Mesh>                            quadMesh;
    std::shared_ptr<Mesh>                            sphereMesh;
    std::vector<std::shared_ptr<MeshInstance>>       boxMeshInstances;
    std::vector<std::shared_ptr<MeshInstance>>       quadMeshInstances;
    std::shared_ptr<MeshInstance>                    sphereMeshInstance;
    
    std::vector<bool>                                createdBoxes;
    std::vector<bool>                                createdQuads;
    bool                                             createdSphere      =   false;
};
