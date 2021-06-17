#include "shaderwidget.h"

#include <vector>

void ShaderWidget::InitOpengl()
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);
}

ShaderWidget::ShaderWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}

ShaderWidget::~ShaderWidget()
{
    makeCurrent();

    m_Program.release();
    m_Vbo.destroy();
    m_Vao.destroy();

    doneCurrent();
}

void ShaderWidget::Start()
{
    m_Timer.start(12, this);
}

void ShaderWidget::Stop()
{
    m_Timer.stop();
}

void ShaderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    m_Vao.create();
    if (m_Vao.isCreated())
        m_Vao.bind();

    m_Vbo.create();
    m_Vbo.bind();

    float vertices[12] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, 1.0f,
        -1.0f, 1.0f
    };

    m_Vbo.allocate(vertices, 12 * sizeof(float));

    if (m_Program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/quad.vert"))
        if (m_Program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/quad.frag"))
            if (m_Program.link())
                if (m_Program.bind())
                {
                    m_Program.enableAttributeArray(0);
                    m_Program.setAttributeBuffer(0, GL_FLOAT, 0, 2, 0);
                }

    m_Vbo.release();
    m_Vao.release();
}

void ShaderWidget::timerEvent(QTimerEvent *vTimerEvent)
{
    m_Time += 0.012f; // 12ms is the time frame defined in Timer
    update();
}

void ShaderWidget::resizeGL(int w, int h)
{
    // Set up the rendering context, load shaders and other resources, etc.:
    glViewport(0, 0, w, h);
    m_Size.setX(w);
    m_Size.setY(h);
}

void ShaderWidget::paintGL()
{
    // Draw the scene:
    glClear(GL_COLOR_BUFFER_BIT);

    m_Program.bind();
    m_Program.setUniformValue("time", m_Time);
    m_Program.setUniformValue("size", m_Size);

    m_Vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    m_Vao.release();

    m_Program.release();
}
