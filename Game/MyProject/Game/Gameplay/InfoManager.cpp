#include "InfoManager.hpp"

InfoManager::InfoManager(SceneNode* root) : root(root) {
    
    //get list of all cars
    std::vector<std::shared_ptr<SceneNode>>scene_nodes;
    root->findAllNodesContainingName("Car", scene_nodes);
    
    //set initial values
    for(int i = 0; i < scene_nodes.size(); i++)
    {
        setLap(scene_nodes[i]->getName(), 1);
        setCheckpoint(scene_nodes[i]->getName(), 0);
        setScore(scene_nodes[i]->getName(), 0);
    }
}

const IvVector3& InfoManager::getCarSpeed(const std::string& carName) const{
    return ((CarController*)root->findFirstNodeWithName(carName)->getAnimator())->getVelocity();
}

void InfoManager::setLap(const std::string& carName, int lap){
    laps[carName] = lap;
}

const int InfoManager::getLap(const std::string& carName) const{
    return laps.at(carName);
}

void InfoManager::setCheckpoint(const std::string& carName, int checkpoint){
    checkpoints[carName] = checkpoint;
}

const int InfoManager::getCheckpoint(const std::string& carName) const{
    return checkpoints.at(carName);
}

void InfoManager::setScore(const std::string& carName, int scor){
    score[carName] = scor;
}

const int InfoManager::getScore(const std::string& carName) const{
    return score.at(carName);
}

const float InfoManager::getTime() const{
    return time;
}

void InfoManager::Update(float dt)
{
    time += dt;
}
