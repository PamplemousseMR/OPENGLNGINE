#include "OpenGLNgine/GL/PixelOperation.hpp"
#include "OpenGLNgine/GL/Program.hpp"
#include "OpenGLNgine/GL/Rasterizer.hpp"
#include "OpenGLNgine/GL/Shader.hpp"
#include "OpenGLNgine/GL/Uniform.hpp"
#include "OpenGLNgine/Hardware/HardwareBufferManager.hpp"
#include "OpenGLNgine/Hardware/MaterialManager.hpp"
#include "OpenGLNgine/Hardware/ProgramManager.hpp"
#include "OpenGLNgine/Render/Camera.hpp"
#include "OpenGLNgine/Render/Render.hpp"
#include "OpenGLNgine/Render/RenderWindow.hpp"
#include "OpenGLNgine/Render/SubMesh.hpp"

#include <iostream>

using namespace std;

static const int s_width = 800;
static const int s_height = 450;

class Listener : public Render::RenderWindowListener
{

public:

    void sizeModified(Render::RenderWindow* const _rw, int _width, int _height) override
    {
        {
            Render::Viewport* const viewport = _rw->getViewport("Viewport1");
            viewport->setViewport(0, 0, _width/2, _height/2);
        }
        {
            Render::Viewport* const viewport = _rw->getViewport("Viewport2");
            viewport->setViewport(0, _height/2, _width/2, _height/2);
        }
        {
            Render::Viewport* const viewport = _rw->getViewport("Viewport3");
            viewport->setViewport(_width/2, 0, _width/2, _height);
        }
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
    try
    {
        Render::Render& render = Render::Render::getInstance();

        Render::RenderWindow* const renderWindow = render.createRenderWindow("OPENGLNGINE", s_width, s_height);
        renderWindow->setSamples(4);
        renderWindow->addListener(new Listener);
        renderWindow->makeCurrent();

        Render::SceneManager* const sceneManager = render.createSceneManager("SseneManager");

        Render::Camera* const camera1 = sceneManager->createCamera("Camera1");
        camera1->setProjection(45.f, 1920.f/1080.f, 0.1f, 10.f);
        camera1->setPosition({0.f, 0.f, 1.f});
        camera1->lookAt({0.f, 0.f, 0.f});

        Render::SceneNode* const nodeCamera1 = sceneManager->getRootSceneNode()->createChild("NodeCamera1");
        nodeCamera1->attach(camera1);

        Render::Viewport* const viewport1 = renderWindow->addViewport("Viewport1", camera1);
        viewport1->setViewport(0, 0, s_width/2, s_height/2);
        viewport1->setClearColor(0.8f, 0.8f, 0.8f, 0.f);

        Render::Viewport* const viewport2 = renderWindow->addViewport("Viewport2", camera1);
        viewport2->setViewport(0, s_height/2, s_width/2, s_height/2);
        viewport2->setClearColor(0.9f, 0.9f, 0.9f, 0.f);

        Render::Camera* const camera2 = sceneManager->createCamera("Camera2");
        camera2->setProjection(45.f, 960.f/1080.f, 0.1f, 10.f);
        camera2->setPosition({0.f, 0.f, 2.f});
        camera2->lookAt({0.f, 0.f, 0.f});

        Render::SceneNode* const nodeCamera2 = sceneManager->getRootSceneNode()->createChild("NodeCamera2");
        nodeCamera2->attach(camera2);

        Render::Viewport* const viewport3 = renderWindow->addViewport("Viewport3", camera2);
        viewport3->setViewport(s_width/2, 0, s_width/2, s_height);
        viewport3->setClearColor(0.7f, 0.7f, 0.7f, 0.f);

        Render::SceneNode* const node1 = sceneManager->getRootSceneNode()->createChild("Node1");
        node1->setPosition({-0.5f, 0.f, 0.f});

        Render::Mesh* const mesh1 = sceneManager->createMesh("Mesh1");
        Render::SubMesh* subMesh1 = mesh1->createSubMesh("SubMesh1");
        node1->attach(mesh1);

        // Create the mesh
        {
            const std::vector<float> vertexBufferData = {
                -0.25f, -0.25f, 0.25f,
                1.0f, 0.f, 0.f,
                0.25f, -0.25f, 0.25f,
                0.f, 1.0f, 0.f,
                0.f, 0.25f, 0.f,
                0.f, 0.f, 1.0f,

                0.25f, -0.25f, 0.25f,
                0.f, 1.0f, 0.f,
                0.f, -0.25f, -0.25f,
                0.f, 1.0f, 0.f,
                0.f, 0.25f, 0.f,
                0.f, 0.f, 1.0f,

                0.f, -0.25f, -0.25f,
                0.f, 1.0f, 0.f,
                -0.25f, -0.25f, 0.25f,
                1.0f, 0.f, 0.f,
                0.f, 0.25f, 0.f,
                0.f, 0.f, 1.0f,

                -0.25f, -0.25f, 0.25f,
                1.0f, 0.f, 0.f,
                0.25f, -0.25f, 0.25f,
                0.f, 1.0f, 0.f,
                0.f, -0.25f, -0.25f,
                0.f, 1.0f, 0.f,
            };

            Hardware::HardwareBufferManager& manager = Hardware::HardwareBufferManager::getInstance();

            subMesh1->vertexData = manager.createVertexData();
            subMesh1->useSharedVertices = false;
            subMesh1->vertexData->m_renderOperation = Hardware::VR_TRIANGLES;

            Hardware::HardwareVertexBufferPtr vertexBuffer = manager.createVertexBuffer(Hardware::VT_FLOAT, vertexBufferData.size(), Hardware::HU_STATIC_DRAW);
            vertexBuffer->writeData(0, vertexBuffer->getSizeInBytes(), vertexBufferData.data(), false);

            subMesh1->vertexData->m_vertexDeclaration->addElement(0, 0, Hardware::VET_FLOAT3, Hardware::VES_POSITION);
            subMesh1->vertexData->m_vertexDeclaration->addElement(0, sizeof(float)*3, Hardware::VET_FLOAT3, Hardware::VES_COLOR);

            subMesh1->vertexData->m_vertexBufferBinding->setBinding(0, vertexBuffer);

            subMesh1->vertexData->m_vertexCount = 12;

            // Create VAO.
            subMesh1->vertexData->m_vertexDeclaration->lock();
            for(const auto& binding : subMesh1->vertexData->m_vertexBufferBinding->getBufferBindings())
            {
                const Hardware::HardwareVertexBufferPtr buffer = binding.second;
                buffer->lock();

                int stride = 0;

                const Hardware::VertexDeclaration::VertexElementList& elements = subMesh1->vertexData->m_vertexDeclaration->getElements();
                for(const Hardware::VertexElement& element : elements)
                {
                    if(element.m_source == binding.first)
                    {
                        stride += element.getTypeCount();
                    }
                }

                for(const Hardware::VertexElement& element : elements)
                {
                    const int offset = element.m_offsetInBytes + subMesh1->vertexData->m_vertexStart * buffer->m_vertexType;
                    GL::DataBuffer::setAttrib(element.m_semantic, element.getTypeCount(), element.getType(), false, buffer->m_vertexType*stride, offset);
                    GL::DataBuffer::setLocation(element.m_semantic);
                }
            }
            subMesh1->vertexData->m_vertexDeclaration->unlock();
        }

        Render::SceneNode* const node2 = sceneManager->getRootSceneNode()->createChild("Node2");
        node2->setPosition({0.5f, 0.f, 0.f});

        Render::Mesh* const mesh2 = sceneManager->createMesh("Mesh2");
        Render::SubMesh* subMesh2 = mesh2->createSubMesh("SubMesh2");
        node2->attach(mesh2);

        // Create the mesh
        {
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

            mesh2->sharedVertexData = manager.createVertexData();
            subMesh2->useSharedVertices = true;
            mesh2->sharedVertexData->m_renderOperation = Hardware::VR_TRIANGLE_STRIP;

            Hardware::HardwareVertexBufferPtr vertexBuffer = manager.createVertexBuffer(Hardware::VT_FLOAT, vertexData.size(), Hardware::HU_STATIC_DRAW);
            vertexBuffer->writeData(0, vertexBuffer->getSizeInBytes(), vertexData.data(), false);

            mesh2->sharedVertexData->m_vertexDeclaration->addElement(0, 0, Hardware::VET_FLOAT3, Hardware::VES_POSITION);
            mesh2->sharedVertexData->m_vertexDeclaration->addElement(0, sizeof(float)*3, Hardware::VET_FLOAT4, Hardware::VES_COLOR);

            mesh2->sharedVertexData->m_vertexBufferBinding->setBinding(0, vertexBuffer);

            mesh2->sharedVertexData->m_vertexCount = 8;
            mesh2->sharedVertexData->m_vertexStart = 0;

            subMesh2->indexData = manager.createIndexData();

            Hardware::HardwareIndexBufferPtr indexBuffer = manager.createIndexBuffer(Hardware::IT_UNSIGNED_INT, indexData.size(), Hardware::HU_STATIC_DRAW);
            subMesh2->indexData->m_indexBuffer = indexBuffer;

            indexBuffer->writeData(0, indexBuffer->getSizeInBytes(), indexData.data(), false);
            subMesh2->indexData->m_indexCount = 14;
            subMesh2->indexData->m_indexStart = 0;

            // Create VAO.
            mesh2->sharedVertexData->m_vertexDeclaration->lock();
            for(const auto& binding : mesh2->sharedVertexData->m_vertexBufferBinding->getBufferBindings())
            {
                const Hardware::HardwareVertexBufferPtr buffer = binding.second;
                buffer->lock();

                int stride = 0;

                const Hardware::VertexDeclaration::VertexElementList& elements = mesh2->sharedVertexData->m_vertexDeclaration->getElements();
                for(const Hardware::VertexElement& element : elements)
                {
                    if(element.m_source == binding.first)
                    {
                        stride += element.getTypeCount();
                    }
                }

                for(const Hardware::VertexElement& element : elements)
                {
                    const int offset = element.m_offsetInBytes + mesh2->sharedVertexData->m_vertexStart * buffer->m_vertexType;
                    GL::DataBuffer::setAttrib(element.m_semantic, element.getTypeCount(), element.getType(), false, buffer->m_vertexType*stride, offset);
                    GL::DataBuffer::setLocation(element.m_semantic);
                }

                subMesh2->indexData->m_indexBuffer->lock();
            }
            mesh2->sharedVertexData->m_vertexDeclaration->unlock();
        }

        Hardware::ProgramManager& shaderMng = Hardware::ProgramManager::getInstance();

        Hardware::ShaderPtr vertexShader = shaderMng.createShader("VertexShader", Hardware::ST_VERTEX);
        vertexShader->setSourceFromFile(GLSL_PATH"/default_VP.glsl");
        vertexShader->load();

        Hardware::ShaderPtr fragmentShader = shaderMng.createShader("FragmentShader", Hardware::ST_FRAGMENT);
        fragmentShader->setSourceFromFile(GLSL_PATH"/default_FP.glsl");
        fragmentShader->load();

        Hardware::ProgramPtr program = shaderMng.createProgram("Program");
        program->attach(vertexShader);
        program->attach(fragmentShader);
        program->link();

        Hardware::MaterialManager& materialMng = Hardware::MaterialManager::getInstance();
        Hardware::MaterialPtr material = materialMng.create("Material");

        material->getPasses()[0]->setProgram(program);

        material->getPasses()[0]->depthTest = true;
        material->getPasses()[0]->blendTest = true;
        material->getPasses()[0]->sourceFactor = Hardware::MB_ONE;
        material->getPasses()[0]->destinationFactor = Hardware::MB_ONE_MINUS_SRC_ALPHA;

        mesh1->setMaterial(material);
        mesh2->setMaterial(material);

        GL::Uniform u_m4Model("u_m4Model", program->getIdTMP());
        GL::Uniform u_m4View("u_m4View", program->getIdTMP());
        GL::Uniform u_m4Projection("u_m4Projection", program->getIdTMP());

        // Render
        {
            float dest = 1.f;
            while(!renderWindow->shouldBeClose())
            {
                // Test rotation
                static glm::mat4 orientation(1.f);
                orientation = glm::rotate(orientation, 0.01f, glm::vec3(0.f, 1.f, 0.f));
                orientation = glm::rotate(orientation, 0.01f, glm::vec3(1.f, 0.f, 0.f));

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
                                const glm::mat4 model = n->getFullTransform() * orientation;

                                for(const Render::SubMesh* subMesh : me.second->getSubMeshes())
                                {
                                    if(subMesh->material != nullptr)
                                    {
                                        const Hardware::MaterialPtr& mat = subMesh->material;
                                        for(Hardware::Pass* pass : mat->getPasses())
                                        {
                                            pass->lock();

                                            u_m4Projection = cam->getProjection();
                                            u_m4View = cam->getView();
                                            u_m4Model = model;

                                            GL::PixelOperation::enableDepthTest(pass->depthTest);
                                            GL::PixelOperation::enableDepthWrite(pass->depthWrite);
                                            GL::PixelOperation::setDepthFunc(Hardware::Pass::getType(pass->depthFunc));
                                            GL::PixelOperation::enableBlendTest(pass->blendTest);
                                            GL::PixelOperation::setBlendFunc(Hardware::Pass::getType(pass->sourceFactor), Hardware::Pass::getType(pass->destinationFactor));
                                            GL::PixelOperation::setColorMask(pass->colorMask[0], pass->colorMask[1], pass->colorMask[2], pass->colorMask[3]);

                                            const Hardware::VertexData* vertexData = subMesh->useSharedVertices ? me.second->sharedVertexData : subMesh->vertexData;
                                            vertexData->m_vertexDeclaration->lock();
                                            if(subMesh->indexData != nullptr)
                                            {
                                                const int offset = subMesh->indexData->m_indexStart * subMesh->indexData->m_indexBuffer->m_indexType;
                                                GL::DrawCall::drawElements(vertexData->getRenderType(), subMesh->indexData->m_indexCount, subMesh->indexData->m_indexBuffer->getType(), offset);
                                            }
                                            else
                                            {
                                                GL::DrawCall::drawArrays(vertexData->getRenderType(), 0, vertexData->m_vertexCount);
                                            }
                                        }
                                    }
                                }

                                if(n->getPosition().x > 1.f || n->getPosition().x < -1.f)
                                {
                                    dest = -dest;
                                }
                                n->setPosition(n->getPosition() + dest * glm::vec3(0.001f, 0.f, 0.f));
                            }
                        }
                    }
                }
                renderWindow->swapBuffers();
            }
        }

        node2->dettach(mesh2);
        sceneManager->destroyMesh(mesh2);
        sceneManager->getRootSceneNode()->removeAndDestroyChild(node2);
        node1->dettach(mesh1);
        sceneManager->destroyMesh(mesh1);
        sceneManager->getRootSceneNode()->removeAndDestroyChild(node1);
        renderWindow->removeViewport(viewport3);
        nodeCamera2->dettach(camera2);
        sceneManager->getRootSceneNode()->removeAndDestroyChild(nodeCamera2);
        sceneManager->destroyCamera(camera2);
        renderWindow->removeViewport(viewport2);
        renderWindow->removeViewport(viewport1);
        nodeCamera1->dettach(camera1);
        sceneManager->getRootSceneNode()->removeAndDestroyChild(nodeCamera1);
        sceneManager->destroyCamera(camera1);
        render.destroySceneManager(sceneManager);
        render.destroyRenderWindow(renderWindow);

        return EXIT_SUCCESS;
    }
    catch(exception _e)
    {
        cerr << _e.what() << endl;
        return EXIT_FAILURE;
    }
}
