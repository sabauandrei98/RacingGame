//
//  RaceState.cpp
//  RacingGame
//
//  Created by Tamas Both - (p) on 02/05/2019.
//

#include "GameStates.hpp"

// -----------
// CONSTRUCTOR
// -----------

RaceState::RaceState(StateController* state_controller) :
    GameState(state_controller) {
        meshManager=MeshManager();
        score=0;
    }

// -------------------------
// FUNCTION(S) AND METHOD(S)
// -------------------------


void RaceState::onEnter() {
    std::cout << "RaceState enters" << std::endl;
    std::cout << "Pause: x" << std::endl;
    
    raceMenu=std::make_shared<RaceMenu>();
    state_controller->_main_scene=raceMenu->getScene();
    
}

void RaceState::onExit() {
    std::cout << "RaceState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void RaceState::Update(float dt) {
    
    if(isPauseTriggered())
        state_controller->requestChange(Pause);
    else
        if(isGameOverTriggered())
        {
            frames=0;
            score=0;
            state_controller->requestChange(GOver);
        }
        else
        {
            frames++;
            if(frames==10)
            {
                frames=0;
             
                auto val=raceMenu->getRowCol(score%10 +'0');
        
                std::string name="count"+std::to_string(noDigits(score%10));
                const char* quadName=name.c_str();
                
                auto root=raceMenu->getScene()->getRoot();
                auto first=root->findFirstNodeWithName("countRoot");
                auto count1=first->findFirstNodeWithName("count1");
                if(count1==nullptr && score==0)
                {
                    //rendering first quad
                    std::vector<std::string> uniforms;
                    uniforms.push_back("mTexture");
                    uniforms.push_back("row");
                    uniforms.push_back("column");
                    
                     std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad(quadName,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");
                    
                    countScoreQuad->setLocalTransform(IvVector3{17,0,9}, IvVector3{0,4.72,1}, IvVector3{2,2,2});
                    first->addChild(countScoreQuad);
                    
                    auto quad=root->findFirstNodeWithName(quadName);
                    quad->getRenderable()->setUniformValue(1, val.first);
                    quad->getRenderable()->setUniformValue(2, val.second);
                }
                else if(count1==nullptr)
                {
                   //after pause state
                   renderScore();
                }
                else
                {
                    auto renderable=root->findFirstNodeWithName(quadName)->getRenderable();
                    renderable->setUniformValue(1, val.first);
                    renderable->setUniformValue(2, val.second);
                }
                
                if(noDigits(score)>noDigits(score-1))
                    addNewDigit();
                
                checkNeedChangeDigit();
    
                score++;
            }
        }
}   
    
bool RaceState::isPauseTriggered()
{
    return IvGame::mGame->mEventHandler->IsKeyPressed('x');
}

bool RaceState::isGameOverTriggered()
{
    return IvGame::mGame->mEventHandler->IsKeyPressed('q');
}

unsigned int RaceState::noDigits(uint32_t number)
{
    if(number<10)
        return 1;
    else
        return 1+noDigits(number/10);
}

void RaceState::addNewDigit()
{
        //create a new quad
        std::vector<std::string> uniforms;
        uniforms.push_back("mTexture");
        uniforms.push_back("row");
        uniforms.push_back("column");
    
        std::string name="count"+std::to_string(noDigits(score));
    
        const char* quadName=name.c_str();
    
        std::string preName="count"+std::to_string(noDigits(score-1));
    
        const char* previousQuadName=preName.c_str();
        
        std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad(quadName,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"font.tga");
    
        auto root=raceMenu->getScene()->getRoot();
        auto previousPos=root->findFirstNodeWithName(previousQuadName)->getLocalPosition();

        countScoreQuad->setLocalTransform(IvVector3{previousPos.x-1,previousPos.y,previousPos.z}, IvVector3{0,4.72,1}, IvVector3{2,2,2});
    
        root->findFirstNodeWithName("countRoot")->addChild(countScoreQuad);
    
        auto val=raceMenu->getRowCol(score%10 +'0');
    
        name="count"+std::to_string(noDigits(score%10));
    
        quadName=name.c_str();
    
        auto valueRenderable=root->findFirstNodeWithName(quadName)->getRenderable();
        valueRenderable->setUniformValue(1, val.first);
        valueRenderable->setUniformValue(2, val.second);
    
        if(score>=10)
        {
            val=raceMenu->getRowCol(firstDigit(score)+'0');
    
            name="count"+std::to_string(noDigits(score));
    
            quadName=name.c_str();
    
            valueRenderable=root->findFirstNodeWithName(quadName)->getRenderable();
            valueRenderable->setUniformValue(1, val.first);
            valueRenderable->setUniformValue(2, val.second);
        }
    
}

void RaceState::checkNeedChangeDigit()
{
    auto aux =  score-1;
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
        
            auto val=raceMenu->getRowCol(ch );
            auto node=raceMenu->getScene()->getRoot()->findFirstNodeWithName(quadName);
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

int RaceState::firstDigit(int no)
{
    while (no >= 10)
        no /= 10;
        
    return no;
}

void RaceState::renderScore()
{
    int auxScore=score;
    int noDig=noDigits(score);

    while(noDig!=0)
    {
        std::string name="count"+std::to_string(noDigits(score)-noDig + 1);
        const char* quadName=name.c_str();
        
        std::vector<std::string> uniforms;
        uniforms.push_back("mTexture");
        uniforms.push_back("row");
        uniforms.push_back("column");
        
        std::shared_ptr<SceneNode> countScoreQuad=HelperManager::BuildTexturedQuad(quadName,HelperManager::CreateMeshInstance(meshManager.GetMesh("quad"),uniforms,"../../Game/BasicMenu/Shaders/AtlasSpriteShader"),"../../Game/BasicMenu/Resources/font.tga");
        
        std::string n="count"+std::to_string(noDigits(score)-noDig );
        const char* prevName=n.c_str();
        
        auto root=raceMenu->getScene()->getRoot();
        
        if(root->findFirstNodeWithName("countRoot")->findFirstNodeWithName(prevName)==nullptr)
            countScoreQuad->setLocalTransform(IvVector3{17,0,9}, IvVector3{0,4.72,1}, IvVector3{2,2,2});
        else
        {
            auto previousPos=raceMenu->getScene()->getRoot()->findFirstNodeWithName(prevName)->getLocalPosition();
            countScoreQuad->setLocalTransform(IvVector3{previousPos.x-1,previousPos.y,previousPos.z}, IvVector3{0,4.72,1}, IvVector3{2,2,2});
        };
        
        root->findFirstNodeWithName("countRoot")->addChild(countScoreQuad);
        
        auto val=raceMenu->getRowCol(auxScore%10 + '0');
        auto renderable=root->findFirstNodeWithName(quadName)->getRenderable();
        
        renderable->setUniformValue(1, val.first);
        renderable->setUniformValue(2, val.second);
        
        auxScore/=10;
        noDig--;
    }
}
