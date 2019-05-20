#include "InfoManager.hpp"

InfoManager::InfoManager(SceneNode* root) : root(root) {
    
    //get list of all cars
    std::vector<std::shared_ptr<SceneNode>>cars;
    root->findAllNodesContainingName("Car", cars);
    
    //set initial values
    for(const auto& i : cars)
    {
        carsList.push_back(i.get());
        setLap(i->getName(), 1);
        setCheckpoint(i->getName(), 0);
        setScore(i->getName(), 0);
    }
    
    //get the list of middle points
    std::vector<std::shared_ptr<SceneNode>>scene_nodes;
    root->findAllNodesContainingName("bezierMiddlePoint", scene_nodes);
    for(const auto& i : scene_nodes)
        roadMiddlePoints.push_back(i->getLocalPositon());
}

const float InfoManager::getCarSpeed(const std::string& carName) const{
    IvVector3 velocityVector = ((CarController*)root->findFirstNodeWithName(carName)->getAnimator())->getVelocity();
    return velocityVector.x + velocityVector.z;
}

void InfoManager::setLap(const std::string& carName, int lap){
    carsData[carName].laps = lap;
}

const int InfoManager::getLap(const std::string& carName)const {
    return  carsData.at(carName).laps;
}

void InfoManager::setCheckpoint(const std::string& carName, int checkpoint){
    carsData[carName].checkpoints = checkpoint;
}

const int InfoManager::getCheckpoint(const std::string& carName) const{
    return carsData.at(carName).checkpoints;
}

void InfoManager::setScore(const std::string& carName, int scor){
    carsData[carName].score = scor;
}

const int InfoManager::getScore(const std::string& carName) const{
    return carsData.at(carName).score;
}

const float InfoManager::getTime() const{
    return sinceStartTimer;
}

void InfoManager::updateCarStats(){
    for(int i = 0; i < carsList.size(); i++)
    {
        //get distance to next checkpoint
        int nextCheckPointIndex = carsData[carsList[i]->getName()].checkpoints + 1;
        
        //reset the index if needed
        if (nextCheckPointIndex == roadMiddlePoints.size())
            nextCheckPointIndex = 0;
        
        //if close enough to next checkpoint, change stats
        if (Distance(carsList[i]->getLocalPosition(), roadMiddlePoints[nextCheckPointIndex]) < checkpointTriggerDistance)
        {
            //next checkpoint
            carsData[carsList[i]->getName()].checkpoints = nextCheckPointIndex;
            
            //increase score
            carsData[carsList[i]->getName()].score++;
            
            //if last checkpoint -> next lap
            if (nextCheckPointIndex == roadMiddlePoints.size())
            {
                carsData[carsList[i]->getName()].laps++;
                
                //mapping of form: key:CarName + lapNumber -> value: time
                carsData[carsList[i]->getName() + std::to_string(carsData[carsList[i]->getName()].laps)].lapTime = sinceStartTimer;
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

