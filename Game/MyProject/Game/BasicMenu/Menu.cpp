//-------------------------------------------------------------------------------
//-- Menu.cpp -------------------------------------------------------------------
//-------------------------------------------------------------------------------
#include "Menu.hpp"
//-------------------------------------------------------------------------------
//  PUBLIC METHODS
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
// @Menu::Menu()
//-------------------------------------------------------------------------------
Menu::Menu()
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
    
    characters.insert({'z',std::make_pair(0,0)});
    characters.insert({'{',std::make_pair(0,1)});
    characters.insert({'|',std::make_pair(0,2)});
    characters.insert({'}',std::make_pair(0,3)});
    characters.insert({'~',std::make_pair(0,4)});
}
//-------------------------------------------------------------------------------
// @Menu::~Menu()
//-------------------------------------------------------------------------------
Menu::~Menu()
{
    
}
//-------------------------------------------------------------------------------
//  PROTECTED METHODS
//-------------------------------------------------------------------------------
std::pair<float,float>
Menu::getRowCol(const char c)
{
    
    std::pair<float,float> result;
    auto it=characters.find(c);
    if(it!=characters.end())
    {
        result= it->second;
    
    }
    return result;
}
