#include "qopenglmain.h"
const float pi = 3.1415926;
QOpenGLMain::QOpenGLMain(QWidget *parent)
    :QOpenGLWidget(parent)
{
    //APOLLO APOLLO_edified COLIBRI_edified grid Hope_x Hope_x_edified SOYUZ SOYUZ_edified square1 VIKING VIKING_edified
    string filename = "res/APOLLO_edified.su2";
    objLoader = new ObjLoader(filename);
    objLoader->readLines();
    //objLoader->getPointsPositionAndIndex(m_pointsIndex, m_elementIndex);
    m_pointsIndex = objLoader->getPointsIndex();
    m_elementIndex = objLoader->getElementIndex();
    m_xRange = objLoader->getXrange();
    m_yRange = objLoader->getYrange();
    m_zRange = objLoader->getZrange();
    //int x = m_pointsIndex->size();
    //cout << x;
}

QOpenGLMain::~QOpenGLMain()
{
//    delete texture0;
//    delete texture1;
}

CRender* QOpenGLMain::getRender()
{
    return &m_therender;
}

void QOpenGLMain::setRot(float _x, float _y)
{
//    m_rotation = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
//                    0.0, cos(_x), -sin(_x), 0.0,
//                    0.0, sin(_x), cos(_x), 0.0,
//                        0.0, 0.0, 0.0, 1.0)*
//        QMatrix4x4(cos(_y), 0.0, sin(_y), 0.0,
//            0.0, 1.0, 0.0, 0.0,
//            -sin(_y), 0.0, cos(_y), 0.0,
//            0.0, 0.0, 0.0, 1.0)*m_rotation;
    m_alpha += _y;
    m_rotation = QMatrix4x4(cos(m_alpha), -sin(m_alpha), 0.0f, 0.0f,
                       sin(m_alpha), cos(m_alpha), 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    m_stataChange = true;
}

void QOpenGLMain::setMove(float _x, float _y)
{
    m_move = QMatrix4x4(1.0, 0.0, 0.0, _x,
                              0.0, 1.0, 0.0, _y,
                              0.0, 0.0, 1.0, 0.0,
                              0.0, 0.0, 0.0, 1.0) * m_move;

    m_stataChange = true;
}

void QOpenGLMain::setRender()
{
    m_therender.bindShader();
    m_therender.getShader()->setUniformValue(m_uniformIndexScale, m_zoom);
    m_therender.getShader()->setUniformValue(m_uniformIndexMove, m_move);
    m_therender.getShader()->setUniformValue(m_uniformIndexRot, m_rotation);
    m_therender.getShader()->setUniformValue(m_uniformIndexBaseCoord, m_basecoord._x, m_basecoord._y, m_basecoord._z);
    m_therender.releaseShader();
}

void QOpenGLMain::setAnix()
{
    m_choose = 0;
    m_therender.getShader()->setUniformValue(m_uniformIndexChoose, m_choose);
}

void QOpenGLMain::setObj()
{
    m_choose = 1;
    m_therender.getShader()->setUniformValue(m_uniformIndexChoose, m_choose);
}

void QOpenGLMain::initializeGL()
{
    initializeOpenGLFunctions();


//    texture0 = new QOpenGLTexture(QImage("/home/liu/Desktop/02.png").mirrored());
//    texture0->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);//LinearMipMapLinear);
//    texture0->setMagnificationFilter(QOpenGLTexture::Linear);
//    texture0->setWrapMode(QOpenGLTexture::Repeat);

//    texture1 = new QOpenGLTexture(QImage("/home/liu/Desktop/point.png").mirrored());
//    texture1->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);//LinearMipMapLinear);
//    texture1->setMagnificationFilter(QOpenGLTexture::Linear);
//    texture1->setWrapMode(QOpenGLTexture::Repeat);

    m_therender.prepare();
    m_uniformIndexXrange = m_therender.getShader()->uniformLocation("xrange");
    m_uniformIndexYrange = m_therender.getShader()->uniformLocation("yrange");
    m_uniformIndexZrange = m_therender.getShader()->uniformLocation("zrange");
    m_uniformIndexScale = m_therender.getShader()->uniformLocation("scale");
    m_uniformIndexMove = m_therender.getShader()->uniformLocation("move");
    m_uniformIndexRot = m_therender.getShader()->uniformLocation("rot");
    m_uniformIndexChoose = m_therender.getShader()->uniformLocation("choose");
    m_uniformIndexBaseCoord = m_therender.getShader()->uniformLocation("baseCoord");


    m_therender.bindShader();
    m_therender.getShader()->setUniformValue(m_uniformIndexXrange, m_xRange._x, m_xRange._y);
    m_therender.getShader()->setUniformValue(m_uniformIndexYrange, m_yRange._x, m_yRange._y);
    m_therender.getShader()->setUniformValue(m_uniformIndexZrange, m_zRange._x, m_zRange._y);
    m_therender.getShader()->setUniformValue(m_uniformIndexScale, m_zoom);
    m_therender.getShader()->setUniformValue(m_uniformIndexMove, m_move);
    m_therender.getShader()->setUniformValue(m_uniformIndexRot, m_rotation);
    m_therender.getShader()->setUniformValue(m_uniformIndexChoose, m_choose);
    m_therender.getShader()->setUniformValue(m_uniformIndexBaseCoord, m_basecoord._x, m_basecoord._y, m_basecoord._z);
    m_therender.releaseShader();
//    m_uniformIndexTexture0 = m_therender.getShader()->uniformLocation("texture0");
//    m_uniformIndexTexture0 = m_therender.getShader()->uniformLocation("texture1");
    //m_therender.initialShader();

    glGenVertexArrays(1, &m_vaoAnix);
    glGenBuffers(1, &m_vboAnix);
    glGenBuffers(1, &m_vboIndexAnix);


    genAndBindAnix();
    genAndBindObject();

}
//size_t i1 = 0;
//size_t i2 = 0;
void QOpenGLMain::paintGL()
{
    //qDebug() << "paintGL: " << i1++;
    //glViewport(0, 0, width(), height());
    setRender();
    m_therender.bindShader();
    setAnix();
    drawAnix();
    setObj();
    drawObject();
    m_therender.releaseShader();
}

void QOpenGLMain::drawAnix()
{
    //qDebug() << "draw: " << i2++;
    //m_context->makeCurrent(m_surface);
    glBindVertexArray(m_vaoAnix);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
        m_vboIndexAnix);
    glDrawElements(GL_LINES,m_arrowIndex.size()-18, GL_UNSIGNED_INT, 0);
    glLineWidth(1.5);
    glDrawElements(GL_LINES, 18, GL_UNSIGNED_INT, (char*)((m_arrowIndex.size() - 18)*4));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //ll
    glBindVertexArray(0);
}

