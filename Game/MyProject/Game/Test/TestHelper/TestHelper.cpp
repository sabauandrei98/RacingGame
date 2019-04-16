//-------------------------------------------------------------------------------
//-- TestHelper.cpp -------------------------------------------------------------
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
//-- Dependencies ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "TestHelper.h"

void
TestHelper::Setup()
{
    helperClass=std::make_shared<HelperClass>();
    helper=std::make_shared<HelperManager>();
    
    boxMesh=helper->CreateBoxMesh();
    quadMesh=helper->CreateQuadMesh();
    sphereMesh=helper->CreateSphereMesh();
    
    createdBoxes.push_back(false);
    createdBoxes.push_back(false);
    
    createdQuads.push_back(false);
    createdQuads.push_back(false);
    createdQuads.push_back(false);
   
    
}

void
TestHelper::Draw()
{
//    //test boxes
//    //helperClass->SetWireframeState(true);
//    if(!createdBoxes[0])
//    {
//        boxMeshInstances.push_back(helper->CreateMeshInstance(boxMesh));
//        createdBoxes[0]=true;
//    }
//    helperClass->DrawBox(boxMeshInstances[0],IvVector3(0,0,0));
//
//    if(!createdBoxes[1])
//    {
//        boxMeshInstances.push_back(helper->CreateMeshInstance(boxMesh));
//        createdBoxes[1]=true;
//    }
//    helperClass->DrawBox(boxMeshInstances[1],IvVector3(1,1,1));

//    //test quads
//    if(!createdQuads[0])
//    {
//        quadMeshInstances.push_back(helper->CreateMeshInstance(quadMesh));
//        createdQuads[0]=true;
//    }
//    //helperClass->DrawQuad(quadMeshInstances[0],IvVector3::xAxis);
//
//    if(!createdQuads[1])
//    {
//        quadMeshInstances.push_back(helper->CreateMeshInstance(quadMesh));
//        createdQuads[1]=true;
//    }
//    //helperClass->DrawQuad(quadMeshInstances[1], IvVector3::zAxis);
//
//    if(!createdQuads[2])
//    {
//        quadMeshInstances.push_back(helper->CreateMeshInstance(quadMesh));
//        createdQuads[2]=true;
//    }
//   // helperClass->DrawQuad(quadMeshInstances[2], IvVector3::yAxis);
    
    
    
//    //test cross quad
//    if(!createdQuads[0])
//    {
//        quadMeshInstances.push_back(helper->CreateMeshInstance(quadMesh,"TextureShader"));
//        createdQuads[0]=true;
//    }
//    helperClass->DrawCrossQuad(quadMeshInstances[0]);
    
    //test sphere

    if(!createdSphere)
    {
        sphereMeshInstance=helper->CreateMeshInstance(sphereMesh);
        createdSphere=true;
    }
    helperClass->SetWireframeState(true);
    helperClass->DrawSphere(sphereMeshInstance);

}
