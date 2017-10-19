#include "objloader.h"

//

ObjLoader::ObjLoader(string fileName)
{
    m_pointsIndex = new vector<float>;
    m_elementIndex = new vector<uint>;
    m_fileName = fileName;
    //fileName = "res/APOLLO.su2";
}

ObjLoader::~ObjLoader()
{
    delete m_pointsIndex;
    delete m_elementIndex;
}

vector<uint> *ObjLoader::getElementIndex()
{
    return m_elementIndex;
}

vector<float> *ObjLoader::getPointsIndex()
{
    return m_pointsIndex;
}

bool ObjLoader::readFaces()
{
    ifstream fin;
    fin.open(m_fileName);
    if(fin.fail())
    {
        cout << "fail! Cannot open the file!" << endl;
    }
    string ch;
    string mark1Sta = "MARKER_TAG= wall";                         //节点信息读取初始标记
    string mark2Sta = "NPOIN=";                   //mark2Sta = mark1End;节点信息读取结束标记,也是元素索引信息读取开始标记

    int mark1 = 0;
    int mark2 = 0;

    int eleNum = -1;
    int pointsNum = -1;

    while(getline(fin, ch))
    {
        if((string::npos != ch.find(mark1Sta)) && (0 == mark1))
        {
            getline(fin, ch);
            stringstream ss(ch);
            string substr;
            ss >> substr;
            ss >> substr;
            eleNum = stringToNum<int>(substr);
            mark1 = 1;
            continue;
        }
        if((1 == mark1) && (eleNum > 0))
        {
            float firstPoint;
            uint readUint;
            for(int i(0); i < eleNum - 1; ++i)
            {
                stringstream ss(ch);
                string substr;
                ss >> substr;
                ss >> substr;
                readUint = stringToNum<uint>(substr);
                firstPoint = readUint;
                m_elementIndex->push_back(readUint);
                ss >> substr;
                readUint = stringToNum<uint>(substr);
                m_elementIndex->push_back(readUint);
                ss >> substr;
                readUint = stringToNum<uint>(substr);
                m_elementIndex->push_back(readUint);
//                m_elementIndex->push_back(firstPoint);
                getline(fin, ch);
            }
            stringstream ss(ch);
            string substr;
            ss >> substr;
            ss >> substr;
            readUint = stringToNum<uint>(substr);
            firstPoint = readUint;
            m_elementIndex->push_back(readUint);
            ss >> substr;
            readUint = stringToNum<uint>(substr);
            m_elementIndex->push_back(readUint);
            ss >> substr;
            readUint = stringToNum<uint>(substr);
            m_elementIndex->push_back(readUint);
//            m_elementIndex->push_back(firstPoint);
            mark1 = 0;
        }
        //飞行器的z坐标是机体系的y坐标
        //飞行器的-y坐标是机体系的x坐标
        //飞行器的-x坐标是机体系的z坐标
        if((string::npos != ch.find(mark2Sta)) && (0 == mark2))
        {
            stringstream ss(ch);
            string substr;
            ss >> substr;
            ss >> substr;
            pointsNum = stringToNum<int>(substr);
            mark2 = 1;
            continue;
        }
        if((1 == mark2) && (pointsNum > 0))
        {
            float readFloat;
            vector3f position;
            for(int i(0); i < pointsNum - 1; ++i)
            {
                stringstream ss(ch);
                string substr;
                ss >> substr;
                readFloat = stringToNum<float>(substr);
                //readFloat = atof(substr.c_str());
                position._z = -readFloat;
                if(position._z > m_zRange._x)
                {
                    m_zRange._x = position._z;
                }
                else if(position._z < m_zRange._y)
                {
                    m_zRange._y = position._z;
                }
                //m_pointsIndex->push_back(readFloat);

                ss >> substr;
                readFloat = stringToNum<float>(substr);
                position._x = -readFloat;
                if(position._x > m_xRange._x)
                {
                    m_xRange._x = position._x;
                }
                else if(position._x < m_xRange._y)
                {
                    m_xRange._y = position._x;
                }
                //m_pointsIndex->push_back(readFloat);

                ss >> substr;
                readFloat = stringToNum<float>(substr);
                position._y = readFloat;
                if(position._y > m_yRange._x)
                {
                    m_yRange._x = position._y;
                }
                else if(position._y < m_yRange._y)
                {
                    m_yRange._y = position._y;
                }

                //m_pointsIndex->push_back(readFloat);
                m_pointsIndex->push_back(position._x); m_pointsIndex->push_back(position._y); m_pointsIndex->push_back(position._z);
                //m_pointsIndex->push_back(1.0); m_pointsIndex->push_back(0.0); m_pointsIndex->push_back(0.0); m_pointsIndex->push_back(1.0);
                getline(fin, ch);
            }
            stringstream ss(ch);
            string substr;
            ss >> substr;
            readFloat = stringToNum<float>(substr);
            //readFloat = atof(substr.c_str());
            position._z = -readFloat;
            if(position._z > m_zRange._x)
            {
                m_zRange._x = position._z;
            }
            else if(position._z < m_zRange._y)
            {
                m_zRange._y = position._z;
            }
            //m_pointsIndex->push_back(readFloat);

            ss >> substr;
            readFloat = stringToNum<float>(substr);
            position._x = -readFloat;
            if(position._x > m_xRange._x)
            {
                m_xRange._x = position._x;
            }
            else if(position._x < m_xRange._y)
            {
                m_xRange._y = position._x;
            }
            //m_pointsIndex->push_back(readFloat);

            ss >> substr;
            readFloat = stringToNum<float>(substr);
            position._y = readFloat;
            if(position._y > m_yRange._x)
            {
                m_yRange._x = position._y;
            }
            else if(position._y < m_yRange._y)
            {
                m_yRange._y = position._y;
            }

            //m_pointsIndex->push_back(readFloat);
            m_pointsIndex->push_back(position._x); m_pointsIndex->push_back(position._y); m_pointsIndex->push_back(position._z);
            //m_pointsIndex->push_back(1.0); m_pointsIndex->push_back(0.0); m_pointsIndex->push_back(0.0); m_pointsIndex->push_back(1.0);
            mark2 = 0;
        }
    }
//    cout << mark2;
    fin.close();
}

