#include "OpenGLNgine/GL/PixelOperation.hpp"
#include "OpenGLNgine/GL/Program.hpp"
#include "OpenGLNgine/GL/Rasterizer.hpp"
#include "OpenGLNgine/GL/Shader.hpp"
#include "OpenGLNgine/GL/Uniform.hpp"
#include "OpenGLNgine/GL/Texture.hpp"
#include "OpenGLNgine/GL/RenderBuffer.hpp"
#include "OpenGLNgine/GL/FrameBuffer.hpp"
#include "OpenGLNgine/GL/DrawCall.hpp"
#include "OpenGLNgine/GL/VertexArrayBuffer.hpp"
#include "OpenGLNgine/Render/Camera.hpp"
#include "OpenGLNgine/Render/Render.hpp"
#include "OpenGLNgine/Render/RenderWindow.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

static const int s_width = 640;
static const int s_height = 480;
static const int s_sample = 8;

class Listener : public Render::RenderWindowListener
{

public:

    void sizeModified(Render::RenderWindow* const _rw, int _width, int _height) override
    {
        Render::Viewport* const viewport1 = _rw->getViewport("Viewport1");
        viewport1->setViewport(0, 0, _width/2, _height/2);

        Render::Viewport* const viewport2 = _rw->getViewport("Viewport2");
        viewport2->setViewport(0, _height/2, _width/2, _height/2);

        Render::Camera* const camera1 = viewport1->getCamera();
        camera1->setProjection(camera1->getFovy(), static_cast<float>(_width/2)/static_cast<float>(_height/2), camera1->getNear(), camera1->getFar());

        Render::Viewport* const viewport3 = _rw->getViewport("Viewport3");
        viewport3->setViewport(_width/2, 0, _width/2, _height);

        Render::Camera* const camera2 = viewport3->getCamera();
        camera2->setProjection(camera2->getFovy(), static_cast<float>(_width/2)/static_cast<float>(_height), camera2->getNear(), camera2->getFar());
    }

    void keyPressed(Render::RenderWindow* const _rw, RENDERWINDOWLISTENER_KEY _key) override
    {
        if(_key == Render::RenderWindowListener::RK_ESCAPE)
        {
            _rw->shouldBeClose(true);
        }
    }

};

