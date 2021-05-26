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
        ::Render::Viewport* const viewport1 = _rw->getViewport("Viewport_1");
        viewport1->setViewport(0, 0, _width/2, _height/2);

        ::Render::Viewport* const viewport2 = _rw->getViewport("Viewport_2");
        viewport2->setViewport(_width/2, 0, _width/2, _height/2);

        ::Render::Viewport* const viewport3 = _rw->getViewport("Viewport_3");
        viewport3->setViewport(0, _height/2, _width/2, _height/2);

        ::Render::Viewport* const viewport4 = _rw->getViewport("Viewport_4");
        viewport4->setViewport(_width/2, _height/2, _width/2, _height/2);

        ::Render::Camera* const camera = viewport1->getCamera();
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
    ::Render::RenderWindow* const renderWindow = render.createRenderWindow("GLViewports", width, height);
    renderWindow->makeCurrent();
    renderWindow->setSamples(8);
    renderWindow->addListener(new Listener);

    // Create a scene manager.
    ::Render::SceneManager* const sceneManager = render.createSceneManager("SeneManager");

    // Create a camera.
    ::Render::Camera* const camera = sceneManager->createCamera("Camera");
    camera->setProjection(45.f, static_cast<float>(width/2)/static_cast<float>(height/2), 0.1f, 10.f);
    camera->setPosition({0.f, 0.f, 1.f});
    camera->lookAt({0.f, 0.f, 0.f});

    // Make the link between the camera, the scene manager and viewports in the render window.
    ::Render::Viewport* const viewport1 = renderWindow->addViewport("Viewport_1", camera);
    viewport1->setViewport(0, 0, width/2, height/2);
    viewport1->setClearColor(0.0f, 1.0f, 0.0f, 0.f);

    ::Render::Viewport* const viewport2 = renderWindow->addViewport("Viewport_2", camera);
    viewport2->setViewport(width/2, 0, width/2, height/2);
    viewport2->setClearColor(1.0f, 1.0f, 0.0f, 0.f);

    ::Render::Viewport* const viewport3 = renderWindow->addViewport("Viewport_3", camera);
    viewport3->setViewport(0, height/2, width/2, height/2);
    viewport3->setClearColor(0.0f, 0.0f, 1.0f, 0.f);

    ::Render::Viewport* const viewport4 = renderWindow->addViewport("Viewport_4", camera);
    viewport4->setViewport(width/2, height/2, width/2, height/2);
    viewport4->setClearColor(1.0f, 0.0f, 0.0f, 0.f);

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

    ::GL::DataBuffer::setAttrib(::Hardware::VES_COLOR, 4, ::GL::DT_FLOAT, false, 7*sizeof(float), 3*sizeof(float));
    ::GL::DataBuffer::setLocation(::Hardware::VES_COLOR);


    meshEBO.bind();

    // Render loop.
    while(render.getRenderWindows().size() > 0)
    {
        const ::Render::Render::RenderWindowList& renderWindows = render.getRenderWindows();
        for(auto rwIt = renderWindows.begin(); rwIt != renderWindows.end();)
        {
            if(!rwIt->second->shouldBeClose())
            {
                for(const auto& vp : rwIt->second->getViewports())
                {
                    ::GL::PixelOperation::enableDepthTest(true);
                    ::GL::PixelOperation::enableDepthWrite(true);
                    ::GL::Rasterizer::enableScissorTest(true);

                    const auto& color = vp.second->getClearColor();
                    ::GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);

                    const auto& size = vp.second->getViewport();
                    ::GL::Rasterizer::setViewport(size[0], size[1], size[2], size[3]);
                    ::GL::Rasterizer::setScissor(size[0], size[1], size[2], size[3]);

                    ::GL::DrawCall::clear(::GL::DC_COLOR_DEPTH);

                    program.bind();
                    {
                        u_m4MVP = camera->getProjection() * camera->getView() * node->getFullTransform();

                        meshVAO.bind();
                        {
                            ::GL::DrawCall::drawElements(::GL::DR_TRIANGLE_STRIP, 14, ::GL::DT_UNSIGNED_INT, 0);
                        }
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
