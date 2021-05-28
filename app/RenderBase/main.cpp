#include <OpenGLNgine/Hardware/HardwareBufferManager.hpp>
#include <OpenGLNgine/Hardware/MaterialManager.hpp>
#include <OpenGLNgine/Hardware/ProgramManager.hpp>
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
    ::Render::RenderWindow* const renderWindow = render.createRenderWindow("RenderBase", width, height);
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

    // Create the Program.
    ::Hardware::ProgramManager& shaderMng = ::Hardware::ProgramManager::getInstance();

    ::Hardware::ShaderPtr vertexShader = shaderMng.createShader("VertexShader", ::Hardware::ST_VERTEX);
    vertexShader->setSourceFromFile(GLNGINE_GLSL_PATH"/Common/Default_VP.glsl");
    vertexShader->load();

    ::Hardware::ShaderPtr fragmentShader = shaderMng.createShader("FragmentShader", ::Hardware::ST_FRAGMENT);
    fragmentShader->setSourceFromFile(GLNGINE_GLSL_PATH"/Common/Default_FP.glsl");
    fragmentShader->load();

    // Create the material.
    ::Hardware::ProgramPtr program = shaderMng.createProgram("Program");
    program->attach(vertexShader);
    program->attach(fragmentShader);
    program->link();

    program->setNamedAutoConstant(::Hardware::PP_MODELVIEWPROJ_MATRIX, "u_m4MVP");

    ::Hardware::MaterialManager& materialMng = ::Hardware::MaterialManager::getInstance();
    ::Hardware::MaterialPtr material = materialMng.create("Material");

    material->getPasses()[0]->setProgram(program);

    material->getPasses()[0]->depthTest = true;

    // Create the mesh.
    ::Render::SceneNode* const node = sceneManager->getRootSceneNode()->createChild("Node");
    node->setPosition({0.0f, 0.f, 0.f});

    ::Render::Mesh* const mesh = sceneManager->createMesh("Mesh");
    ::Render::SubMesh* subMesh = mesh->createSubMesh("SubMesh");
    node->attach(mesh);

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

    ::Hardware::HardwareBufferManager& manager = ::Hardware::HardwareBufferManager::getInstance();

    subMesh->vertexData = manager.createVertexData();
    subMesh->vertexData->m_renderOperation = ::Hardware::VR_TRIANGLE_STRIP;

    ::Hardware::HardwareVertexBufferPtr vertexBuffer = manager.createVertexBuffer(::Hardware::VT_FLOAT, vertexData.size(), ::Hardware::HU_STATIC_DRAW);
    vertexBuffer->writeData(0, vertexBuffer->getSizeInBytes(), vertexData.data(), false);

    subMesh->vertexData->m_vertexDeclaration->addElement(0, 0, ::Hardware::VET_FLOAT3, ::Hardware::VES_POSITION);
    subMesh->vertexData->m_vertexDeclaration->addElement(0, sizeof(float)*3, ::Hardware::VET_FLOAT4, ::Hardware::VES_COLOR);

    subMesh->vertexData->m_vertexBufferBinding->setBinding(0, vertexBuffer);

    subMesh->vertexData->m_vertexCount = 8;
    subMesh->vertexData->m_vertexStart = 0;

    subMesh->indexData = manager.createIndexData();

    ::Hardware::HardwareIndexBufferPtr indexBuffer = manager.createIndexBuffer(::Hardware::IT_UNSIGNED_INT, indexData.size(), ::Hardware::HU_STATIC_DRAW);
    subMesh->indexData->m_indexBuffer = indexBuffer;

    indexBuffer->writeData(0, indexBuffer->getSizeInBytes(), indexData.data(), false);
    subMesh->indexData->m_indexCount = 14;
    subMesh->indexData->m_indexStart = 0;

    mesh->setMaterial(material);

    // Render loop.
    while(render.getRenderWindows().size() > 0)
    {
        const ::Render::Render::RenderWindowList& renderWindows = render.getRenderWindows();
        for(auto rwIt = renderWindows.begin(); rwIt != renderWindows.end();)
        {
            if(!rwIt->second->shouldBeClose())
            {
                rwIt->second->render();
                rwIt->second->swapBuffers();

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
