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
#include "OpenGLNgine/Render/Light.hpp"
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
        Render::Viewport* const viewport = _rw->getViewport("Viewport");
        viewport->setViewport(0, 0, _width, _height);

        Render::Camera* const camera = viewport->getCamera();
        camera->setProjection(camera->getFovy(), static_cast<float>(_width)/static_cast<float>(_height), camera->getNear(), camera->getFar());
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

    Render::RenderWindow* const renderWindow = render.createRenderWindow("Geometry", s_width, s_height);
    renderWindow->makeCurrent();
    renderWindow->setSamples(s_sample);
    renderWindow->addListener(new Listener);

    Render::SceneManager* const sceneManager = render.createSceneManager("SseneManager");

    Render::Camera* const camera = sceneManager->createCamera("Camera");
    camera->setProjection(45.f, static_cast<float>(s_width)/static_cast<float>(s_height), 0.1f, 10.f);
    camera->setPosition({0.f, 0.f, 1.f});
    camera->lookAt({0.f, 0.f, 0.f});

    Render::Viewport* const viewport = renderWindow->addViewport("Viewport", camera);
    viewport->setViewport(0, 0, s_width, s_height);
    viewport->setClearColor(0.8f, 0.8f, 0.8f, 0.f);

    // Init shaders

    GL::Shader vertexShader(GL::ST_VERTEX);
    vertexShader.setSourceFromFile(GLSL_PATH"/BlinnPhong/BlinnPhong_VP.glsl");
    vertexShader.compile();

    GL::Shader fragmentShader(GL::ST_FRAGMENT);
    fragmentShader.setSourceFromFile(GLSL_PATH"/BlinnPhong/BlinnPhong_FP.glsl");
    fragmentShader.compile();

    GL::Program program;
    program.attach(vertexShader);
    program.attach(fragmentShader);
    program.link();

    GL::Uniform model("u_m4Model", program.getId());
    GL::Uniform view("u_m4View", program.getId());
    GL::Uniform projection("u_m4Projection", program.getId());

    GL::Uniform lightPos_Ws("u_f4LightPos_Ws", program.getId());
    GL::Uniform lightAmbient("u_f3LightAmbient", program.getId());
    GL::Uniform lightDiffuse("u_f3LightDiffuse", program.getId());
    GL::Uniform lightSpecular("u_f3LightSpecular", program.getId());

    GL::Shader geometryVertexShader(GL::ST_VERTEX);
    geometryVertexShader.setSourceFromFile(GLSL_PATH"/Geometry/Geometry_VP.glsl");
    geometryVertexShader.compile();

    GL::Shader geometryGeometryShader(GL::ST_GEOMETRY);
    geometryGeometryShader.setSourceFromFile(GLSL_PATH"/Geometry/Geometry_GP.glsl");
    geometryGeometryShader.compile();

    GL::Shader geometryFragmentShader(GL::ST_FRAGMENT);
    geometryFragmentShader.setSourceFromFile(GLSL_PATH"/Geometry/Geometry_FP.glsl");
    geometryFragmentShader.compile();

    GL::Program geometryProgram;
    geometryProgram.attach(geometryVertexShader);
    geometryProgram.attach(geometryGeometryShader);
    geometryProgram.attach(geometryFragmentShader);
    geometryProgram.link();

    GL::Uniform geometryModel("u_m4Model", geometryProgram.getId());
    GL::Uniform geometryView("u_m4View", geometryProgram.getId());
    GL::Uniform geometryProjection("u_m4Projection", geometryProgram.getId());

    // Init VBO EBO and VAO

    const std::vector<float> vertexData = {
        -0.25f, 0.25f, 0.25f,
        0.0f, 1.0f, 1.0f, 0.5f,
        0.0f, 0.0f, 1.0f,

        0.25f, 0.25f, 0.25f,
        1.0f, 0.0f, 1.0f, 0.5f,
        0.0f, 0.0f, 1.0f,

        -0.25f, -0.25f, 0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,
        0.0f, 0.0f, 1.0f,

        0.25f, 0.25f, 0.25f,
        1.0f, 0.0f, 1.0f, 0.5f,
        0.0f, 0.0f, 1.0f,

        -0.25f, -0.25f, 0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,
        0.0f, 0.0f, 1.0f,

        0.25f, -0.25f, 0.25f,
        0.0f, 1.0f, 0.0f, 0.5f,
        0.0f, 0.0f, 1.0f,

        -0.25f, -0.25f, 0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,
        0.0f, -1.0f, 0.0f,

        0.25f, -0.25f, 0.25f,
        0.0f, 1.0f, 0.0f, 0.5f,
        0.0f, -1.0f, 0.0f,

        0.25f, -0.25f, -0.25f,
        1.0f, 0.0f, 0.0f, 0.5f,
        0.0f, -1.0f, 0.0f,

        0.25f, -0.25f, 0.25f,
        0.0f, 1.0f, 0.0f, 0.5f,
        1.0f, 0.0f, 0.0f,

        0.25f, -0.25f, -0.25f,
        1.0f, 0.0f, 0.0f, 0.5f,
        1.0f, 0.0f, 0.0f,

        0.25f, 0.25f, 0.25f,
        1.0f, 0.0f, 1.0f, 0.5f,
        1.0f, 0.0f, 0.0f,

        0.25f, -0.25f, -0.25f,
        1.0f, 0.0f, 0.0f, 0.5f,
        1.0f, 0.0f, 0.0f,

        0.25f, 0.25f, 0.25f,
        1.0f, 0.0f, 1.0f, 0.5f,
        1.0f, 0.0f, 0.0f,

        0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 1.0f, 0.5f,
        1.0f, 0.0f, 0.0f,

        0.25f, 0.25f, 0.25f,
        1.0f, 0.0f, 1.0f, 0.5f,
        0.0f, 1.0f, 0.0f,

        0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 1.0f, 0.5f,
        0.0f, 1.0f, 0.0f,

        -0.25f, 0.25f, 0.25f,
        0.0f, 1.0f, 1.0f, 0.5f,
        0.0f, 1.0f, 0.0f,

        0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 1.0f, 0.5f,
        0.0f, 1.0f, 0.0f,

        -0.25f, 0.25f, 0.25f,
        0.0f, 1.0f, 1.0f, 0.5f,
        0.0f, 1.0f, 0.0f,

        -0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 0.0f, 0.5f,
        0.0f, 1.0f, 0.0f,

        -0.25f, 0.25f, 0.25f,
        0.0f, 1.0f, 1.0f, 0.5f,
        -1.0f, 0.0f, 0.0f,

        -0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 0.0f, 0.5f,
        -1.0f, 0.0f, 0.0f,

        -0.25f, -0.25f, 0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,
        -1.0f, 0.0f, 0.0f,

        -0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 0.0f, 0.5f,
        -1.0f, 0.0f, 0.0f,

        -0.25f, -0.25f, 0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,
        -1.0f, 0.0f, 0.0f,

        -0.25f, -0.25f, -0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,
        -1.0f, 0.0f, 0.0f,

        -0.25f, -0.25f, 0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,
        0.0f, -1.0f, 0.0f,

        -0.25f, -0.25f, -0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,
        0.0f, -1.0f, 0.0f,

        0.25f, -0.25f, -0.25f,
        1.0f, 0.0f, 0.0f, 0.5f,
        0.0f, -1.0f, 0.0f,

        -0.25f, -0.25f, -0.25f,
        0.0f, 0.0f, 1.0f, 0.5f,
        0.0f, 0.0f, -1.0f,

        0.25f, -0.25f, -0.25f,
        1.0f, 0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, -1.0f,

        -0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 0.0f, 0.5f,
        0.0f, 0.0f, -1.0f,

        0.25f, -0.25f, -0.25f,
        1.0f, 0.0f, 0.0f, 0.5f,
        0.0f, 0.0f, -1.0f,

        -0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 0.0f, 0.5f,
        0.0f, 0.0f, -1.0f,

        0.25f, 0.25f, -0.25f,
        1.0f, 1.0f, 1.0f, 0.5f,
        0.0f, 0.0f, -1.0f,
    };

    GL::DataBuffer cubeVBO(GL::DT_ARRAY);
    cubeVBO.bind();
    cubeVBO.writeData(vertexData, GL::DT_STATIC_DRAW);

    GL::VertexArrayBuffer cubeVAO;
    cubeVAO.bind();

    cubeVBO.bind();

    GL::DataBuffer::setAttrib(0, 3, GL::DT_FLOAT, false, 10*sizeof(float), 0);
    GL::DataBuffer::setLocation(0);

    GL::DataBuffer::setAttrib(1, 4, GL::DT_FLOAT, false, 10*sizeof(float), 3*sizeof(float));
    GL::DataBuffer::setLocation(1);

    GL::DataBuffer::setAttrib(2, 3, GL::DT_FLOAT, false, 10*sizeof(float), 7*sizeof(float));
    GL::DataBuffer::setLocation(2);

    // Create lights

    Render::Light light;
    light.setType(Render::LT_POINT);
    light.setPosition(::glm::vec3(0.f, 0.f, -100.f));
    light.setAmbient(::glm::vec3(0.1f, 0.1f, 0.1f));
    light.setDiffuse(::glm::vec3(1.f, 1.f, 1.f));
    light.setSpecular(::glm::vec3(1.f, 1.f, 1.f));

    // Init standar gl enable

    GL::PixelOperation::enableDepthTest(true);
    GL::PixelOperation::enableDepthWrite(true);

    glm::mat4 cubeModel(1.f);

    while(!renderWindow->shouldBeClose())
    {
        const auto& color = viewport->getClearColor();
        GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);

        const auto& size = viewport->getViewport();
        GL::Rasterizer::setViewport(size[0], size[1], size[2], size[3]);

        GL::DrawCall::clear(GL::DC_COLOR_DEPTH);

        cubeVAO.bind();
        {
            program.bind();
            {
                model = cubeModel;
                view = camera->getView();
                projection = camera->getProjection();

                lightPos_Ws = light.getShaderPosition();
                lightAmbient = light.getAmbient();
                lightDiffuse = light.getDiffuse();
                lightSpecular = light.getSpecular();

                GL::DrawCall::drawArrays(GL::DR_TRIANGLES, 0, 36);
            }
            program.unbind();

            geometryProgram.bind();
            {
                geometryModel = cubeModel;
                geometryView = camera->getView();
                geometryProjection = camera->getProjection();

                GL::DrawCall::drawArrays(GL::DR_TRIANGLES, 0, 36);        }
            geometryProgram.unbind();
        }
        cubeVAO.unbind();

        renderWindow->swapBuffers();

        cubeModel = glm::rotate(cubeModel, 0.01f, glm::vec3(0.8f, 0.5f, 1.f));
    }

    renderWindow->removeViewport(viewport);
    sceneManager->destroyCamera(camera);
    render.destroyRenderWindow(renderWindow);

    return EXIT_SUCCESS;
}