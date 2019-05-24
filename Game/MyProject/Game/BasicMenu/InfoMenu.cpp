//-------------------------------------------------------------------------------
//-- InfoMenu.cpp ---------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "InfoMenu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @InfoMenu::InfoMenu()
//-------------------------------------------------------------------------------
InfoMenu::InfoMenu()
{
    meshManager=MeshManager();
    
    std::shared_ptr<Camera> camera=std::make_shared<Camera>(45.0, 0.1, 200.0, 1280, 720);
    camera->setLookAt({0,0,0});
    camera->setPosition({0,-25,0});
    camera->setRotation({0,0,1});
    
    std::shared_ptr<CameraSceneNode> cameraSceneNode=std::make_shared<CameraSceneNode>("camera",camera);
    
    menu=std::make_shared<SceneGraph>();
    
    setCharacters();
    
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
    
    info->addChild(scoreText);
    info->addChild(score);
    
    info->addChild(lapText);
    info->addChild(lap);
    
    info->addChild(checkpointText);
    info->addChild(checkpoint);
    
    info->addChild(lapTimeText);
    info->addChild(lapTime);
    
    info->addChild(carSpeedText);
    info->addChild(carSpeed);
    
    info->addChild(timeText);
    info->addChild(time);
    
    timeText->setLocalPosition(         {-8, -1, 0.80});
    lapText->setLocalPosition(          {-8, -1, 0.10});
    lapTimeText->setLocalPosition(      {-8, -1,-0.55});
    
    scoreText->setLocalPosition(        {2, -1, 0.80});
    checkpointText->setLocalPosition(   {2, -1, 0.10});
    carSpeedText->setLocalPosition(     {2, -1,-0.55});
    
    time->setLocalPosition(             {-5, -1, -1.6});
    lap->setLocalPosition(              {-5, -1, -2.3});
    lapTime->setLocalPosition(          {-5, -1, -3.});
    
    score->setLocalPosition(            {7, -1, -1.5});
    checkpoint->setLocalPosition(       {7, -1, -2.3});
    carSpeed->setLocalPosition(         {7, -1, -3.});
    

    info->setLocalTransform( IvVector3{0,0,5} , {0,0,0} ,{1,1,1});
    
    menu->setRoot(info);
    menu->getRoot()->addChild(cameraSceneNode);
    menu->setCamera(camera);
    
}
//-------------------------------------------------------------------------------
// @InfoMenu::~InfoMenu()
//-------------------------------------------------------------------------------
InfoMenu::~InfoMenu()
{
    
}
//-------------------------------------------------------------------------------
// @InfoMenu::renderDigit()
//-------------------------------------------------------------------------------
void
InfoMenu::renderDigit(std::string name,uint32_t no)
{
    auto val=getRowCol(no%10 +'0');
    
    std::string m_name="count"+std::to_string(noDigits(no%10));
    const char* quadName=m_name.c_str();
    
    auto root=menu->getRoot();
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
        
        countScoreQuad->setLocalTransform(first->getAbsolutePosition(), IvVector3{0,4.72,1}, IvVector3{1,1,1});
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
    
    for(auto & ch : first->_children)
    {
        ch->_enabled = false;
    }
    
    auto keepNo=no;
    
    while(no != 0)
    {
        int digit = no % 10;
        auto val=getRowCol(digit+'0');
        
        m_name.clear();
        m_name ="count"+ std::to_string(noDigits(no));
        quadName=m_name.c_str();
        
        auto nd = first->findFirstNodeWithName(quadName);
        if(nd!=nullptr)
        {
            nd->_enabled = true;
            auto renderable=nd->getRenderable();
            if(renderable!=nullptr)
            {
                renderable->setUniformValue(1, val.first);
                renderable->setUniformValue(2, val.second);
            }
        }
        no = no / 10;
    }
    
    if(noDigits(keepNo)>noDigits(keepNo-1))
        addNewDigit(name,keepNo);
    
    checkNeedChangeDigit(keepNo);
}
//-------------------------------------------------------------------------------
// @RaceMenu::renderDigit()
//-------------------------------------------------------------------------------
void InfoMenu::renderText(std::string name, std::string text)
{
    auto root = menu->getRoot()->findFirstNodeWithName(name);
    if(root!=nullptr)
    {
        std::vector<std::string> uniforms;
        uniforms.push_back("mTexture");
        uniforms.push_back("row");
        uniforms.push_back("column");
        
        std::string n="textQuad"+name;
        const char* _name=n.c_str();
        
        auto position=root->getLocalPositon();
        std::vector<std::shared_ptr<SceneNode> > quads;
        root->findAllNodesWithName(_name,quads);
        
        if(quads.size()==0)
        {
            for(auto& ch :text)
            {
                auto quad=HelperManager::BuildTexturedQuad(_name,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");
                
                quad->setLocalTransform(position, IvVector3{0,4.72,1}, IvVector3{1,1,1});
                
                root->addChild(quad);
                
                auto val=getRowCol(ch);
                
                auto renderable=quad->getRenderable();
                renderable->setUniformValue(1, val.first);
                renderable->setUniformValue(2, val.second);
            }
            
            root->findAllNodesWithName(_name,quads);
            for(auto & quad:quads)
            {
                quad->setLocalPosition(position);
                position+={0.8,0,0};
            }
        }
    }
}

//-------------------------------------------------------------------------------
//  PRIVATE METHODS
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// @InfoMenu::noDigits()
//-------------------------------------------------------------------------------
unsigned int
InfoMenu::noDigits(uint32_t number)
{
    if(number<10)
        return 1;
    else
        return 1+noDigits(number/10);
}
//-------------------------------------------------------------------------------
// @InfoMenu::addNewDigit()
//-------------------------------------------------------------------------------
void
InfoMenu::addNewDigit(std::string name,uint32_t no)
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
    
    auto root= menu->getRoot();
    auto previousPos=root->findFirstNodeWithName(name)->findFirstNodeWithName(previousQuadName)->getLocalPosition();
    
    countScoreQuad->setLocalTransform(IvVector3{previousPos.x+0.7f,previousPos.y,previousPos.z}, IvVector3{0,4.72,1}, IvVector3{1,1,1});
    
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
InfoMenu::checkNeedChangeDigit(uint32_t no)
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
            auto node= menu->getRoot()->findFirstNodeWithName(quadName);
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

int InfoMenu::firstDigit(uint32_t no)
{
    while (no >= 10)
        no /= 10;
    
    return no;
}

void InfoMenu::renderNumber(std::string name,uint32_t no,const IvVector3& position)
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
        
        auto root= menu->getRoot();
        auto specificRoot=root->findFirstNodeWithName(name);
        
        if(specificRoot->findFirstNodeWithName(prevName)==nullptr)
            countScoreQuad->setLocalTransform(specificRoot->getAbsolutePosition(), IvVector3{0,4.72,1}, IvVector3{1,1,1});
        else
        {
            auto previousPos= menu->getRoot()->findFirstNodeWithName(prevName)->getLocalPosition();
            countScoreQuad->setLocalTransform(IvVector3{previousPos.x+0.8f,previousPos.y,previousPos.z}, IvVector3{0,4.72,1}, IvVector3{1,1,1});
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

std::pair<float,float>
InfoMenu::getRowCol(const char c) const
{
    std::pair<float,float> result=std::make_pair(-1,-1);
    auto it=characters.find(c);
    if(it!=characters.end())
    {
        result= it->second;
    }
    return result;
}

void
InfoMenu::setCharacters()
{
    characters.insert({' ',std::make_pair(9,0)});
    characters.insert({'!',std::make_pair(9,1)});
    characters.insert({'"',std::make_pair(9,2)});
    characters.insert({'#',std::make_pair(9,3)});
    characters.insert({'$',std::make_pair(9,4)});
    characters.insert({'%',std::make_pair(9,5)});
    characters.insert({'&',std::make_pair(9,6)});
    characters.insert({'\'',std::make_pair(9,7)});
    characters.insert({'(',std::make_pair(9,8)});
    characters.insert({')',std::make_pair(9,9)});
    
    characters.insert({'*',std::make_pair(8,0)});
    characters.insert({'+',std::make_pair(8,1)});
    characters.insert({',',std::make_pair(8,2)});
    characters.insert({'-',std::make_pair(8,3)});
    characters.insert({'.',std::make_pair(8,4)});
    characters.insert({'/',std::make_pair(8,5)});
    characters.insert({'0',std::make_pair(8,6)});
    characters.insert({'1',std::make_pair(8,7)});
    characters.insert({'2',std::make_pair(8,8)});
    characters.insert({'3',std::make_pair(8,9)});
    
    characters.insert({'4',std::make_pair(7,0)});
    characters.insert({'5',std::make_pair(7,1)});
    characters.insert({'6',std::make_pair(7,2)});
    characters.insert({'7',std::make_pair(7,3)});
    characters.insert({'8',std::make_pair(7,4)});
    characters.insert({'9',std::make_pair(7,5)});
    characters.insert({':',std::make_pair(7,6)});
    characters.insert({';',std::make_pair(7,7)});
    characters.insert({'<',std::make_pair(7,8)});
    characters.insert({'=',std::make_pair(7,9)});
    
    characters.insert({'>',std::make_pair(6,0)});
    characters.insert({'?',std::make_pair(6,1)});
    characters.insert({'@',std::make_pair(6,2)});
    characters.insert({'A',std::make_pair(6,3)});
    characters.insert({'B',std::make_pair(6,4)});
    characters.insert({'C',std::make_pair(6,5)});
    characters.insert({'D',std::make_pair(6,6)});
    characters.insert({'E',std::make_pair(6,7)});
    characters.insert({'F',std::make_pair(6,8)});
    characters.insert({'G',std::make_pair(6,9)});
    
    characters.insert({'H',std::make_pair(5,0)});
    characters.insert({'I',std::make_pair(5,1)});
    characters.insert({'J',std::make_pair(5,2)});
    characters.insert({'K',std::make_pair(5,3)});
    characters.insert({'L',std::make_pair(5,4)});
    characters.insert({'M',std::make_pair(5,5)});
    characters.insert({'N',std::make_pair(5,6)});
    characters.insert({'O',std::make_pair(5,7)});
    characters.insert({'P',std::make_pair(5,8)});
    characters.insert({'Q',std::make_pair(5,9)});
    
    characters.insert({'R',std::make_pair(4,0)});
    characters.insert({'S',std::make_pair(4,1)});
    characters.insert({'T',std::make_pair(4,2)});
    characters.insert({'U',std::make_pair(4,3)});
    characters.insert({'V',std::make_pair(4,4)});
    characters.insert({'W',std::make_pair(4,5)});
    characters.insert({'X',std::make_pair(4,6)});
    characters.insert({'Y',std::make_pair(4,7)});
    characters.insert({'Z',std::make_pair(4,8)});
    characters.insert({'[',std::make_pair(4,9)});
    
    characters.insert({'\\',std::make_pair(3,0)});
    characters.insert({']',std::make_pair(3,1)});
    characters.insert({'^',std::make_pair(3,2)});
    characters.insert({'_',std::make_pair(3,3)});
    characters.insert({'`',std::make_pair(3,4)});
    characters.insert({'a',std::make_pair(3,5)});
    characters.insert({'b',std::make_pair(3,6)});
    characters.insert({'c',std::make_pair(3,7)});
    characters.insert({'d',std::make_pair(3,8)});
    characters.insert({'e',std::make_pair(3,9)});
    
    characters.insert({'f',std::make_pair(2,0)});
    characters.insert({'g',std::make_pair(2,1)});
    characters.insert({'h',std::make_pair(2,2)});
    characters.insert({'i',std::make_pair(2,3)});
    characters.insert({'j',std::make_pair(2,4)});
    characters.insert({'k',std::make_pair(2,5)});
    characters.insert({'l',std::make_pair(2,6)});
    characters.insert({'m',std::make_pair(2,7)});
    characters.insert({'n',std::make_pair(2,8)});
    characters.insert({'o',std::make_pair(2,9)});
    
    characters.insert({'p',std::make_pair(1,0)});
    characters.insert({'q',std::make_pair(1,1)});
    characters.insert({'r',std::make_pair(1,2)});
    characters.insert({'s',std::make_pair(1,3)});
    characters.insert({'t',std::make_pair(1,4)});
    characters.insert({'u',std::make_pair(1,5)});
    characters.insert({'v',std::make_pair(1,6)});
    characters.insert({'w',std::make_pair(1,7)});
    characters.insert({'x',std::make_pair(1,8)});
    characters.insert({'y',std::make_pair(1,9)});
    
    characters.insert({' ',std::make_pair(0,0)});
    characters.insert({'{',std::make_pair(0,1)});
    characters.insert({'|',std::make_pair(0,2)});
    characters.insert({'}',std::make_pair(0,3)});
    characters.insert({'~',std::make_pair(0,4)});
}
