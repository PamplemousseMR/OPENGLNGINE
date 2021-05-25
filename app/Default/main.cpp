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
#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"
#include "OpenGLNgine/Hardware/MaterialManager.hpp"
#include "OpenGLNgine/Hardware/ProgramManager.hpp"
#include "OpenGLNgine/Render/Camera.hpp"
#include "OpenGLNgine/Render/Render.hpp"
#include "OpenGLNgine/Render/RenderWindow.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

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
    const int width = 640;
    const int height = 480;

    // Create the render.
    Render::Render& render = Render::Render::getInstance();

    // Create a render window.
    Render::RenderWindow* const renderWindow = render.createRenderWindow("Default", width, height);
    renderWindow->makeCurrent();
    renderWindow->setSamples(8);
    renderWindow->addListener(new Listener);

    // Create a scene manager.
    Render::SceneManager* const sceneManager = render.createSceneManager("SeneManager");

    // Create a camera.
    Render::Camera* const camera = sceneManager->createCamera("Camera");
    camera->setProjection(45.f, static_cast<float>(width)/static_cast<float>(height), 0.1f, 10.f);
    camera->setPosition({0.f, 0.f, 1.f});
    camera->lookAt({0.f, 0.f, 0.f});

    // Make the link between the camera, the scene manager and the viewport in the render window.
    Render::Viewport* const viewport = renderWindow->addViewport("Viewport", camera);
    viewport->setViewport(0, 0, width, height);
    viewport->setClearColor(0.8f, 0.8f, 0.8f, 0.f);

    // Create the Program.
    Hardware::ProgramManager& shaderMng = Hardware::ProgramManager::getInstance();

    Hardware::ShaderPtr vertexShader = shaderMng.createShader("VertexShader", Hardware::ST_VERTEX);
    vertexShader->setSourceFromFile(GLSL_PATH"/Common/Default_VP.glsl");
    vertexShader->load();

    Hardware::ShaderPtr fragmentShader = shaderMng.createShader("FragmentShader", Hardware::ST_FRAGMENT);
    fragmentShader->setSourceFromFile(GLSL_PATH"/Common/Default_FP.glsl");
    fragmentShader->load();

    // Create the material.
    Hardware::ProgramPtr program = shaderMng.createProgram("Program");
    program->attach(vertexShader);
    program->attach(fragmentShader);
    program->link();

    program->setNamedAutoConstant(Hardware::PP_WORLDVIEWPROJ_MATRIX, "u_m4MVP");

    Hardware::MaterialManager& materialMng = Hardware::MaterialManager::getInstance();
    Hardware::MaterialPtr material = materialMng.create("Material");

    material->getPasses()[0]->setProgram(program);

    material->getPasses()[0]->depthTest = true;

    // Create the mesh.
    Render::SceneNode* const node = sceneManager->getRootSceneNode()->createChild("Node");
    node->setPosition({0.0f, 0.f, 0.f});

    Render::Mesh* const mesh = sceneManager->createMesh("Mesh");
    Render::SubMesh* subMesh = mesh->createSubMesh("SubMesh");
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

    Hardware::HardwareBufferManager& manager = Hardware::HardwareBufferManager::getInstance();

    subMesh->vertexData = manager.createVertexData();
    subMesh->vertexData->m_renderOperation = Hardware::VR_TRIANGLE_STRIP;

    Hardware::HardwareVertexBufferPtr vertexBuffer = manager.createVertexBuffer(Hardware::VT_FLOAT, vertexData.size(), Hardware::HU_STATIC_DRAW);
    vertexBuffer->writeData(0, vertexBuffer->getSizeInBytes(), vertexData.data(), false);

    subMesh->vertexData->m_vertexDeclaration->addElement(0, 0, Hardware::VET_FLOAT3, Hardware::VES_POSITION);
    subMesh->vertexData->m_vertexDeclaration->addElement(0, sizeof(float)*3, Hardware::VET_FLOAT4, Hardware::VES_COLOR);

    subMesh->vertexData->m_vertexBufferBinding->setBinding(0, vertexBuffer);

    subMesh->vertexData->m_vertexCount = 8;
    subMesh->vertexData->m_vertexStart = 0;

    subMesh->indexData = manager.createIndexData();

    Hardware::HardwareIndexBufferPtr indexBuffer = manager.createIndexBuffer(Hardware::IT_UNSIGNED_INT, indexData.size(), Hardware::HU_STATIC_DRAW);
    subMesh->indexData->m_indexBuffer = indexBuffer;

    indexBuffer->writeData(0, indexBuffer->getSizeInBytes(), indexData.data(), false);
    subMesh->indexData->m_indexCount = 14;
    subMesh->indexData->m_indexStart = 0;

    mesh->setMaterial(material);

    // RENDER
    while(!renderWindow->shouldBeClose())
    {
        for(const auto& rw : render.getRenderWindows())
        {
            rw.second->makeCurrent();

            for(const auto& vp : rw.second->getViewports())
            {
                const auto& size = vp.second->getViewport();
                GL::Rasterizer::setViewport(size[0], size[1], size[2], size[3]);
                GL::Rasterizer::enableScissorTest(true);
                GL::Rasterizer::setScissor(size[0], size[1], size[2], size[3]);

                const auto& color = vp.second->getClearColor();

                GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);
                GL::DrawCall::clear(GL::DC_COLOR_DEPTH);
                GL::Rasterizer::enableScissorTest(false);

                const Render::Camera* const cam = vp.second->getCamera();

                const Render::SceneManager* const sm = cam->getSceneManager();

                for(const auto& me : sm->getMeshes())
                {
                    if(me.second->isAttached())
                    {
                        Render::SceneNode* n = me.second->getParent();

                        for(const Render::SubMesh* subMesh : me.second->getSubMeshes())
                        {
                            if(subMesh->material != nullptr)
                            {
                                const Hardware::MaterialPtr& mat = subMesh->material;
                                for(Hardware::Pass* pass : mat->getPasses())
                                {
                                    pass->lock();

                                    for(std::pair<Hardware::PROGRAM_PARAMETER, GL::Uniform> parameter : pass->getProgramParameters())
                                    {
                                        switch(parameter.first)
                                        {
                                        case Hardware::PP_WORLDVIEWPROJ_MATRIX:
                                            parameter.second = cam->getProjection() * cam->getView() * n->getFullTransform();
                                            break;
                                        default:
                                            GLNGINE_EXCEPTION("Unhandle program parameter");
                                        }
                                    }

                                    GL::PixelOperation::enableDepthTest(pass->depthTest);
                                    GL::PixelOperation::enableDepthWrite(pass->depthWrite);
                                    GL::PixelOperation::setDepthFunc(Hardware::Pass::getType(pass->depthFunc));
                                    GL::PixelOperation::enableBlendTest(pass->blendTest);
                                    GL::PixelOperation::setBlendFunc(Hardware::Pass::getType(pass->sourceFactor), Hardware::Pass::getType(pass->destinationFactor));
                                    GL::PixelOperation::setColorMask(pass->colorMask[0], pass->colorMask[1], pass->colorMask[2], pass->colorMask[3]);

                                    subMesh->render();
                                }
                            }
                        }
                    }
                }
            }
        }

        node->setOrientation(node->getOrientation() + glm::vec3(0.1f, 0.5f, 0.2f));
        renderWindow->swapBuffers();
    }

    return EXIT_SUCCESS;
}
