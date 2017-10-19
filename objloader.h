#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <crender.h>

using namespace std;

//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性）
template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

class ObjLoader
{
public:
    ObjLoader(string fileName);
    ~ObjLoader();
    vector<uint> *getElementIndex();
    vector<float> *getPointsIndex();
    bool        readFaces();
    bool        readLines();
    vector2f    getXrange();
    vector2f    getYrange();
    vector2f    getZrange();
private:
    vector2f            m_xRange = {1,0};
    vector2f            m_yRange = {1,0};
    vector2f            m_zRange = {1,0};
    vector<uint>*       m_elementIndex;
    vector<float>*      m_pointsIndex;
    string              m_fileName;
};

#endif // OBJLOADER_H
