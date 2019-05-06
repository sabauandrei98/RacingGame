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
    state_controller->_main_scene=raceMenu->GetScene();
    
}

void RaceState::onExit() {
    std::cout << "RaceState exits" << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

void RaceState::Update() {
    
    if(isPauseTriggered())
        state_controller->requestChange(Pause);
   
    seconds++;
    if(seconds==5)
    {
        seconds=0;
        
        if(!changed  )
       {
            auto val=raceMenu->getRowCol(score%10 +'0');

            std::string name="count"+std::to_string(noDigits(score%10));
        
            const char* quadName=name.c_str();
        
            raceMenu->GetScene()->getRoot()->findFirstNodeWithName(quadName)->getRenderable()->setUniformValue(1, val.first);
            raceMenu->GetScene()->getRoot()->findFirstNodeWithName(quadName)->getRenderable()->setUniformValue(2, val.second);
         
        }

        
        changed=false;
        if(noDigits(score)>noDigits(score-1))
        {
            addNewDigit();
            changed=true;
        }
        changed2=checkNeedChangeDigit();
        
        score++;
    }
}


bool RaceState::isPauseTriggered()
{
    return IvGame::mGame->mEventHandler->IsKeyPressed('x');
    //return IvGame::mGame->mEventHandler->IsKeyDown(27);
    
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
        
        auto previousPos=raceMenu->GetScene()->getRoot()->findFirstNodeWithName(previousQuadName)->getLocalPosition();
        countScoreQuad->setLocalTransform(IvVector3{previousPos.x-1,previousPos.y,previousPos.z}, IvVector3{0,4.72,1}, IvVector3{2,2,2});
        
        raceMenu->GetScene()->getRoot()->findFirstNodeWithName("countRoot")->addChild(countScoreQuad);
    
        auto val=raceMenu->getRowCol(score%10 +'0');
    
        name="count"+std::to_string(noDigits(score%10));
    
        quadName=name.c_str();
    
        raceMenu->GetScene()->getRoot()->findFirstNodeWithName(quadName)->getRenderable()->setUniformValue(1, val.first);
        raceMenu->GetScene()->getRoot()->findFirstNodeWithName(quadName)->getRenderable()->setUniformValue(2, val.second);
    
        val=raceMenu->getRowCol(firstDigit(score)+'0');
    
        name="count"+std::to_string(noDigits(score));
    
        quadName=name.c_str();
    
        raceMenu->GetScene()->getRoot()->findFirstNodeWithName(quadName)->getRenderable()->setUniformValue(1, val.first);
        raceMenu->GetScene()->getRoot()->findFirstNodeWithName(quadName)->getRenderable()->setUniformValue(2, val.second);
    
}


bool RaceState::checkNeedChangeDigit()
{
    auto aux =  score-1;
    auto noDigits = 1;
    auto continue_ = false;
    auto changed   = false;
    
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
            raceMenu->GetScene()->getRoot()->findFirstNodeWithName(quadName)->getRenderable()->setUniformValue(1, val.first);
            raceMenu->GetScene()->getRoot()->findFirstNodeWithName(quadName)->getRenderable()->setUniformValue(2, val.second);
        
            changed=true;
            
        }
        if(!continue_)
            break;
        
        aux/=10;
        noDigits++;
    }
    
    return changed;
}

int RaceState::firstDigit(int no)
{
 
    while (no >= 10)
        no /= 10;
        
    return no;
    
}
