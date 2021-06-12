#include <OpenGLNgine/Hardware/CompositorManager.hpp>
#include <OpenGLNgine/Hardware/CompositorPassClear.hpp>
#include <OpenGLNgine/Hardware/HardwareBufferManager.hpp>
#include <OpenGLNgine/Hardware/MaterialManager.hpp>
#include <OpenGLNgine/Hardware/ProgramManager.hpp>
#include <OpenGLNgine/Hardware/RenderTargetManager.hpp>
#include <OpenGLNgine/Hardware/TextureManager.hpp>
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
    ::Render::RenderWindow* const renderWindow = render.createRenderWindow("OpenGLViewer", width, height);
    renderWindow->addListener(new Listener);

    // Create a scene manager.
    ::Render::SceneManager* const sceneManager = renderWindow->createSceneManager("SeneManager");

    // Create a camera.
    ::Render::Camera* const camera = sceneManager->createCamera("Camera");
    camera->setProjection(45.f, static_cast<float>(width)/static_cast<float>(height), 0.1f, 1000.f);
    camera->setPosition({0.f, 0.f, 100.f});
    camera->lookAt({0.f, 0.f, 0.f});

    // Make the link between the camera, the scene manager and the viewport in the render window.
    ::Render::Viewport* const viewport = renderWindow->addViewport("Viewport", camera);
    viewport->setClearColor(0.8f, 0.8f, 0.8f, 0.f);

    // Create a light.
    ::Render::Light* const light = sceneManager->createLight("Light");
    light->setType(::Render::LT_DIRECTIONAL);
    light->setDirection(::glm::vec3(-1.f, 0.f, -1.f));

    // Create the Program.
    ::Hardware::ProgramManager& shaderMng = ::Hardware::ProgramManager::getInstance();

    ::Hardware::ShaderPtr vertexShader = shaderMng.createShader("VertexShader", ::Hardware::ST_VERTEX);
    vertexShader->setSourceFromFile(GLNGINE_GLSL_PATH"/OpenGLViewer_VP.glsl");
    vertexShader->load();

    ::Hardware::ShaderPtr fragmentShader = shaderMng.createShader("FragmentShader", ::Hardware::ST_FRAGMENT);
    fragmentShader->setSourceFromFile(GLNGINE_GLSL_PATH"/OpenGLViewer_FP.glsl");
    fragmentShader->load();

    // Create the material.
    ::Hardware::ProgramPtr program = shaderMng.createProgram("Program");
    program->attach(vertexShader);
    program->attach(fragmentShader);
    program->link();

    program->setNamedAutoConstant(::Hardware::PP_MODELVIEW_MATRIX, "u_m4MV");
    program->setNamedAutoConstant(::Hardware::PP_MODELVIEWPROJ_MATRIX, "u_m4MVP");

    program->setNamedAutoConstant(::Hardware::PP_LIGHT_COUNT, "u_uiLightCount");
    program->setNamedAutoConstant(::Hardware::PP_LIGHT_POSITION_VIEW_SPACE_ARRAY, "u_f4LightPos_Vs");
    program->setNamedAutoConstant(::Hardware::PP_LIGHT_DIFFUSE_COLOR_ARRAY, "u_f3LightDiffuse");
    program->setNamedAutoConstant(::Hardware::PP_LIGHT_SPECULAR_COLOR_ARRAY, "u_f3LightSpecular");

    program->setNamedAutoConstant(::Hardware::PP_MATERIAL_AMBIENT, "u_f3Ambient");
    program->setNamedAutoConstant(::Hardware::PP_MATERIAL_DIFFUSE, "u_f3Diffuse");
    program->setNamedAutoConstant(::Hardware::PP_MATERIAL_SPECULAR, "u_f3Specular");
    program->setNamedAutoConstant(::Hardware::PP_MATERIAL_SHININESS, "u_fShininess");

    program->setTextureConstant(::Hardware::TS_AMBIENT, "u_s2Ambient");
    program->setNamedAutoConstant(::Hardware::PP_MATERIAL_HAS_TS_AMBIENT, "u_fHasAmbient");
    program->setTextureConstant(::Hardware::TS_DIFFUSE, "u_s2Diffuse");
    program->setNamedAutoConstant(::Hardware::PP_MATERIAL_HAS_TF_DIFFUSE, "u_fHasDiffuse");
    program->setTextureConstant(::Hardware::TS_SPECULAR, "u_s2Specular");
    program->setNamedAutoConstant(::Hardware::PP_MATERIAL_HAS_TS_SPECULAR, "u_fHasSpecular");

    // Create the mesh.
    ::Render::Mesh* const mesh = sceneManager->createMesh("Mesh");
    mesh->load(MODEL_PATH"/Flamethrower/Flamethrower.obj");

    ::Hardware::MaterialManager& materialMng = ::Hardware::MaterialManager::getInstance();
    for(::Render::SubMesh* subMesh : mesh->getSubMeshes())
    {
        ::Hardware::MaterialPtr material = subMesh->m_material;
        if(!material)
        {
            material = materialMng.create("Material_" + subMesh->getName());
            subMesh->m_material = material;
        }

        material->getPasses()[0]->setProgram(program);
        material->getPasses()[0]->m_depthTest = true;

        for(::Hardware::TextureUnitState* textUnit : material->getPasses()[0]->getTextureUnitStates())
        {
            textUnit->m_minFilter = ::Hardware::TF_LINEAR_MIPMAP_LINEAR;
            textUnit->m_magFilter = ::Hardware::TF_LINEAR;

            const ::Hardware::TexturePtr texture = textUnit->getTexture();
            if(texture && !texture->isMipMapsGenerated())
            {
                texture->lock();
                texture->generateMipMaps();
            }
        }
    }

    // Create the node.
    ::Render::SceneNode* const node = sceneManager->getRootSceneNode()->createChild("Node");
    node->setPosition({0.0f, 0.f, 0.f});
    node->attach(mesh);

    // Create a compositor
    ::Hardware::RenderTargetManager& renderTargetManager = ::Hardware::RenderTargetManager::getInstance();
    const ::Hardware::RenderTargetPtr renderTarget = renderTargetManager.create("RenderTarget");
    renderTarget->pushTexture(::Hardware::TIF_DEPTH24);
    renderTarget->pushTexture(::Hardware::TIF_RGBA8);
    renderTarget->m_heightScale = 4.f;
    renderTarget->m_widthScale = 4.f;

    ::Hardware::CompositorManager& compositorManager = ::Hardware::CompositorManager::getInstance();
    const ::Hardware::CompositorPtr compositor = compositorManager.create("Compositor");

    {
        ::Hardware::CompositorTargetPass* cmpTargetPass = compositor->createCompositorTargetPass();
        cmpTargetPass->m_mode = ::Hardware::CM_NONE;
        cmpTargetPass->m_renderTarget = renderTarget;

        ::Hardware::CompositorPassClear* const clear = static_cast< ::Hardware::CompositorPassClear* >(cmpTargetPass->createCompositorPass(::Hardware::CT_CLEAR));
        clear->m_buffers = ::Hardware::CC_COLOR_DEPTH;
        clear->setClearColor(0.8f, 0.8f, 0.8f, 1.f);

        cmpTargetPass->createCompositorPass(::Hardware::CT_SCENE);
    }
    {
        ::Hardware::CompositorTargetPass* cmpTargetPass = compositor->createCompositorTargetPass();
        cmpTargetPass->m_mode = ::Hardware::CM_PREVIOUS;
        cmpTargetPass->m_mask = ::Hardware::CM_COLOR;
        cmpTargetPass->m_filter = ::Hardware::CF_LINEAR;
    }

    ::Render::CompositorChain* cmpChain = renderWindow->createCompositorChain(viewport, "CompositorChain");
    cmpChain->addCompositor(compositor);

    // Render loop.
    while(render.getRenderWindows().size() > 0)
    {
        const ::Render::Render::RenderWindowList& renderWindows = render.getRenderWindows();
        for(auto rwIt = renderWindows.begin(); rwIt != renderWindows.end();)
        {
            rwIt->second->makeCurrent();
            if(!rwIt->second->shouldBeClose())
            {
                rwIt->second->render();
                rwIt->second->swapBuffers();
                node->setOrientation(node->getOrientation() + ::glm::vec3(0.f, 0.5f, 0.f));

                ++rwIt;
            }
            else
            {
                rwIt = render.destroyRenderWindow(rwIt->second);
            }
        }
    }

    return EXIT_SUCCESS;
}
