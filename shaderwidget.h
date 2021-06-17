#ifndef SHADERWIDGET_H
#define SHADERWIDGET_H

#include <QObject>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <QBasicTimer >

class ShaderWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    static void InitOpengl();

public:
    ShaderWidget(QWidget *parent);
    ~ShaderWidget();

    void Start();
    void Stop();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void timerEvent(QTimerEvent *vTimerEvent) override;

private:
    QOpenGLVertexArrayObject m_Vao;
    QOpenGLBuffer m_Vbo;
    QOpenGLShaderProgram m_Program;
    QVector2D m_Size;
    QBasicTimer m_Timer;
    float m_Time = 0.0f;
};

#endif // SHADERWIDGET_H
