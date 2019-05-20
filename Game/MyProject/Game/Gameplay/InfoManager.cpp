#include "InfoManager.hpp"

InfoManager::InfoManager(SceneNode* root) : root(root) {
    
    //get list of all cars
    std::vector<std::shared_ptr<SceneNode>>cars;
    root->findAllNodesContainingName("Car", cars);
    for(auto& i : cars)
        carsList.push_back(i.get());
    
    //set initial values
    for(auto& i : carsList)
    {
        setLap(i->getName(), 1);
        setCheckpoint(i->getName(), 0);
        setScore(i->getName(), 0);
    }
    
    //get the list of middle points
    std::vector<std::shared_ptr<SceneNode>>scene_nodes;
    root->findAllNodesContainingName("bezierMiddlePoint", scene_nodes);
    for(auto& i : scene_nodes)
        roadMiddlePoints.push_back(i->getLocalPositon());
}

const float InfoManager::getCarSpeed(const std::string& carName) const{
    IvVector3 velocityVector = ((CarController*)root->findFirstNodeWithName(carName)->getAnimator())->getVelocity();
    return velocityVector.x + velocityVector.z;
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
    return sinceStartTimer;
}

void InfoManager::updateCarStats(){
    for(int i = 0; i < carsList.size(); i++)
    {
        //get distance to next checkpoint
        int nextCheckPointIndex = checkpoints[carsList[i]->getName()] + 1;
        
        //reset the index if needed
        if (nextCheckPointIndex == roadMiddlePoints.size())
            nextCheckPointIndex = 0;
        
        //if close enough to next checkpoint, change stats
        if (Distance(carsList[i]->getLocalPosition(), roadMiddlePoints[nextCheckPointIndex]) < checkpointTriggerDistance)
        {
            //next checkpoint
            checkpoints[carsList[i]->getName()] = nextCheckPointIndex;
            
            //increase score
            score[carsList[i]->getName()]++;
            
            //if last checkpoint -> next lap
            if (nextCheckPointIndex == roadMiddlePoints.size())
            {
                laps[carsList[i]->getName()]++;
                
                //mapping of form: key:CarName + lapNumber -> value: time
                lapTime[carsList[i]->getName() + std::to_string(laps[carsList[i]->getName()])] = sinceStartTimer;
            }
        }
    }
}

void InfoManager::Update(float dt)
{
    sinceStartTimer += dt;
    updateCarStats();
}

InfoManager::~InfoManager(){
    
}

