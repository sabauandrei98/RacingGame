#include "RoadGeneratorControler.hpp"

void RoadGeneratorControler::updateControlPointsPosition(int index)
{
    if ((index + 1) % 3 == 0)
    {
        bezierPoints[index + 2].x = bezierPoints[index + 1].x * 2 - bezierPoints[index].x;
        bezierPoints[index + 2].z = bezierPoints[index + 1].z * 2 - bezierPoints[index].z;
    }
    else
        if ((index - 1) % 3 == 0)
        {
            bezierPoints[index - 2].x = bezierPoints[index - 1].x * 2 - bezierPoints[index].x;
            bezierPoints[index - 2].z = bezierPoints[index - 1].z * 2 - bezierPoints[index].z;
        }
}

void RoadGeneratorControler::mergeHeadTail()
{
    bezierPoints[bezierPoints.size() - 1] = bezierPoints[0];
    bezierPoints[bezierPoints.size() - 2].x = bezierPoints[0].x * 2 - bezierPoints[1].x;
    bezierPoints[bezierPoints.size() - 2].z = bezierPoints[0].z * 2 - bezierPoints[1].z;
    rMarginPoints[rMarginPoints.size() - 1].first = rMarginPoints[0].first;
    rMarginPoints[rMarginPoints.size() - 1].second = rMarginPoints[0].second;
}

//returns true if the track was updated on the current frame
bool
RoadGeneratorControler::Update( float dt )
{
    bool isUpdated = false;
    
    //go to next point
    if (IvGame::mGame->mEventHandler->IsKeyReleased('.'))
    {
        if (editIndex + 1 <= bezierPoints.size() - 1)
            editIndex ++;
        isUpdated = true;
    }

    //go to prev point
    if (IvGame::mGame->mEventHandler->IsKeyReleased(','))
    {
        if (editIndex - 1 >= 0)
            editIndex --;
        isUpdated = true;
    }
    
    if (IvGame::mGame->mEventHandler->IsKeyReleased('r'))
    {
        //move the edit on a fixed point
        while(editIndex % 3 != 0)
            editIndex ++;
        
        if(editIndex != bezierPoints.size() - 1)
        {
            bezierPoints.insert(bezierPoints.begin() + editIndex + 2, {-1, 0, 0});
            bezierPoints.insert(bezierPoints.begin() + editIndex + 3, {0, 0, 0});
            bezierPoints.insert(bezierPoints.begin() + editIndex + 4, {1, 0, 0});
            updateControlPointsPosition(editIndex + 2);
        }
        else
        {
            bezierPoints.insert(bezierPoints.begin() + editIndex + 1, {-1, 0, 0});
            bezierPoints.insert(bezierPoints.begin() + editIndex + 2, {0, 0, 0});
            bezierPoints.insert(bezierPoints.begin() + editIndex + 3, {1, 0, 0});
            updateControlPointsPosition(editIndex + 1);
        }
        
        editIndex += 3;
        isUpdated = true;
    }
        
    if (IvGame::mGame->mEventHandler->IsKeyReleased('f'))
    {
        //works only on fixed points
        if(editIndex % 3 != 0 || bezierPoints.size() == 4)
            return false;
    
        if(editIndex != bezierPoints.size() - 1)
        {
            bezierPoints.erase(bezierPoints.begin() + editIndex);
            bezierPoints.erase(bezierPoints.begin() + editIndex);
            bezierPoints.erase(bezierPoints.begin() + editIndex);
        }
        else
        {
            bezierPoints.erase(bezierPoints.begin() + editIndex);
            bezierPoints.erase(bezierPoints.begin() + editIndex - 1);
            bezierPoints.erase(bezierPoints.begin() + editIndex - 2);
            editIndex = bezierPoints.size() - 1;
        }
        isUpdated = true;
    }

    static unsigned char input[4] = {'w','a','s','d'};
    for(int i = 0; i < 4; i++)
        if (IvGame::mGame->mEventHandler->IsKeyDown(input[i]))
        {
            
            IvVector3 offset = {0, 0, 0};
            if (input[i] == 'w')
                offset.z = editSpeed * dt;
            if (input[i] == 's')
                offset.z = -editSpeed * dt;
            if (input[i] == 'a')
                offset.x = -editSpeed * dt;
            if (input[i] == 'd')
                offset.x = editSpeed * dt;


            //FIXED POINT
            if(editIndex % 3 == 0)
            {
                //first fixed point
                if(editIndex == 0)
                {
                    bezierPoints[editIndex] += offset;
                    bezierPoints[editIndex + 1] += offset;
                }
                else
                    //last fixed point
                    if(editIndex == bezierPoints.size() - 1)
                    {
                        bezierPoints[editIndex] += offset;
                        bezierPoints[editIndex - 1] += offset;
                    }
                //other fixed point
                    else{
                        bezierPoints[editIndex - 1] += offset;
                        bezierPoints[editIndex] += offset;
                        bezierPoints[editIndex + 1] += offset;
                    }
            }

            //CONTROL POINT
            if (editIndex % 3 != 0)
            {
                //first or last control point
                if(editIndex == 1 || editIndex == bezierPoints.size() - 2)
                {
                    bezierPoints[editIndex] += offset;
                    
                    if(editIndex == 1)
                    {
                        bezierPoints[bezierPoints.size() - 2].x = bezierPoints[0].x * 2 - bezierPoints[1].x;
                        bezierPoints[bezierPoints.size() - 2].z = bezierPoints[0].z * 2 - bezierPoints[1].z;
                    }
                    else
                    {
                        bezierPoints[1].x = bezierPoints[0].x * 2 - bezierPoints[bezierPoints.size() - 2].x;
                        bezierPoints[1].z = bezierPoints[0].z * 2 - bezierPoints[bezierPoints.size() - 2].z;
                    }
                }
                else
                {
                    //left control point
                    if ((editIndex + 1) % 3 == 0)
                    {
                        bezierPoints[editIndex] += offset;
                        bezierPoints[editIndex + 2].x = bezierPoints[editIndex + 1].x * 2 - bezierPoints[editIndex].x;
                        bezierPoints[editIndex + 2].z = bezierPoints[editIndex + 1].z * 2 - bezierPoints[editIndex].z;
                    }
                    else
                        //right control point
                        if ((editIndex - 1) % 3 == 0)
                        {
                            bezierPoints[editIndex] += offset;
                            bezierPoints[editIndex - 2].x = bezierPoints[editIndex - 1].x * 2 - bezierPoints[editIndex].x;
                            bezierPoints[editIndex - 2].z = bezierPoints[editIndex - 1].z * 2 - bezierPoints[editIndex].z;
                        }

                }
            }
            isUpdated = true;
        }

    
    rMiddlePoints = BezierCurve::buildCurve(bezierPoints, tStep);
    rMarginPoints =  RoadMargins::findTrackPoints(rMiddlePoints);
    mergeHeadTail();
    
    for(int i = 2; i < bezierPoints.size() - 2; i++)
        if (i % 3 != 0)
            updateControlPointsPosition(i);
    
    return isUpdated;
}
