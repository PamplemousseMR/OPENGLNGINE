#include "OpenGLNgine/Render/Camera.hpp"
#include "OpenGLNgine/Render/Render.hpp"
#include "OpenGLNgine/Render/RenderWindow.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Listener : public ::Render::RenderWindowListener
{

public:

    void sizeModified(::Render::RenderWindow* const _rw, int _width, int _height) override
    {
        ::Render::Viewport* const viewport = _rw->getViewport("Viewport");
        viewport->setViewport(0, 0, _width, _height);

        ::Render::Camera* const camera = viewport->getCamera();
        camera->setProjection(camera->getFovy(), static_cast<float>(_width)/static_cast<float>(_height), camera->getNear(), camera->getFar());
    }

    void keyPressed(::Render::RenderWindow* const _rw, RENDERWINDOWLISTENER_KEY _key) override
    {
        if(_key == ::Render::RenderWindowListener::RK_ESCAPE)
        {
            _rw->shouldBeClose(true);
        }
    }

};

int main()
{
    const int width = 640;
    const int height = 480;

    // Create the render.
    ::Render::Render& render = ::Render::Render::getInstance();

    // Create a render window.
    ::Render::RenderWindow* const renderWindow = render.createRenderWindow("GLLighting", width, height);
    renderWindow->makeCurrent();
    renderWindow->setSamples(8);
    renderWindow->addListener(new Listener);

    // Create a scene manager.
    ::Render::SceneManager* const sceneManager = render.createSceneManager("SeneManager");

    // Create a camera.
    ::Render::Camera* const camera = sceneManager->createCamera("Camera");
    camera->setProjection(45.f, static_cast<float>(width)/static_cast<float>(height), 0.1f, 10.f);
    camera->setPosition({0.f, 0.f, 1.f});
    camera->lookAt({0.f, 0.f, 0.f});

    // Make the link between the camera, the scene manager and the viewport in the render window.
    ::Render::Viewport* const viewport = renderWindow->addViewport("Viewport", camera);
    viewport->setViewport(0, 0, width, height);
    viewport->setClearColor(0.8f, 0.8f, 0.8f, 0.f);

    // Create a node for the mesh.
    ::Render::SceneNode* const node = sceneManager->getRootSceneNode()->createChild("Node");
    node->setPosition({0.0f, 0.f, 0.f});

    // Create lights
    ::Render::Light* light1 = sceneManager->createLight("Light_1");
    light1->setType(::Render::LT_POINT);
    light1->setPosition(::glm::vec3(0.4f, 0.4f, 1.f));
    light1->setAmbient(::glm::vec3(0.f, 0.f, 0.f));

    ::Render::Light* light2 = sceneManager->createLight("Light_2");
    light2->setType(::Render::LT_POINT);
    light2->setPosition(::glm::vec3(-0.4f, -0.4f, 1.f));
    light2->setAmbient(::glm::vec3(0.f, 0.f, 0.f));

    // Init shaders.
    ::GL::Shader vertexShader(::GL::ST_VERTEX);
    vertexShader.setSourceFromFile(GLNGINE_GLSL_PATH"/Lighting/BlinnPhong_VP.glsl");
    vertexShader.compile();

    ::GL::Shader fragmentShader(::GL::ST_FRAGMENT);
    fragmentShader.setSourceFromFile(GLNGINE_GLSL_PATH"/Lighting/BlinnPhong_FP.glsl");
    fragmentShader.compile();

    ::GL::Program program;
    program.attach(vertexShader);
    program.attach(fragmentShader);
    program.link();

    ::GL::Uniform u_m4View("u_m4View", program.getId());
    ::GL::Uniform u_m4MV("u_m4MV", program.getId());
    ::GL::Uniform u_m4MVP("u_m4MVP", program.getId());

    ::GL::Uniform u_uiLightCount("u_uiLightCount", program.getId());
    ::GL::Uniform u_f4LightPos_Vs("u_f4LightPos_Vs", program.getId());

    ::GL::Uniform u_f3LightAmbient("u_f3LightAmbient", program.getId());
    ::GL::Uniform u_f3LightDiffuse("u_f3LightDiffuse", program.getId());
    ::GL::Uniform u_f3LightSpecular("u_f3LightSpecular", program.getId());

    // Init the mesh EBO, VBO and VAO.
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

    GL::DataBuffer meshVBO(GL::DT_ARRAY);
    meshVBO.bind();
    meshVBO.writeData(vertexData, GL::DT_STATIC_DRAW);

    GL::VertexArrayBuffer meshVAO;
    meshVAO.bind();

    meshVBO.bind();

    GL::DataBuffer::setAttrib(::Hardware::VES_POSITION, 3, GL::DT_FLOAT, false, 10*sizeof(float), 0);
    GL::DataBuffer::setLocation(::Hardware::VES_POSITION);

    GL::DataBuffer::setAttrib(::Hardware::VES_COLOR, 4, GL::DT_FLOAT, false, 10*sizeof(float), 3*sizeof(float));
    GL::DataBuffer::setLocation(::Hardware::VES_COLOR);

    GL::DataBuffer::setAttrib(::Hardware::VES_NORMAL, 3, GL::DT_FLOAT, false, 10*sizeof(float), 7*sizeof(float));
    GL::DataBuffer::setLocation(::Hardware::VES_NORMAL);

    // Render loop.
    while(render.getRenderWindows().size() > 0)
    {
        const ::Render::Render::RenderWindowList& renderWindows = render.getRenderWindows();
        for(auto rwIt = renderWindows.begin(); rwIt != renderWindows.end();)
        {
            if(!rwIt->second->shouldBeClose())
            {
                ::GL::PixelOperation::enableDepthTest(true);
                ::GL::PixelOperation::enableDepthWrite(true);

                const auto& color = viewport->getClearColor();
                ::GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);

                const auto& size = viewport->getViewport();
                ::GL::Rasterizer::setViewport(size[0], size[1], size[2], size[3]);

                ::GL::DrawCall::clear(::GL::DC_COLOR_DEPTH);

                program.bind();
                {
                    u_m4View = camera->getView();
                    u_m4MV = camera->getView() * node->getFullTransform();
                    u_m4MVP = camera->getProjection() * camera->getView() * node->getFullTransform();

                    u_uiLightCount = static_cast< unsigned >(sceneManager->getLights().size());
                    std::vector< ::glm::vec4 > lightPositionViewSpaces;
                    lightPositionViewSpaces.reserve(sceneManager->getLights().size());
                    for(const std::pair< const std::string, ::Render::Light* >& light : sceneManager->getLights())
                    {
                        lightPositionViewSpaces.push_back(camera->getView() * light.second->getShaderPosition());
                    }
                    u_f4LightPos_Vs = lightPositionViewSpaces;

                    std::vector< ::glm::vec3 > lightAmbientColors;
                    lightAmbientColors.reserve(sceneManager->getLights().size());
                    for(const std::pair< const std::string, ::Render::Light* >& light : sceneManager->getLights())
                    {
                        lightAmbientColors.push_back(light.second->getAmbient());
                    }
                    u_f3LightAmbient = lightAmbientColors;

                    std::vector< ::glm::vec3 > lightDiffuseColors;
                    lightDiffuseColors.reserve(sceneManager->getLights().size());
                    for(const std::pair< const std::string, ::Render::Light* >& light : sceneManager->getLights())
                    {
                        lightDiffuseColors.push_back(light.second->getDiffuse());
                    }
                    u_f3LightDiffuse = lightDiffuseColors;

                    std::vector< ::glm::vec3 > lightSpecularColors;
                    lightSpecularColors.reserve(sceneManager->getLights().size());
                    for(const std::pair< const std::string, ::Render::Light* >& light : sceneManager->getLights())
                    {
                        lightSpecularColors.push_back(light.second->getSpecular());
                    }
                    u_f3LightSpecular = lightSpecularColors;

                    meshVAO.bind();
                    {
                        ::GL::DrawCall::drawArrays(::GL::DR_TRIANGLES, 0, 36);
                    }
                    meshVAO.unbind();
                }
                program.unbind();

                renderWindow->swapBuffers();

                ++rwIt;
            }
            else
            {
                rwIt = render.destroyRenderWindow(rwIt->second);
            }
        }

        node->setOrientation(node->getOrientation() + ::glm::vec3(0.1f, 0.5f, 0.2f));
    }

    return EXIT_SUCCESS;
}
