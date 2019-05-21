//-------------------------------------------------------------------------------
//-- RaceMenu.cpp ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "RaceMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @RaceMenu::RaceMenu()
//-------------------------------------------------------------------------------
RaceMenu::RaceMenu()
{
    meshManager=MeshManager();
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(80.0, 0.1, 700.0, 1280, 720);
    camera->setLookAt({0,-25,0});
    camera->setPosition({0,0,0});
    camera->setRotation({0,1,0});
    
    menu=std::make_shared<SceneGraph>();
    std::shared_ptr<SceneNode> root=std::make_shared<SceneNode>("rootRace");
    
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    uniforms.push_back("row");
    uniforms.push_back("column");
    uniforms.push_back("noRows");
    uniforms.push_back("noColumns");
    
    std::shared_ptr<SceneNode> info=std::make_shared<SceneNode>("infoRoot");
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    std::shared_ptr<SceneNode> _child1 = HelperManager::BuildSphere("sphere", HelperManager::CreateMeshInstance( meshManager.GetMesh("sphere")));
    std::shared_ptr<SceneNode>  _child2 = ModelLoader::loadModel("jeep.fbx", "example_shader");
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<MeshInstance> mesh_instance = std::make_shared<MeshInstance>();
    std::vector<IvTCPVertex> vertices;
    
    std::shared_ptr<CarController> _controller = std::make_shared<CarController>();
    _child2->setAnimator(_controller);
    
    RoadImporterExporter* roadIE = new RoadImporterExporter();
    roadIE->importFrom("roadDataTest.txt");
    std::shared_ptr<RoadNode> roadNode = std::make_shared<RoadNode>("roadNode", roadIE->getMarginPoints());
    roadNode->setLocalTransform(IvVector3{0,-0.5,0}, IvVector3{3.144,0,0}, IvVector3{12,12,12});
    
    std::shared_ptr<SceneNode> environment=std::make_shared<Environment>("environment",roadIE->getMarginPoints());
    
    delete roadIE;
    
    environment->setLocalTransform({0,10,0}, {0,0,0}, {2,2,2});
    cameraSceneNode->setAbsolutePosition(IvVector3(0.f, 3.f, -15.f));
    
    cameraSceneNode->setAnimator(std::make_shared<CameraFollowAnimator>(_child2.get(), IvVector2(3.f, 10.f), true));
    
    menu->setRoot(root);
    menu->getRoot()->addChild(_child2);
    menu->getRoot()->addChild(roadNode);
    menu->getRoot()->addChild(environment);
    menu->getRoot()->addChild(info);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
    
    
}
//-------------------------------------------------------------------------------
// @RaceMenu::~RaceMenu()
//-------------------------------------------------------------------------------
RaceMenu::~RaceMenu()
{
    
}
//-------------------------------------------------------------------------------
// @RaceMenu::renderNo()
//-------------------------------------------------------------------------------
void
RaceMenu::renderNo(uint32_t no,const IvVector3& position)
{
    auto val=getRowCol(no%10 +'0');
    
    std::string name="count"+std::to_string(noDigits(no%10));
    const char* quadName=name.c_str();
    
    auto root=getScene()->getRoot();
    auto first=root->findFirstNodeWithName("infoRoot");
    auto count1=first->findFirstNodeWithName("count1");
    if(count1==nullptr && no==0)
    {
        //rendering first quad
        std::vector<std::string> uniforms;
        uniforms.push_back("mTexture");
        uniforms.push_back("row");
        uniforms.push_back("column");
        
        std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad(quadName,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");
        
        countScoreQuad->setLocalTransform(position , IvVector3{4.72,1.5,4.72}, IvVector3{1,1,1});
        first->addChild(countScoreQuad);
        
        auto quad=root->findFirstNodeWithName(quadName);
        quad->getRenderable()->setUniformValue(1, val.first);
        quad->getRenderable()->setUniformValue(2, val.second);
    }
    else if(count1==nullptr)
    {
        //after pause state
        renderScore(no,position);
    }
    else
    {
        auto renderable=root->findFirstNodeWithName(quadName)->getRenderable();
        renderable->setUniformValue(1, val.first);
        renderable->setUniformValue(2, val.second);
    }
    
    if(noDigits(no)>noDigits(no-1))
        addNewDigit(no);
    
    checkNeedChangeDigit(no);

}
//-------------------------------------------------------------------------------
// @RaceMenu::noDigits()
//-------------------------------------------------------------------------------
unsigned int
RaceMenu::noDigits(uint32_t number)
{
    if(number<10)
        return 1;
    else
        return 1+noDigits(number/10);
}
//-------------------------------------------------------------------------------
// @RaceMenu::addNewDigit()
//-------------------------------------------------------------------------------
void
RaceMenu::addNewDigit(uint32_t no)
{
    //create a new quad
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    uniforms.push_back("row");
    uniforms.push_back("column");
    
    std::string name="count"+std::to_string(noDigits(no));
    
    const char* quadName=name.c_str();
    
    std::string preName="count"+std::to_string(noDigits(no-1));
    
    const char* previousQuadName=preName.c_str();
    
    std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad(quadName,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");
    
    auto root=getScene()->getRoot();
    auto previousPos=root->findFirstNodeWithName(previousQuadName)->getLocalPosition();
    
    countScoreQuad->setLocalTransform(IvVector3{previousPos.x+0.8f,previousPos.y,previousPos.z}, IvVector3{4.72,1.5,4.72}, IvVector3{1,1,1});
    
    root->findFirstNodeWithName("infoRoot")->addChild(countScoreQuad);
    
    auto val=getRowCol(no%10 +'0');
    
    name="count"+std::to_string(noDigits(no%10));
    
    quadName=name.c_str();
    
    auto valueRenderable=root->findFirstNodeWithName(quadName)->getRenderable();
    valueRenderable->setUniformValue(1, val.first);
    valueRenderable->setUniformValue(2, val.second);
    
    if(no>=10)
    {
        val=getRowCol(firstDigit(no)+'0');
        
        name="count"+std::to_string(noDigits(no));
        
        quadName=name.c_str();
        
        valueRenderable=root->findFirstNodeWithName(quadName)->getRenderable();
        valueRenderable->setUniformValue(1, val.first);
        valueRenderable->setUniformValue(2, val.second);
    }
}

void
RaceMenu::checkNeedChangeDigit(uint32_t no)
{
    auto aux =no-1;
    auto noDigits = 1;
    auto continue_ = false;
    
    while(aux!=0)
    {
        continue_=false;
        
        if(aux%10==9 )
        {
            continue_=true;
            
            std::string name="count"+std::to_string(noDigits+1);
            
            const char* quadName=name.c_str();
            
            char ch=(aux/10%10+1)%10 +'0';
            
            auto val=getRowCol(ch);
            auto node=getScene()->getRoot()->findFirstNodeWithName(quadName);
            if(node!=nullptr)
            {
                node->getRenderable()->setUniformValue(1, val.first);
                node->getRenderable()->setUniformValue(2, val.second);
            }
        }
        
        if(!continue_)
            break;
        
        aux/=10;
        noDigits++;
    }
}

int RaceMenu::firstDigit(uint32_t no)
{
    while (no >= 10)
        no /= 10;
    
    return no;
}

void RaceMenu::renderScore(uint32_t no,const IvVector3& position)
{
    int auxScore=no;
    int noDig=noDigits(no);
    
    while(noDig!=0)
    {
        std::string name="count"+std::to_string(noDigits(no)-noDig + 1);
        const char* quadName=name.c_str();
        
        std::vector<std::string> uniforms;
        uniforms.push_back("mTexture");
        uniforms.push_back("row");
        uniforms.push_back("column");
        
        std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad(quadName,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");
        
        std::string n="count"+std::to_string(noDigits(no)-noDig );
        const char* prevName=n.c_str();
        
        auto root=getScene()->getRoot();
        
        if(root->findFirstNodeWithName("infoRoot")->findFirstNodeWithName(prevName)==nullptr)
            countScoreQuad->setLocalTransform(position, IvVector3{4.72,1.5,4.72}, IvVector3{1,1,1});
        else
        {
            auto previousPos=getScene()->getRoot()->findFirstNodeWithName(prevName)->getLocalPosition();
            countScoreQuad->setLocalTransform(IvVector3{previousPos.x+0.8f,previousPos.y,previousPos.z}, IvVector3{4.72,1.5,4.72}, IvVector3{1,1,1});
        };
        
        root->findFirstNodeWithName("infoRoot")->addChild(countScoreQuad);
        
        auto val=getRowCol(auxScore%10 + '0');
        auto renderable=root->findFirstNodeWithName(quadName)->getRenderable();
        
        renderable->setUniformValue(1, val.first);
        renderable->setUniformValue(2, val.second);
        
        auxScore/=10;
        noDig--;
    }
}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------


