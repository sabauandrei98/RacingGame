#include "InfoManager.hpp"

InfoManager::InfoManager(SceneNode* root) : root(root) {
    
    //get list of all cars
    std::vector<std::shared_ptr<SceneNode>>cars;
    root->findAllNodesContainingName("Car", cars);
    
    //set initial values
    for(const auto& i : cars)
    {
        carsList.push_back(i.get());
        CarProps prop;
        prop.laps = 1;
        prop.checkpoints = 0;
        prop.score = 0;
        prop.lapTime.push_back(0);
        carsData[i->getName() ] = prop;
    }
    
    //get the list of middle points
    std::vector<std::shared_ptr<SceneNode>>scene_nodes;
    roadMiddlePoints = ((RoadNode*)root->findFirstNodeWithName("roadNode"))->getMiddlePoints();
}

const float InfoManager::getCarSpeed(const std::string& carName) const{
    IvVector3 velocityVector = ((CarController*)root->findFirstNodeWithName(carName)->getAnimator())->getVelocity();
    return abs(velocityVector.x) + abs(velocityVector.z);
}

void InfoManager::setLap(const std::string& carName, int lap){
    carsData[carName].laps = lap;
}

const int InfoManager::getLap(const std::string& carName)const {
    return  carsData.at(carName).laps;
}

void InfoManager::setLapTime(const std::string& carName, int lap, float time){
    carsData[carName].lapTime[lap] = time;
}

const float InfoManager::getLapTime(const std::string& carName, int lap) const {
    return  carsData.at(carName).lapTime[lap];
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
        auto& carInfo = carsData[carsList[i]->getName()];
        
        //get distance to next checkpoint
        int nextCheckPointIndex = carInfo.checkpoints + 1;
        
        //reset the index if needed
        if (nextCheckPointIndex == roadMiddlePoints.size())
            nextCheckPointIndex = 0;
        
        //if close enough to next checkpoint, change stats
        if (Distance(carsList[i]->getLocalPosition(), roadMiddlePoints[nextCheckPointIndex]) < checkpointTriggerDistance)
        {
            //next checkpoint
            carInfo.checkpoints = nextCheckPointIndex;
            
            //increase score
            carInfo.score++;
            
            //if last checkpoint -> next lap
            if (nextCheckPointIndex == roadMiddlePoints.size())
            {
                carInfo.laps++;
                carInfo.lapTime.push_back(sinceStartTimer);
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

