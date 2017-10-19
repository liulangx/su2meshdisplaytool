#ifndef QOPENGLMAIN_H
#define QOPENGLMAIN_H
#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_4_3_Core>
#include <QTimer>
#include <QMouseEvent>
#include "objloader.h"
#include "crender.h"

class QOpenGLMain : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
public:
    QOpenGLMain(QWidget *parent);
    ~QOpenGLMain();
    CRender *getRender();
private:
    void setRot(float _x, float _y);
    void setMove(float _x, float _y);
    void setRender();
    void setAnix();
    void setObj();
protected:
    void initializeGL();
    void paintGL();
    void drawAnix();
    void drawObject();
    void genAndBindAnix();
    void genAndBindObject();

private slots:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    bool						m_stataChange=true;
    bool                        m_isReadLines = 1;
    int                         m_choose = 1;
    vector3f                    m_basecoord = {0, 0, 0};
    float               m_alpha = 0;
    QMatrix4x4          m_rotation = {
                                1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1
                            };
    QMatrix4x4          m_move = {
                                1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1
                            };
    QMatrix4x4          m_moveMatrix = {
                                        1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1
                                    };
    float   m_zoom = 1.0;
    bool	m_leftPushDown = false;		//左键按下
    bool	m_rightPushDown = false;	//右键按下
    int		m_mouseCordx = 0;			//左键鼠标位置x
    int		m_mouseCordy = 0;			//左键鼠标位置y
    CRender m_therender;
    GLuint m_uniformIndexXrange;
    GLuint m_uniformIndexYrange;
    GLuint m_uniformIndexZrange;
    GLuint m_uniformIndexScale;
    GLuint m_uniformIndexMove;
    GLuint m_uniformIndexRot;
    GLuint m_uniformIndexChoose;
    GLuint m_uniformIndexBaseCoord;

    GLuint m_vaoAnix;
    GLuint m_vboAnix;
    GLuint m_vboIndexAnix;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_vboTexture;
    GLuint m_vboIndex;

    GLuint m_vaoPoint;
    GLuint m_vboPoint;
    GLuint m_vboTexturePoint;

    ObjLoader* objLoader;

    vector<uint>* m_elementIndex;
    vector<float>* m_pointsIndex;
    vector2f     m_xRange = {2, 0};
    vector2f     m_yRange = {2, 0};
    vector2f     m_zRange = {2, 0};

    QOpenGLTexture* texture0;
    QOpenGLTexture* texture1;

    GLuint m_uniformIndexTexture0;
    GLuint m_uniformIndexTexture1;

    vector<GLuint>				m_arrowIndex;					//箭头检索
    vector<float>				m_arrowpoint;					//箭头的点
    vector2f  m_x = {0,1};			//坐标X
    vector2f m_y = {0,1};			//坐标Y
    vector2f m_z = {0,1};			//坐标Z

    vector4f					m_xcolor = {1,0,0,1};						//x轴颜色
    vector4f					m_ycolor = {0,1,0,1};						//y轴颜色
    vector4f					m_zcolor = {0,0,1,1};						//z轴颜色

    vector2f					m_arrowbase = {0.01f,0.05f};		//箭头底半径 箭头长度

};

#endif // QOPENGLMAIN_H