void QOpenGLMain::drawObject()
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);
    //int x =  m_elementIndex->size();
    glDrawElements(GL_LINES, m_elementIndex->size(), GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_TRIANGLES, m_elementIndex->size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}


void QOpenGLMain::genAndBindAnix()
{
    m_arrowIndex.clear();
    m_arrowpoint.clear();

    size_t anglenum = 20;
    int offsite = 0;
    for (size_t index = 0; index < anglenum; ++index)		//��������
    {
        if (index < (anglenum - 1))
        {
            m_arrowIndex.push_back(0);
            m_arrowIndex.push_back(index + 1);
            m_arrowIndex.push_back(index + 2);
        }
        else {
            m_arrowIndex.push_back(0);
            m_arrowIndex.push_back(index + 1);
            m_arrowIndex.push_back(1);
        }
    }
    offsite = anglenum + 1;
    for (size_t index = 0; index < anglenum; ++index)		//��������
    {
        if (index < (anglenum - 1))
        {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(index + 2 + offsite);
        }
        else {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(1 + offsite);
        }
    }
    offsite = 2 * (anglenum + 1);
    for (size_t index = 0; index < anglenum; ++index)		//��������
    {
        if (index < (anglenum - 1))
        {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(index + 2 + offsite);
        }
        else {
            m_arrowIndex.push_back(0 + offsite);
            m_arrowIndex.push_back(index + 1 + offsite);
            m_arrowIndex.push_back(1 + offsite);
        }
    }
    offsite = 3 * (anglenum + 1);
    for (size_t index = 0; index < 6 * 3; ++index)					//����������
    {
        m_arrowIndex.push_back(offsite + index);
    }

    m_arrowpoint.push_back(m_x._y);			//x���
    m_arrowpoint.push_back(m_y._x);			//y��С
    m_arrowpoint.push_back(m_z._x);			//z��С
    m_arrowpoint.push_back(m_xcolor._r);//��ɫ
    m_arrowpoint.push_back(m_xcolor._g);//��ɫ
    m_arrowpoint.push_back(m_xcolor._b);//��ɫ
    m_arrowpoint.push_back(m_xcolor._a);//��ɫ

    for (size_t index = 0; index < anglenum; ++index)
    {
        m_arrowpoint.push_back(m_x._y - m_arrowbase._y);
        m_arrowpoint.push_back(m_y._x+m_arrowbase._x*cos(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_z._x+m_arrowbase._x*sin(index * 2 * pi / anglenum));

        m_arrowpoint.push_back(m_xcolor._r);//��ɫ
        m_arrowpoint.push_back(m_xcolor._g);//��ɫ
        m_arrowpoint.push_back(m_xcolor._b);//��ɫ
        m_arrowpoint.push_back(m_xcolor._a);//��ɫ
    }

    m_arrowpoint.push_back(m_x._x);			//x���
    m_arrowpoint.push_back(m_y._y);			//y��С
    m_arrowpoint.push_back(m_z._x);			//z��С
    m_arrowpoint.push_back(m_ycolor._r);//��ɫ
    m_arrowpoint.push_back(m_ycolor._g);//��ɫ
    m_arrowpoint.push_back(m_ycolor._b);//��ɫ
    m_arrowpoint.push_back(m_ycolor._a);//��ɫ
    for (size_t index = 0; index < anglenum; ++index)
    {
        m_arrowpoint.push_back(m_x._x + m_arrowbase._x*cos(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_y._y - m_arrowbase._y);
        m_arrowpoint.push_back(m_z._x + m_arrowbase._x*sin(index * 2 * pi / anglenum));

        m_arrowpoint.push_back(m_ycolor._r);//��ɫ
        m_arrowpoint.push_back(m_ycolor._g);//��ɫ
        m_arrowpoint.push_back(m_ycolor._b);//��ɫ
        m_arrowpoint.push_back(m_ycolor._a);//��ɫ
    }

    //Z���� ��ͷ
    m_arrowpoint.push_back(m_x._x);
    m_arrowpoint.push_back(m_y._x);
    m_arrowpoint.push_back(m_z._y);
    m_arrowpoint.push_back(m_zcolor._r);//��ɫ
    m_arrowpoint.push_back(m_zcolor._g);//��ɫ
    m_arrowpoint.push_back(m_zcolor._b);//��ɫ
    m_arrowpoint.push_back(m_zcolor._a);//��ɫ
    for (size_t index = 0; index < anglenum; ++index)
    {
        m_arrowpoint.push_back(m_x._x + m_arrowbase._x*cos(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_y._x - m_arrowbase._x*sin(index * 2 * pi / anglenum));
        m_arrowpoint.push_back(m_z._y - m_arrowbase._y);
        m_arrowpoint.push_back(m_zcolor._r);//��ɫ
        m_arrowpoint.push_back(m_zcolor._g);//��ɫ
        m_arrowpoint.push_back(m_zcolor._b);//��ɫ
        m_arrowpoint.push_back(m_zcolor._a);//��ɫ
    }

    //X��
    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_xcolor._r); m_arrowpoint.push_back(m_xcolor._g); m_arrowpoint.push_back(m_xcolor._b); m_arrowpoint.push_back(m_xcolor._a);

    m_arrowpoint.push_back(m_x._y); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_xcolor._r); m_arrowpoint.push_back(m_xcolor._g); m_arrowpoint.push_back(m_xcolor._b); m_arrowpoint.push_back(m_xcolor._a);
    //Y��
    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_ycolor._r); m_arrowpoint.push_back(m_ycolor._g); m_arrowpoint.push_back(m_ycolor._b); m_arrowpoint.push_back(m_ycolor._a);

    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._y); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_ycolor._r); m_arrowpoint.push_back(m_ycolor._g); m_arrowpoint.push_back(m_ycolor._b); m_arrowpoint.push_back(m_ycolor._a);
    //Z��
    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._x);
    m_arrowpoint.push_back(m_zcolor._r); m_arrowpoint.push_back(m_zcolor._g); m_arrowpoint.push_back(m_zcolor._b); m_arrowpoint.push_back(m_zcolor._a);

    m_arrowpoint.push_back(m_x._x); m_arrowpoint.push_back(m_y._x); m_arrowpoint.push_back(m_z._y);
    m_arrowpoint.push_back(m_zcolor._r); m_arrowpoint.push_back(m_zcolor._g); m_arrowpoint.push_back(m_zcolor._b); m_arrowpoint.push_back(m_zcolor._a);

    glBindVertexArray(m_vaoAnix);
    GLuint  _persize = sizeof(vector3f) + sizeof(vector4f);//λ��3+��ɫ3
    glBindBuffer(GL_ARRAY_BUFFER, m_vboAnix);
    glBufferData(GL_ARRAY_BUFFER,
        m_arrowpoint.size() * sizeof(GLfloat),
        m_arrowpoint.data(),
        GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
        3,
        GL_FLOAT,
        GL_FALSE,
        _persize,
        0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
        4,
        GL_FLOAT,
        GL_FALSE,
        _persize,
        (char*)(sizeof(vector3f)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
        m_vboIndexAnix);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        m_arrowIndex.size() * sizeof(GLuint),
        m_arrowIndex.data(),
        GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void QOpenGLMain::genAndBindObject()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    GLuint _persize = sizeof(vector3f);
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_pointsIndex->size() * sizeof(GLfloat), m_pointsIndex->data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
        3,
        GL_FLOAT,
        GL_FALSE,
        _persize,
        0);
    /*glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
        4,
        GL_FLOAT,
        GL_FALSE,
        _persize,
        (char*)(sizeof(vector3f)));*/
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    glGenBuffers(1, &m_vboIndex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_elementIndex->size() * sizeof(GLuint), m_elementIndex->data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


}

