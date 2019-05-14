//-------------------------------------------------------------------------------
//-- TestMenu.cpp ------------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "TestMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @TestMenu::TestMenu()
//-------------------------------------------------------------------------------
TestMenu::TestMenu()
{
    MeshManager meshManager;
    SkyBox skyBox;
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(75.0, 0.1, 450.0, 1280, 720);
    camera->setLookAt({20,20,20});
    camera->setPosition({0,-50,0});
    camera->setRotation({0,0,1});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootTestMenu");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    std::shared_ptr<SceneNode> backQuad=HelperManager::BuildTexturedQuad("backTest",HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AlphaChanger"),"tr_back.tga");
    
    std::shared_ptr<SceneNode> box=HelperManager::BuildBox("box", HelperManager::CreateMeshInstance(meshManager.GetMesh("box")));
    std::shared_ptr<SceneNode> sky=skyBox.getSky();
    
    box->setLocalTransform({0,0,1}, {0,0,0}, {2,2,2});
    backQuad->setLocalTransform({14,0,-8}, {0,4.72,1}, {4,4,4});
    sky->setLocalTransform({0,0,0}, {0,0,0}, {50,50,50});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    menu->setRoot(root);

    // menu->getRoot()->addChild(box);
       menu->getRoot()->addChild(backQuad);
    // menu->getRoot()->addChild(sky);
    
    Terrain terrain(12,12);
    std::shared_ptr<SceneNode> normals=std::make_shared<SceneNode>("normals");
   
    std::shared_ptr<SceneNode> line;
    for(auto val:terrain.getNormal())
    {
        std::shared_ptr<Mesh> mesh=std::make_shared<Mesh>();
        
        IvVertexFormat format=IvVertexFormat::kCPFormat;
        std::vector<IvCPVertex> vertices;
        std::vector<unsigned int> indices;
        
        IvCPVertex vertex1;
        IvCPVertex vertex2;
        
        vertex1.position={20,20,20};
        vertex2.position={40,40,40};//{val.x,val.y+14,val.z};
        
        vertex1.color={255,0,0,255};
        vertex2.color={255,255,0,255};
        
        vertices.push_back(vertex1);
        vertices.push_back(vertex2);
        
        mesh->setVertexBuffer(vertices,format);
        
        std::shared_ptr<MeshInstance> meshInstance=std::make_shared<MeshInstance>();
        meshInstance->setMesh(mesh);
        meshInstance->setShader("BasicShader");
        
        RenderPacket m_renderPacket;
        m_renderPacket._use_blend = true;
        m_renderPacket._use_depth = true;
        m_renderPacket._use_wireframe = false;
        m_renderPacket._prim_type = kLineListPrim;
        
        line = std::make_shared<HelperSceneNode>("testLine", m_renderPacket);
        
        normals->addChild(line);
    }
   
    menu->getRoot()->addChild(terrain.getTerrain());
    menu->getRoot()->addChild(normals);

    normals->setLocalPosition({0,0,0});
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
}
//-------------------------------------------------------------------------------
// @TestMenu::~TestMenu()
//-------------------------------------------------------------------------------
TestMenu::~TestMenu()
{
    
}
//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------




