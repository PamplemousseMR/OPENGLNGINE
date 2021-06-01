#include <OpenGLNgine/Render/Camera.hpp>
#include <OpenGLNgine/Render/Render.hpp>
#include <OpenGLNgine/Render/RenderWindow.hpp>

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
    ::Render::RenderWindow* const renderWindow = render.createRenderWindow("GLBase", width, height);
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

    // Init shaders.
    ::GL::Shader vertexShader(::GL::ST_VERTEX);
    vertexShader.setSourceFromFile(GLNGINE_GLSL_PATH"/Common/Default_VP.glsl");
    vertexShader.compile();

    ::GL::Shader fragmentShader(::GL::ST_FRAGMENT);
    fragmentShader.setSourceFromFile(GLNGINE_GLSL_PATH"/Common/Default_FP.glsl");
    fragmentShader.compile();

    ::GL::Program program;
    program.attach(vertexShader);
    program.attach(fragmentShader);
    program.link();

    ::GL::Uniform u_m4MVP("u_m4MVP", program.getId());

    // Init the mesh EBO, VBO and VAO.
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

    ::GL::DataBuffer meshVBO(::GL::DT_ARRAY);
    meshVBO.bind();
    meshVBO.writeData(vertexData, ::GL::DT_STATIC_DRAW);

    ::GL::DataBuffer meshEBO(::GL::DT_ELEMENT);
    meshEBO.bind();
    meshEBO.writeData(indexData, ::GL::DT_STATIC_DRAW);

    ::GL::VertexArrayBuffer meshVAO;
    meshVAO.bind();

    meshVBO.bind();

    ::GL::DataBuffer::setAttrib(::Hardware::VES_POSITION, 3, ::GL::DT_FLOAT, false, 7*sizeof(float), 0);
    ::GL::DataBuffer::setLocation(::Hardware::VES_POSITION);

    ::GL::DataBuffer::setAttrib(::Hardware::VES_COLOR_0, 4, ::GL::DT_FLOAT, false, 7*sizeof(float), 3*sizeof(float));
    ::GL::DataBuffer::setLocation(::Hardware::VES_COLOR_0);

    meshEBO.bind();

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
                    u_m4MVP = camera->getProjection() * camera->getView() * node->getFullTransform();

                    meshVAO.bind();
                    {
                        ::GL::DrawCall::drawElements(::GL::DR_TRIANGLE_STRIP, 14, ::GL::DT_UNSIGNED_INT, 0);
                    }
                }

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