void QOpenGLMain::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        if(m_isReadLines)
            m_isReadLines = false;
        else
            m_isReadLines = true;
    }
    genAndBindObject();
}

void QOpenGLMain::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftPushDown = true;
        m_mouseCordx = event->x();
        m_mouseCordy = event->y();
    }
    if (event->button() == Qt::RightButton)
    {
        m_rightPushDown = true;
        m_mouseCordx = event->x();
        m_mouseCordy = event->y();
    }
}

void QOpenGLMain::mouseMoveEvent(QMouseEvent *event)
{
    if (m_leftPushDown)
    {
        float _roatx = m_mouseCordx - event->x();
        float _roaty = m_mouseCordy - event->y();
        m_mouseCordx = event->x();
        m_mouseCordy = event->y();
        setRot(_roatx / 200,  _roaty/ 200);
    }
    if (m_rightPushDown)
    {
        float _movex = ((float)m_mouseCordx - event->x())/width();
        float _movey = ((float)m_mouseCordy - event->y())/height();
        m_mouseCordx = event->x();
        m_mouseCordy = event->y();
        setMove(-_movex, _movey);
    }
}

void QOpenGLMain::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftPushDown = false;
    }
    if (event->button() == Qt::RightButton)
    {
        m_rightPushDown = false;
    }
}

void QOpenGLMain::wheelEvent(QWheelEvent *event)
{
    if (event->delta()>0)
    {
        m_zoom *= 1.1;
    }
    else {
        m_zoom *= 0.9;
    }
    //setZoom(m_zoom);
}
