#ifndef CRENDER_H
#define CRENDER_H
#include <vector>
#include <QOpenGLFunctions_4_3_Core>
#include <QGLShader>
#include <QGLShaderProgram>
using namespace std;
typedef float SPFLOAT;
struct vector2f
{
    SPFLOAT _x, _y;
};
struct vector3f
{
    SPFLOAT _x, _y, _z;
};
struct vector4f
{
    SPFLOAT _r, _g, _b, _a;
};
struct vector4b
{
    GLubyte _r, _g, _b, _a;
};
class CRender :protected QOpenGLFunctions_4_3_Core
{
public:
    CRender();
    ~CRender();
    void	prepare();
    void	bindShader();
    virtual void bindAttributes();
    void    setBackGround(vector4f& _color);
    void	releaseShader();
    QGLShaderProgram *getShader();
    void initialShader();
protected:

    QGLShaderProgram			m_shaderprogram;				//shader程序
    vector<GLuint>              m_vaos;				//vba
};

#endif // CRENDER_H
