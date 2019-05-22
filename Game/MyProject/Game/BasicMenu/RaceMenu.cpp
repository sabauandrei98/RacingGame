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
    std::shared_ptr<SceneNode> score=std::make_shared<SceneNode>("scoreRoot");
    std::shared_ptr<SceneNode> lap=std::make_shared<SceneNode>("lapRoot");
    std::shared_ptr<SceneNode> checkpoint=std::make_shared<SceneNode>("checkpointRoot");
    std::shared_ptr<SceneNode> lapTime=std::make_shared<SceneNode>("lapTimeRoot");
    std::shared_ptr<SceneNode> carSpeed=std::make_shared<SceneNode>("carSpeedRoot");
    std::shared_ptr<SceneNode> time=std::make_shared<SceneNode>("timeRoot");
    
    std::shared_ptr<SceneNode> infoText=std::make_shared<SceneNode>("infoTextRoot");
    std::shared_ptr<SceneNode> scoreText=std::make_shared<SceneNode>("scoreTextRoot");
    std::shared_ptr<SceneNode> lapText=std::make_shared<SceneNode>("lapTextRoot");
    std::shared_ptr<SceneNode> checkpointText=std::make_shared<SceneNode>("checkpointTextRoot");
    std::shared_ptr<SceneNode> lapTimeText=std::make_shared<SceneNode>("lapTimeTextRoot");
    std::shared_ptr<SceneNode> carSpeedText=std::make_shared<SceneNode>("carSpeedTextRoot");
    std::shared_ptr<SceneNode> timeText=std::make_shared<SceneNode>("timeTextRoot");
    
    //info->addChild(scoreText);
    info->addChild(score);
    
  //  info->addChild(lapText);
    info->addChild(lap);
    
   // info->addChild(checkpointText);
    info->addChild(checkpoint);
    
    //info->addChild(lapTimeText);
    info->addChild(lapTime);
    
    //info->addChild(carSpeedText);
    info->addChild(carSpeed);
    
    info->addChild(timeText);
    info->addChild(time);
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    std::shared_ptr<SceneNode> carNode = ModelLoader::loadModel("jeep.fbx", "example_shader");
    
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<MeshInstance> mesh_instance = std::make_shared<MeshInstance>();
    std::vector<IvTCPVertex> vertices;
    
    std::shared_ptr<CarController> _controller = std::make_shared<CarController>();
    carNode->setAnimator(_controller);
    carNode->setName("Car");
    
    RoadImporterExporter roadIE;
    roadIE.importFrom("roadDataTest.txt");
    std::shared_ptr<RoadNode> roadNode = std::make_shared<RoadNode>("roadNode", roadIE.getMarginPoints(), 10.0f);
    roadNode->setLocalTransform(IvVector3{0,-0.5,0}, IvVector3{0,0,0}, IvVector3{1,1,1});
    
    std::shared_ptr<SceneNode> environment=std::make_shared<Environment>("environment",roadIE.getMarginPoints());
    
    timeText->setLocalPosition(     {-2, 1.5,-1});
    
    time->setLocalPosition(         {-2, -1.5,-1});
    lap->setLocalPosition(          {-2, -2,  -1});
    lapTime->setLocalPosition(      {-2, -2.5,-1});
    
    score->setLocalPosition(        {-6, -1.5,-1});
    checkpoint->setLocalPosition(   {-6, -2., -1});
    carSpeed->setLocalPosition(     {-6, -2.5,-1});
    
    environment->setLocalTransform({0,10,0}, {0,0,0}, {2,2,2});
    cameraSceneNode->setAbsolutePosition(IvVector3(0.f, 3.f, -15.f));
    
    cameraSceneNode->setAnimator(std::make_shared<CameraFollowAnimator>(carNode.get(), IvVector2(3.f, 10.f), true));
    
    IvVector3 pos = roadIE.getMarginPoints()[0].first + roadIE.getMarginPoints()[0].second;
    pos *= 10.0;
    pos /= 2.0;
    
    carNode->addChild(info);
    carNode->setLocalPosition(pos);
    info->setLocalTransform( -pos + IvVector3{0,10,0} , {0,0,0} ,{3.5,3.5,3.5});
    
    menu->setRoot(root);
    menu->getRoot()->addChild(roadNode);
    menu->getRoot()->addChild(environment);
    menu->getRoot()->addChild(carNode);
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
// @RaceMenu::renderDigit()
//-------------------------------------------------------------------------------
void
RaceMenu::renderDigit(std::string name,uint32_t no)
{
    auto val=getRowCol(no%10 +'0');
    
    std::string m_name="count"+std::to_string(noDigits(no%10));
    const char* quadName=m_name.c_str();

    auto root=getScene()->getRoot()->findFirstNodeWithName("infoRoot");
    auto first=root->findFirstNodeWithName(name);
    auto count1=first->findFirstNodeWithName("count1");
    if(count1==nullptr && no==0)
    {
        //rendering first quad
        std::vector<std::string> uniforms;
        uniforms.push_back("mTexture");
        uniforms.push_back("row");
        uniforms.push_back("column");

        std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad(quadName,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");

        countScoreQuad->setLocalTransform(first->getAbsolutePosition(), IvVector3{4.72,1.5,4.72}, IvVector3{1,1,1});
        first->addChild(countScoreQuad);

        auto renderable=first->findFirstNodeWithName(quadName)->getRenderable();
        if(renderable!=nullptr)
        {
            renderable->setUniformValue(1, val.first);
            renderable->setUniformValue(2, val.second);
        }
    }
    else if(count1==nullptr)
    {
        //after pause state
        renderNumber(name,no,first->getAbsolutePosition());
    }
    else
    {
        auto renderable=first->findFirstNodeWithName(quadName)->getRenderable();
        if(renderable!=nullptr)
        {
            renderable->setUniformValue(1, val.first);
            renderable->setUniformValue(2, val.second);
        }
    }

    if(noDigits(no)>noDigits(no-1))
        addNewDigit(name,no);

    checkNeedChangeDigit(no);

}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------

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
RaceMenu::addNewDigit(std::string name,uint32_t no)
{
    //create a new quad
    std::vector<std::string> uniforms;
    uniforms.push_back("mTexture");
    uniforms.push_back("row");
    uniforms.push_back("column");
    
    std::string m_name="count"+std::to_string(noDigits(no));
    
    const char* quadName=m_name.c_str();
    
    std::string preName="count"+std::to_string(noDigits(no-1));
    
    const char* previousQuadName=preName.c_str();
    
    std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad(quadName,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");
    
    auto root=getScene()->getRoot()->findFirstNodeWithName("infoRoot");
    auto previousPos=root->findFirstNodeWithName(name)->findFirstNodeWithName(previousQuadName)->getLocalPosition();
    
    countScoreQuad->setLocalTransform(IvVector3{previousPos.x+0.8f,previousPos.y+0.05f,previousPos.z}, IvVector3{4.72,1.5,4.72}, IvVector3{1,1,1});
    
    root->findFirstNodeWithName(name)->addChild(countScoreQuad);
    
    auto val=getRowCol(no%10 +'0');
    
    m_name="count"+std::to_string(noDigits(no%10));
    
    quadName=m_name.c_str();
    
    auto renderable=root->findFirstNodeWithName(quadName)->getRenderable();
    if(renderable!=nullptr)
    {
        renderable->setUniformValue(1, val.first);
        renderable->setUniformValue(2, val.second);
    }
    
    if(no>=10)
    {
        val=getRowCol(firstDigit(no)+'0');
        
        m_name="count"+std::to_string(noDigits(no));
        
        quadName=m_name.c_str();
        
        renderable=root->findFirstNodeWithName(quadName)->getRenderable();
        if(renderable!=nullptr)
        {
            renderable->setUniformValue(1, val.first);
            renderable->setUniformValue(2, val.second);
        }
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
                auto renderable=node->getRenderable();
                renderable->setUniformValue(1, val.first);
                renderable->setUniformValue(2, val.second);
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

void RaceMenu::renderNumber(std::string name,uint32_t no,const IvVector3& position)
{
    int auxScore=no;
    int noDig=noDigits(no);
    
    while(noDig!=0)
    {
        std::string m_name="count"+std::to_string(noDigits(no)-noDig + 1);
        const char* quadName=m_name.c_str();
        
        std::vector<std::string> uniforms;
        uniforms.push_back("mTexture");
        uniforms.push_back("row");
        uniforms.push_back("column");
        
        std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad(quadName,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");
        
        std::string n="count"+std::to_string(noDigits(no)-noDig );
        const char* prevName=n.c_str();
        
        auto root=getScene()->getRoot()->findFirstNodeWithName("infoRoot");
        auto specificRoot=root->findFirstNodeWithName(name);
        
        if(specificRoot->findFirstNodeWithName(prevName)==nullptr)
            countScoreQuad->setLocalTransform(specificRoot->getAbsolutePosition(), IvVector3{4.72,1.5,4.72}, IvVector3{1,1,1});
        else
        {
            auto previousPos=getScene()->getRoot()->findFirstNodeWithName(prevName)->getLocalPosition();
            countScoreQuad->setLocalTransform(IvVector3{previousPos.x+0.8f,previousPos.y,previousPos.z}, IvVector3{4.72,1.5,4.72}, IvVector3{1,1,1});
        };
        
        specificRoot->addChild(countScoreQuad);
        
        auto val=getRowCol(auxScore%10 + '0');
        auto renderable=root->findFirstNodeWithName(quadName)->getRenderable();
        
        if(renderable!=nullptr)
        {
            renderable->setUniformValue(1, val.first);
            renderable->setUniformValue(2, val.second);
        }
        auxScore/=10;
        noDig--;
    }
}

//-------------------------------------------------------------------------------
// @RaceMenu::renderDigit()
//-------------------------------------------------------------------------------
void RaceMenu::renderText(std::string name, std::string text)
{
    auto root = getScene()->getRoot()->findFirstNodeWithName(name);
    if(root!=nullptr)
    {
        std::vector<std::string> uniforms;
        uniforms.push_back("mTexture");
        uniforms.push_back("row");
        uniforms.push_back("column");
        
        std::string n="textQuad"+text;
        const char* _name=n.c_str();
        
        auto position=root->getLocalPositon();
        std::vector<std::shared_ptr<SceneNode> > quads;
        root->findAllNodesWithName(_name,quads);
        
        if(quads.size()==0)
        {
            for(auto& ch :text)
            {
                auto quad=HelperManager::BuildTexturedQuad(_name,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");
                
                quad->setLocalTransform(position, IvVector3{4.72,1.5,4.72}, IvVector3{1,1,1});
                
                root->addChild(quad);
                
                auto val=getRowCol(ch);
                
                auto renderable=quad->getRenderable();
                renderable->setUniformValue(1, val.first);
                renderable->setUniformValue(2, val.second);
            }
        }
        else
        {
            for(auto & quad:quads)
            {
                quad->setLocalPosition(position);
                position+={-0.5,0,0};
            }
        }
       
    }
}