int main()
{
    // Init window

    Render::Render& render = Render::Render::getInstance();

    Render::RenderWindow* const renderWindow = render.createRenderWindow("Viewports", s_width, s_height);
    renderWindow->makeCurrent();
    renderWindow->setSamples(s_sample);
    renderWindow->addListener(new Listener);

    Render::Camera* const camera1 = render.createCamera("Camera1");
    camera1->setProjection(45.f, static_cast<float>(s_width/2)/static_cast<float>(s_height/2), 0.1f, 10.f);
    camera1->setPosition({0.f, 0.f, 1.f});
    camera1->lookAt({0.f, 0.f, 0.f});

    Render::Viewport* const viewport1 = renderWindow->addViewport("Viewport1", camera1);
    viewport1->setViewport(0, 0, s_width/2, s_height/2);
    viewport1->setClearColor(0.8f, 0.8f, 0.8f, 0.f);

    Render::Viewport* const viewport2 = renderWindow->addViewport("Viewport2", camera1);
    viewport2->setViewport(0, s_height/2, s_width/2, s_height/2);
    viewport2->setClearColor(0.7f, 0.7f, 0.7f, 0.f);

    Render::Camera* const camera2 = render.createCamera("Camera2");
    camera2->setProjection(45.f, static_cast<float>(s_width/2)/static_cast<float>(s_height), 0.1f, 10.f);
    camera2->setPosition({3.f, 0.f, 0.f});
    camera2->lookAt({0.f, 0.f, 0.f});

    Render::Viewport* const viewport3 = renderWindow->addViewport("Viewport3", camera2);
    viewport3->setViewport(s_width/2, 0, s_width/2, s_height);
    viewport3->setClearColor(0.9f, 0.9f, 0.9f, 0.f);

    // Init shaders

    GL::Shader vertexShader(GL::ST_VERTEX);
    vertexShader.setSourceFromFile(GLSL_PATH"/Default/Default_VP.glsl");
    vertexShader.compile();

    GL::Shader fragmentShader(GL::ST_FRAGMENT);
    fragmentShader.setSourceFromFile(GLSL_PATH"/Default/Default_FP.glsl");
    fragmentShader.compile();

    GL::Program program;
    program.attach(vertexShader);
    program.attach(fragmentShader);
    program.link();

    GL::Uniform model("u_m4Model", program.getId());
    GL::Uniform view("u_m4View", program.getId());
    GL::Uniform projection("u_m4Projection", program.getId());

    // Init VBO EBO and VAO

    const std::vector<float> vertexData = {
        0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 1.0f, 0.5f,

        -0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 0.0f, 0.5f,

        0.25f, 0.25f, 0.25f,
        1.0f, 0.0f, 1.0f, 0.5f,

        -0.25f, 0.25f, 0.25f,
        0.0f, 1.0f, 1.0f, 0.5f,

        0.25f, -0.25f, -0.25f,
        1.0f, 0.0f, 0.0f, 0.5f,

        -0.25f, -0.25f, -0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,

        -0.25f, -0.25f, 0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,

        0.25f, -0.25f, 0.25f,
        0.0f, 1.0f, 0.0f, 0.5f,
    };

    const std::vector<unsigned int> indexData = {
        3, 2, 6, 7, 4, 2, 0, 3, 1, 6, 5, 4, 1, 0
    };

    GL::DataBuffer cubeVBO(GL::DT_ARRAY);
    cubeVBO.bind();
    cubeVBO.writeData(vertexData, GL::DT_STATIC_DRAW);

    GL::DataBuffer cubeEBO(GL::DT_ELEMENT);
    cubeEBO.bind();
    cubeEBO.writeData(indexData, GL::DT_STATIC_DRAW);

    GL::VertexArrayBuffer cubeVAO;
    cubeVAO.bind();

    cubeVBO.bind();

    GL::DataBuffer::setAttrib(0, 3, GL::DT_FLOAT, false, 7*sizeof(float), 0);
    GL::DataBuffer::setLocation(0);

    GL::DataBuffer::setAttrib(1, 4, GL::DT_FLOAT, false, 7*sizeof(float), 3*sizeof(float));
    GL::DataBuffer::setLocation(1);

    cubeEBO.bind();

    // Init standar gl enable

    GL::PixelOperation::enableDepthTest(true);
    GL::PixelOperation::enableDepthWrite(true);

    glm::mat4 cubeModel(1.f);

    while(!renderWindow->shouldBeClose())
    {
        GL::Rasterizer::enableScissorTest(false);
        GL::DrawCall::clear(GL::DC_DEPTH);
        GL::Rasterizer::enableScissorTest(true);
        program.bind();
        cubeVAO.bind();

        {
            const auto& color = viewport1->getClearColor();
            GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);

            const auto& size = viewport1->getViewport();
            GL::Rasterizer::setViewport(size[0], size[1], size[2], size[3]);
            GL::Rasterizer::setScissor(size[0], size[1], size[2], size[3]);

            GL::DrawCall::clear(GL::DC_COLOR);

            model = cubeModel;
            view = viewport1->getCamera()->getView();
            projection = viewport1->getCamera()->getProjection();

            GL::DrawCall::drawElements(GL::DR_TRIANGLE_STRIP, 14, GL::DT_UNSIGNED_INT, 0);
        }
        {
            const auto& color = viewport2->getClearColor();
            GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);

            const auto& size = viewport2->getViewport();
            GL::Rasterizer::setViewport(size[0], size[1], size[2], size[3]);
            GL::Rasterizer::setScissor(size[0], size[1], size[2], size[3]);

            GL::DrawCall::clear(GL::DC_COLOR);

            model = cubeModel;
            view = viewport2->getCamera()->getView();
            projection = viewport2->getCamera()->getProjection();

            GL::DrawCall::drawElements(GL::DR_TRIANGLE_STRIP, 14, GL::DT_UNSIGNED_INT, 0);
        }
        {
            const auto& color = viewport3->getClearColor();
            GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);

            const auto& size = viewport3->getViewport();
            GL::Rasterizer::setViewport(size[0], size[1], size[2], size[3]);
            GL::Rasterizer::setScissor(size[0], size[1], size[2], size[3]);

            GL::DrawCall::clear(GL::DC_COLOR);

            model = cubeModel;
            view = viewport3->getCamera()->getView();
            projection = viewport3->getCamera()->getProjection();

            GL::DrawCall::drawElements(GL::DR_TRIANGLE_STRIP, 14, GL::DT_UNSIGNED_INT, 0);
        }

        cubeVAO.unbind();
        program.unbind();

        renderWindow->swapBuffers();

        cubeModel = glm::rotate(cubeModel, 0.01f, glm::vec3(1.f, 1.f, 0.f));
    }

    renderWindow->removeViewport(viewport3);
    render.destroyCamera(camera2);
    renderWindow->removeViewport(viewport2);
    renderWindow->removeViewport(viewport1);
    render.destroyCamera(camera1);
    render.destroyRenderWindow(renderWindow);

    return EXIT_SUCCESS;
}
