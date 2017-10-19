#include "crender.h"
#include <QMessageBox>

CRender::CRender()
{

}

CRender::~CRender()
{

}

void CRender::prepare()
{
    initializeOpenGLFunctions();
    glClearColor(1,1,1,0.2);
    glClear(GL_COLOR_BUFFER_BIT);
    initialShader();
}

void CRender::bindShader()
{
    m_shaderprogram.bind();
}

void CRender::bindAttributes()
{
    m_shaderprogram.bindAttributeLocation("Position", 0);
    m_shaderprogram.bindAttributeLocation("textureCoords", 1);
}

void CRender::setBackGround(vector4f &_color)
{
    glClearColor(_color._r, _color._g, _color._b, _color._a);
    glFlush();
}

void CRender::releaseShader()
{
    m_shaderprogram.release();
}

QGLShaderProgram *CRender::getShader()
{
    return &m_shaderprogram;  
}

void CRender::initialShader()
{
    if (!m_shaderprogram.addShaderFromSourceFile(QGLShader::Vertex, "/home/liu/asio/textureTest/vertex.shader"))
    {
        QMessageBox::information(NULL, "vert",
            m_shaderprogram.log(),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
    }
    if (!m_shaderprogram.addShaderFromSourceFile(QGLShader::Fragment, "/home/liu/asio/textureTest/fragment.shader"))
    {
        QMessageBox::information(NULL, "Frag",
            m_shaderprogram.log(),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
    }
    if (!m_shaderprogram.link())
    {
        QMessageBox::information(NULL, "Frag",
            m_shaderprogram.log(),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::Yes);
    }
}