bool ObjLoader::readLines()
{
    ifstream fin;
    fin.open(m_fileName);
    if(fin.fail())
    {
        cout << "fail! Cannot open the file!" << endl;
    }
    string ch;
    string mark1Sta = "MARKER_TAG= wall";                         //节点信息读取初始标记
    string mark2Sta = "NPOIN=";                   //mark2Sta = mark1End;节点信息读取结束标记,也是元素索引信息读取开始标记

    int mark1 = 0;
    int mark2 = 0;

    int eleNum = -1;
    int pointsNum = -1;

    while(getline(fin, ch))
    {
        if((string::npos != ch.find(mark1Sta)) && (0 == mark1))
        {
            getline(fin, ch);
            stringstream ss(ch);
            string substr;
            ss >> substr;
            ss >> substr;
            eleNum = stringToNum<int>(substr);
            mark1 = 1;
            continue;
        }
        if((1 == mark1) && (eleNum > 0))
        {
            float firstPoint;
            uint readUint;
            for(int i(0); i < eleNum - 1; ++i)
            {
                stringstream ss(ch);
                string substr;
                ss >> substr;
                ss >> substr;
                readUint = stringToNum<uint>(substr);
                firstPoint = readUint;
                m_elementIndex->push_back(readUint);
                ss >> substr;
                readUint = stringToNum<uint>(substr);
                m_elementIndex->push_back(readUint);
                ss >> substr;
                readUint = stringToNum<uint>(substr);
                m_elementIndex->push_back(readUint);
                m_elementIndex->push_back(firstPoint);
                getline(fin, ch);
            }
            stringstream ss(ch);
            string substr;
            ss >> substr;
            ss >> substr;
            readUint = stringToNum<uint>(substr);
            firstPoint = readUint;
            m_elementIndex->push_back(readUint);
            ss >> substr;
            readUint = stringToNum<uint>(substr);
            m_elementIndex->push_back(readUint);
            ss >> substr;
            readUint = stringToNum<uint>(substr);
            m_elementIndex->push_back(readUint);
            m_elementIndex->push_back(firstPoint);
            mark1 = 0;
        }

        //飞行器的z坐标是机体系的y坐标
        //飞行器的-y坐标是机体系的x坐标
        //飞行器的-x坐标是机体系的z坐标
        if((string::npos != ch.find(mark2Sta)) && (0 == mark2))
        {
            stringstream ss(ch);
            string substr;
            ss >> substr;
            ss >> substr;
            pointsNum = stringToNum<int>(substr);
            mark2 = 1;
            continue;
        }
        if((1 == mark2) && (pointsNum > 0))
        {
            float readFloat;
            vector3f position;
            for(int i(0); i < pointsNum - 1; ++i)
            {
                stringstream ss(ch);
                string substr;
                ss >> substr;
                readFloat = stringToNum<float>(substr);
                //readFloat = atof(substr.c_str());
                position._z = -readFloat;
                if(position._z > m_zRange._x)
                {
                    m_zRange._x = position._z;
                }
                else if(position._z < m_zRange._y)
                {
                    m_zRange._y = position._z;
                }
                //m_pointsIndex->push_back(readFloat);

                ss >> substr;
                readFloat = stringToNum<float>(substr);
                position._x = -readFloat;
                if(position._x > m_xRange._x)
                {
                    m_xRange._x = position._x;
                }
                else if(position._x < m_xRange._y)
                {
                    m_xRange._y = position._x;
                }
                //m_pointsIndex->push_back(readFloat);

                ss >> substr;
                readFloat = stringToNum<float>(substr);
                position._y = readFloat;
                if(position._y > m_yRange._x)
                {
                    m_yRange._x = position._y;
                }
                else if(position._y < m_yRange._y)
                {
                    m_yRange._y = position._y;
                }

                //m_pointsIndex->push_back(readFloat);
                m_pointsIndex->push_back(position._x); m_pointsIndex->push_back(position._y); m_pointsIndex->push_back(position._z);
                //m_pointsIndex->push_back(1.0); m_pointsIndex->push_back(0.0); m_pointsIndex->push_back(0.0); m_pointsIndex->push_back(1.0);
                getline(fin, ch);
            }
            stringstream ss(ch);
            string substr;
            ss >> substr;
            readFloat = stringToNum<float>(substr);
            //readFloat = atof(substr.c_str());
            position._z = -readFloat;
            if(position._z > m_zRange._x)
            {
                m_zRange._x = position._z;
            }
            else if(position._z < m_zRange._y)
            {
                m_zRange._y = position._z;
            }
            //m_pointsIndex->push_back(readFloat);

            ss >> substr;
            readFloat = stringToNum<float>(substr);
            position._x = -readFloat;
            if(position._x > m_xRange._x)
            {
                m_xRange._x = position._x;
            }
            else if(position._x < m_xRange._y)
            {
                m_xRange._y = position._x;
            }
            //m_pointsIndex->push_back(readFloat);

            ss >> substr;
            readFloat = stringToNum<float>(substr);
            position._y = readFloat;
            if(position._y > m_yRange._x)
            {
                m_yRange._x = position._y;
            }
            else if(position._y < m_yRange._y)
            {
                m_yRange._y = position._y;
            }

            //m_pointsIndex->push_back(readFloat);
            m_pointsIndex->push_back(position._x); m_pointsIndex->push_back(position._y); m_pointsIndex->push_back(position._z);
            //m_pointsIndex->push_back(1.0); m_pointsIndex->push_back(0.0); m_pointsIndex->push_back(0.0); m_pointsIndex->push_back(1.0);
            mark2 = 0;
        }
    }
//    cout << mark2;
    fin.close();
}

vector2f ObjLoader::getXrange()
{
    return m_xRange;
}

vector2f ObjLoader::getYrange()
{
    return m_yRange;
}

vector2f ObjLoader::getZrange()
{
    return m_zRange;
}
