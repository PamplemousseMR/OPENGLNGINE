#include "OpenGLNgine/Render/RenderWindow.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Hardware/CompositorPassClear.hpp"
#include "OpenGLNgine/Render/Render.hpp"

namespace Render
{

void RenderWindow::renderScene(const SceneNode* const _node, const Camera* const _cam) const
{
    const SceneManager* const sm = _cam->getSceneManager();

    for(const auto& node : _node->getChildren())
    {
        this->renderScene(node.second, _cam);
    }

    const SceneNode::MeshList& component = _node->getAttachedMeshes();

    for(const auto& me : component)
    {
        for(const SubMesh* const subMesh : me.second->getSubMeshes())
        {
            if(subMesh->m_material != nullptr)
            {
                const ::Hardware::MaterialPtr& mat = subMesh->m_material;
                for(const ::Hardware::Pass* const pass : mat->getPasses())
                {
                    const ::Hardware::ProgramPtr program = pass->getProgram();
                    if(program)
                    {
                        program->lock();

                        for(const std::pair< const ::Hardware::PROGRAM_PARAMETER, std::shared_ptr< ::GL::Uniform > >& parameter : pass->getAutoConstants())
                        {
                            switch(parameter.first)
                            {
                            case ::Hardware::PP_MODELVIEWPROJ_MATRIX:
                                *parameter.second = _cam->getProjection() * _cam->getView() * _node->getFullTransform();
                                break;
                            case ::Hardware::PP_MODELVIEW_MATRIX:
                                *parameter.second = _cam->getView() * _node->getFullTransform();
                                break;
                            case ::Hardware::PP_VIEW_MATRIX:
                                *parameter.second = _cam->getView();
                                break;
                            case ::Hardware::PP_LIGHT_COUNT:
                                *parameter.second = static_cast< unsigned >(sm->getLights().size());
                                break;
                            case ::Hardware::PP_LIGHT_POSITION_WORLD_SPACE_ARRAY:
                            {
                                const SceneManager::LightList& lights = sm->getLights();
                                if(lights.size() > 0)
                                {
                                    std::vector< ::glm::vec4 > lightPositionWorldSpaces;
                                    lightPositionWorldSpaces.reserve(lights.size());
                                    for(const std::pair< const std::string, Light* >& light : lights)
                                    {
                                        lightPositionWorldSpaces.push_back(light.second->getShaderPosition());
                                    }
                                    *parameter.second = lightPositionWorldSpaces;
                                }
                                break;
                            }
                            case ::Hardware::PP_LIGHT_POSITION_VIEW_SPACE_ARRAY:
                            {
                                const SceneManager::LightList& lights = sm->getLights();
                                if(lights.size() > 0)
                                {
                                    std::vector< ::glm::vec4 > lightPositionViewSpaces;
                                    lightPositionViewSpaces.reserve(lights.size());
                                    for(const std::pair< const std::string, Light* >& light : lights)
                                    {
                                        lightPositionViewSpaces.push_back(_cam->getView() * light.second->getShaderPosition());
                                    }
                                    *parameter.second = lightPositionViewSpaces;
                                }
                                break;
                            }
                            case ::Hardware::PP_LIGHT_DIFFUSE_COLOR_ARRAY:
                            {
                                const SceneManager::LightList& lights = sm->getLights();
                                if(lights.size() > 0)
                                {
                                    std::vector< ::glm::vec3 > lightDiffuseColors;
                                    lightDiffuseColors.reserve(lights.size());
                                    for(const std::pair< const std::string, Light* >& light : lights)
                                    {
                                        lightDiffuseColors.push_back(light.second->getDiffuse());
                                    }
                                    *parameter.second = lightDiffuseColors;
                                }
                                break;
                            }
                            case ::Hardware::PP_LIGHT_SPECULAR_COLOR_ARRAY:
                            {
                                const SceneManager::LightList& lights = sm->getLights();
                                if(lights.size() > 0)
                                {
                                    std::vector< ::glm::vec3 > lightSpecularColors;
                                    lightSpecularColors.reserve(sm->getLights().size());
                                    for(const std::pair< const std::string, Light* >& light : sm->getLights())
                                    {
                                        lightSpecularColors.push_back(light.second->getSpecular());
                                    }
                                    *parameter.second = lightSpecularColors;
                                }
                                break;
                            }
                            case ::Hardware::PP_MATERIAL_SHININESS:
                                *parameter.second = pass->m_shininess;
                                break;
                            case ::Hardware::PP_MATERIAL_AMBIENT:
                                *parameter.second = pass->m_ambient;
                                break;
                            case ::Hardware::PP_MATERIAL_HAS_TS_AMBIENT:
                                *parameter.second = pass->findTextureUnitStateBySemantic(::Hardware::TS_AMBIENT) ? 1.f : 0.f;
                                break;
                            case ::Hardware::PP_MATERIAL_DIFFUSE:
                                *parameter.second = pass->m_diffuse;
                                break;
                            case ::Hardware::PP_MATERIAL_HAS_TF_DIFFUSE:
                                *parameter.second = pass->findTextureUnitStateBySemantic(::Hardware::TS_DIFFUSE) ? 1.f : 0.f;
                                break;
                            case ::Hardware::PP_MATERIAL_SPECULAR:
                                *parameter.second = pass->m_specular;
                                break;
                            case ::Hardware::PP_MATERIAL_HAS_TS_SPECULAR:
                                *parameter.second = pass->findTextureUnitStateBySemantic(::Hardware::TS_SPECULAR) ? 1.f : 0.f;
                                break;
                            default:
                                GLNGINE_EXCEPTION("Unhandle program parameter");
                            }
                        }

                        for(const std::pair< const ::Hardware::TEXTUREUNITSTATE_SEMANTIC, std::shared_ptr< ::GL::Uniform > >& parameter : pass->getTextureConstants())
                        {
                            *parameter.second = static_cast< int >(parameter.first);
                            const ::Hardware::TextureUnitState* const textureUnitState = pass->findTextureUnitStateBySemantic(parameter.first);
                            if(textureUnitState)
                            {
                                const ::Hardware::TexturePtr texture = textureUnitState->getTexture();
                                if(texture)
                                {
                                    ::GL::Texture::setActiveTexture(textureUnitState->m_semantic);
                                    texture->lock();
                                    texture->setMagFilter(textureUnitState->m_magFilter);
                                    texture->setMinFilter(textureUnitState->m_minFilter);
                                    texture->setUWrap(textureUnitState->m_uWrap);
                                    texture->setVWrap(textureUnitState->m_vWrap);
                                }
                            }
                        }

                        ::GL::PixelOperation::enableDepthTest(pass->m_depthTest);
                        ::GL::PixelOperation::enableDepthWrite(pass->m_depthWrite);
                        ::GL::PixelOperation::setDepthFunc(::Hardware::Pass::getType(pass->m_depthFunc));
                        ::GL::PixelOperation::enableBlendTest(pass->m_blendTest);
                        ::GL::PixelOperation::setBlendFunc(::Hardware::Pass::getType(pass->m_sourceFactor), ::Hardware::Pass::getType(pass->m_destinationFactor));
                        ::GL::PixelOperation::setColorMask(pass->m_colorMask[0], pass->m_colorMask[1], pass->m_colorMask[2], pass->m_colorMask[3]);

                        ::GL::Rasterizer::enableCulling(pass->m_culling != ::Hardware::PC_NONE);
                        if(pass->m_culling != ::Hardware::PC_NONE)
                        {
                            ::GL::Rasterizer::setCullFace(::Hardware::Pass::getType(pass->m_culling));
                        }

                        const ::Hardware::VertexData* const vertexData = subMesh->m_vertexData;
                        if(vertexData != nullptr)
                        {
                            const ::Hardware::IndexData* const indexData = subMesh->m_indexData;
                            if(subMesh->isDirty())
                            {
                                vertexData->m_vertexDeclaration->lock();
                                for(const auto& binding : vertexData->m_vertexBufferBinding->getBufferBindings())
                                {
                                    const ::Hardware::HardwareVertexBufferPtr buffer = binding.second;
                                    buffer->lock();

                                    int stride = 0;

                                    const ::Hardware::VertexDeclaration::VertexElementList& elements = vertexData->m_vertexDeclaration->getElements();
                                    for(const ::Hardware::VertexElement* const element : elements)
                                    {
                                        if(element->m_source == binding.first)
                                        {
                                            stride += element->getTypeCount();
                                        }
                                    }

                                    for(const ::Hardware::VertexElement* const element : elements)
                                    {
                                        if(element->m_source == binding.first)
                                        {
                                            const int offset = element->m_offsetInBytes + vertexData->m_vertexStart * buffer->m_vertexType;
                                            ::GL::DataBuffer::setAttrib(element->m_semantic, element->getTypeCount(), element->getType(), false, buffer->m_vertexType*stride, offset);
                                            ::GL::DataBuffer::setLocation(element->m_semantic);
                                        }
                                    }
                                }
                                if(indexData != nullptr && indexData->m_indexBuffer != nullptr)
                                {
                                    indexData->m_indexBuffer->lock();
                                }
                                subMesh->_notifyDirty();
                            }

                            vertexData->m_vertexDeclaration->lock();
                            if(indexData != nullptr && indexData->m_indexBuffer != nullptr)
                            {
                                const int offset = indexData->m_indexStart * indexData->m_indexBuffer->m_indexType;
                                ::GL::DrawCall::drawElements(vertexData->getRenderType(), indexData->m_indexCount, indexData->m_indexBuffer->getType(), offset);
                            }
                            else
                            {
                                ::GL::DrawCall::drawArrays(vertexData->getRenderType(), 0, vertexData->m_vertexCount);
                            }
                        }
                    }
                }
            }
        }
    }
}

void RenderWindow::render() const
{
    for(const auto& vp : m_viewports)
    {
        const auto& size = vp.second->getViewport();
        const int viewportOriginX = static_cast< int >(size[0]*m_width);
        const int viewportOriginY = static_cast< int >(size[1]*m_height);
        const int viewportWidth = static_cast< int >(size[2]*m_width);
        const int viewportHeight = static_cast< int >(size[3]*m_height);

        const CompositorChainList::const_iterator compIt = m_compositorChains.find(vp.second);
        if(compIt != m_compositorChains.end() && compIt->second->getCompositors().size() > 0)
        {
            ::Hardware::RenderTargetPtr previousRenderTarget = nullptr;
            for(const ::Hardware::CompositorPtr& compositor : compIt->second->getCompositors())
            {
                for(const ::Hardware::CompositorTargetPass* const targetPass : compositor->getCompositorTargetPasses())
                {
                    int renderTargetOriginX = 0;
                    int renderTargetOriginY = 0;
                    int renderTargetWidth = 0;
                    int renderTargetHeight = 0;

                    const ::Hardware::RenderTargetPtr renderTarget = targetPass->m_renderTarget;
                    if(renderTarget)
                    {
                        renderTargetWidth = static_cast< int >(viewportWidth*renderTarget->m_widthScale);
                        renderTargetHeight = static_cast< int >(viewportHeight*renderTarget->m_heightScale);

                        renderTarget->lockDraw();
                        if(renderTarget->isDirty())
                        {
                            renderTarget->allocate(renderTargetWidth, renderTargetHeight);
                            renderTarget->attach();
                            renderTarget->check();
                            renderTarget->_notifyDirty();
                        }
                        ::GL::Rasterizer::enableScissorTest(false);
                    }
                    else
                    {
                        renderTargetOriginX = viewportOriginX;
                        renderTargetOriginY =  viewportOriginY;
                        renderTargetWidth = viewportWidth;
                        renderTargetHeight = viewportHeight;
                        ::GL::FrameBuffer::bindDrawDefault();
                        ::GL::Rasterizer::enableScissorTest(true);
                        ::GL::Rasterizer::setScissor(renderTargetOriginX, renderTargetOriginY, viewportWidth, viewportHeight);
                    }
                    ::GL::Rasterizer::setViewport(renderTargetOriginX, renderTargetOriginY, renderTargetWidth, renderTargetHeight);

                    switch(targetPass->m_mode)
                    {
                    case ::Hardware::COMPOSITORTARGETPASS_MODE::CM_NONE:
                        break;
                    case ::Hardware::COMPOSITORTARGETPASS_MODE::CM_PREVIOUS:
                    {
                        int readTargetOriginX = 0;
                        int readTargetOriginY = 0;
                        int readTargetWidth = 0;
                        int readTargetHeight = 0;
                        unsigned readSample = 0;
                        if(previousRenderTarget == nullptr)
                        {
                            readTargetOriginX = viewportOriginX;
                            readTargetOriginY =  viewportOriginY;
                            readTargetWidth = viewportWidth;
                            readTargetHeight = viewportHeight;
                            readSample = m_sample;
                            ::GL::FrameBuffer::bindReadDefault();
                        }
                        else
                        {
                            readTargetWidth = static_cast< int >(viewportWidth*previousRenderTarget->m_widthScale);
                            readTargetHeight = static_cast< int >(viewportHeight*previousRenderTarget->m_heightScale);
                            readSample = previousRenderTarget->m_sample;
                            previousRenderTarget->lockRead();
                        }

                        unsigned writeSample = 0;
                        if(renderTarget == nullptr)
                        {
                            writeSample = m_sample;
                            ::GL::FrameBuffer::bindDrawDefault();
                        }
                        else
                        {
                            writeSample = renderTarget->m_sample;
                            renderTarget->lockDraw();
                        }

                        if(readSample == 0 && writeSample > 0)
                        {
                            GLNGINE_EXCEPTION("Unable to blit framebuffer to a multisampled framebuffer");
                        }
                        else if(readSample > 0 && (readTargetWidth != renderTargetWidth || readTargetHeight != renderTargetHeight))
                        {
                            GLNGINE_EXCEPTION("Unable to blit multisampled framebuffer to a different size framebuffer");
                        }
                        else if(readSample > 0 && readSample != writeSample)
                        {
                            GLNGINE_EXCEPTION("Unable to blit multisampled framebuffer to a different sample size framebuffer");
                        }
                        else
                        {
                            ::GL::FrameBuffer::blit(readTargetOriginX, readTargetOriginY, readTargetWidth+readTargetOriginX, readTargetHeight+readTargetOriginY,
                                                    renderTargetOriginX, renderTargetOriginY, renderTargetWidth+renderTargetOriginX, renderTargetHeight+renderTargetOriginY,
                                                    ::Hardware::CompositorTargetPass::getType(targetPass->m_mask), ::Hardware::CompositorTargetPass::getType(targetPass->m_filter));
                        }
                        break;
                    }
                    default:
                        GLNGINE_EXCEPTION("Unhandle pass mode");
                    }

                    const ::Hardware::CompositorTargetPass::CompositorPassList& passes = targetPass->getCompositorPasses();
                    for(const ::Hardware::CompositorPass* const pass : passes)
                    {
                        switch(pass->m_type){
                        case ::Hardware::COMPOSITORPASS_TYPE::CT_CLEAR:
                        {
                            const ::Hardware::CompositorPassClear* const cmpClear = static_cast< const ::Hardware::CompositorPassClear* >(pass);
                            const auto& color = cmpClear->getClearColor();
                            ::GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);
                            ::GL::PixelOperation::setDepthClearValue(cmpClear->m_depthClearValue);
                            ::GL::DrawCall::clear(::Hardware::CompositorPassClear::getType(cmpClear->m_buffers));
                            break;
                        }
                        case ::Hardware::COMPOSITORPASS_TYPE::CT_SCENE:
                        {
                            const Camera* const cam = vp.second->getCamera();
                            const SceneManager* const sm = cam->getSceneManager();
                            const SceneNode* const node = sm->getRootSceneNode();
                            this->renderScene(node, cam);
                            break;
                        }
                        default:
                            GLNGINE_EXCEPTION("Unhandle compositor pass type");
                        }
                    }

                    previousRenderTarget = renderTarget;
                }
            }
        }
        else
        {
            ::GL::FrameBuffer::bindDrawDefault();
            ::GL::Rasterizer::enableScissorTest(true);
            ::GL::Rasterizer::setScissor(viewportOriginX, viewportOriginY, viewportWidth, viewportHeight);
            ::GL::Rasterizer::setViewport(viewportOriginX, viewportOriginY, viewportWidth, viewportHeight);

            const auto& color = vp.second->getClearColor();
            ::GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);
            ::GL::PixelOperation::setDepthClearValue(vp.second->m_depthClearValue);
            ::GL::DrawCall::clear(::GL::DC_ALL);
            ::GL::Rasterizer::enableScissorTest(false);

            const Camera* const cam = vp.second->getCamera();
            const SceneManager* const sm = cam->getSceneManager();
            const SceneNode* const node = sm->getRootSceneNode();
            this->renderScene(node, cam);
        }
    }
}

void RenderWindow::swapBuffers()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void RenderWindow::addListener(RenderWindowListener* const _listener)
{
    GLNGINE_ASSERT_IF(!_listener, "The listener shall not be null");
    m_listeners.push_back(_listener);
}


SceneManager* RenderWindow::createSceneManager(const std::string& _name)
{
    if(m_sceneManagers.find(_name) != m_sceneManagers.end())
    {
        GLNGINE_EXCEPTION("A scene manager with the name '" + _name + "' already exists");
    }

    auto sm = new SceneManager(this, _name);
    m_sceneManagers.emplace(_name, sm);
    return sm;
}

void RenderWindow::destroySceneManager(const SceneManager* const _sceneManager)
{
    GLNGINE_ASSERT_IF(!_sceneManager, "The scene manager shall not be null");

    SceneManagerList::const_iterator it = m_sceneManagers.find(_sceneManager->getName());
    if(it == m_sceneManagers.end())
    {
        GLNGINE_EXCEPTION("A scene manager with the name '" + _sceneManager->getName() + "' doesn't exists");
    }
    GLNGINE_ASSERT_IF(_sceneManager->m_renderWindow != this, "The scene manager does not came from this render window");

    m_sceneManagers.erase(it);
    delete _sceneManager;
}

void RenderWindow::destroyAllSceneManagers()
{
    SceneManagerList::iterator it = m_sceneManagers.begin();
    while(it != m_sceneManagers.end())
    {
        this->destroySceneManager(it->second);
        it = m_sceneManagers.begin();
    }
}

Viewport* RenderWindow::addViewport(const std::string& _name, Camera* const _camera)
{
    if(m_viewports.find(_name) != m_viewports.end())
    {
        GLNGINE_EXCEPTION("A viewport with the name '" + _name + "' already exists");
    }
    GLNGINE_ASSERT_IF(_camera->getSceneManager()->m_renderWindow != this, "The camera does not came from this render window");

    Viewport* const viewport = new Viewport(this, _camera, _name);
    m_viewports.emplace(_name, viewport);
    return viewport;
}

void RenderWindow::removeViewport(const Viewport* const _viewport)
{
    GLNGINE_ASSERT_IF(!_viewport, "The viewport shall not be null");

    ViewportList::const_iterator it = m_viewports.find(_viewport->getName());
    if(it == m_viewports.end())
    {
        GLNGINE_EXCEPTION("A viewport with the name '" + _viewport->getName() + "' doesn't exists");
    }
    GLNGINE_ASSERT_IF(_viewport->m_renderWindow != this, "The viewport does not came from this render window");

    CompositorChainList::const_iterator cit = m_compositorChains.find(it->second);
    if(cit != m_compositorChains.end())
    {
        this->destroyCompositorChain(cit->second);
    }

    m_viewports.erase(it);
    delete _viewport;
}

void RenderWindow::removeViewports(const Camera* const _camera)
{
    GLNGINE_ASSERT_IF(!_camera, "The camera shall not be null");

    ViewportList::iterator it = m_viewports.begin();
    while(it != m_viewports.end())
    {
        if(it->second->getCamera() == _camera)
        {
            delete it->second;
            it = m_viewports.erase(it);

            CompositorChainList::const_iterator cit = m_compositorChains.find(it->second);
            if(cit != m_compositorChains.end())
            {
                this->destroyCompositorChain(cit->second);
            }
        }
        else
        {
            ++it;
        }
    }
}

void RenderWindow::removeAllViewports()
{
    ViewportList::iterator it = m_viewports.begin();
    while(it != m_viewports.end())
    {
        this->removeViewport(it->second);
        it = m_viewports.begin();
    }
}

Viewport* RenderWindow::getViewport(const std::string& _name) const
{
    if(m_viewports.find(_name) == m_viewports.end())
    {
        GLNGINE_EXCEPTION("A viewport with the name '" + _name + "' doesn't exists");
    }
    return m_viewports.at(_name);
}

CompositorChain* RenderWindow::createCompositorChain(Viewport* const _viewport, const std::string& _name)
{
    if(m_compositorChains.find(_viewport) != m_compositorChains.end())
    {
        GLNGINE_EXCEPTION("A compositor chain is already attached to the viewport '" + _viewport->getName() + "'");
    }
    GLNGINE_ASSERT_IF(_viewport->m_renderWindow != this, "The viewport does not came from this render window");

    auto sm = new CompositorChain(_viewport, _name);
    m_compositorChains.emplace(_viewport, sm);
    return sm;
}

void RenderWindow::destroyCompositorChain(const CompositorChain* const _compositorChain)
{
    GLNGINE_ASSERT_IF(!_compositorChain, "The scene manager shall not be null");

    const CompositorChainList::const_iterator it = m_compositorChains.find(_compositorChain->getViewport());
    if(it == m_compositorChains.end())
    {
        GLNGINE_EXCEPTION("A compositor chain with the name '" + _compositorChain->getName() + "' doesn't exists");
    }
    GLNGINE_ASSERT_IF(_compositorChain->getViewport()->m_renderWindow != this, "The compositor chain does not came from this render window");

    m_compositorChains.erase(it);
    delete _compositorChain;
}

void RenderWindow::destroyAllCompositorChains()
{
    CompositorChainList::iterator it = m_compositorChains.begin();
    while(it != m_compositorChains.end())
    {
        this->destroyCompositorChain(it->second);
        it = m_compositorChains.begin();
    }
}

RenderWindow::Initializer::Initializer()
{
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
        GLNGINE_EXCEPTION("Can't initialize the render");
    }
}

void sizeCallback(GLFWwindow* _window, int _width, int _height)
{
    Render& render = Render::getInstance();

    for(const auto& rw : render.getRenderWindows())
    {
        if(rw.second->m_window == _window)
        {
            rw.second->m_height = _height;
            rw.second->m_width = _width;
            for(const auto& compositorChain : rw.second->getCompositorChain())
            {
                for(const ::Hardware::CompositorPtr& compositor : compositorChain.second->getCompositors())
                {
                    for(const ::Hardware::CompositorTargetPass* const targetPass : compositor->getCompositorTargetPasses())
                    {
                        const ::Hardware::RenderTargetPtr renderTarget = targetPass->m_renderTarget;
                        if(renderTarget)
                        {
                            renderTarget->setDirty();
                        }
                    }
                }
            }
            for(RenderWindowListener* const listener : rw.second->m_listeners)
            {
                listener->sizeModified(rw.second, _width, _height);
            }
            break;
        }
    }
}

void keyCallback(GLFWwindow* _window, int _key, int, int _action, int)
{
    Render& render = Render::getInstance();

    for(const auto& rw : render.getRenderWindows())
    {
        if(rw.second->m_window == _window)
        {
            RenderWindowListener::RENDERWINDOWLISTENER_KEY key = static_cast< RenderWindowListener::RENDERWINDOWLISTENER_KEY >(_key);
            for(RenderWindowListener* const listener : rw.second->m_listeners)
            {
                if(_action == GLFW_PRESS)
                {
                    listener->keyPressed(rw.second, key);
                }
                else if(_action == GLFW_REPEAT)
                {
                    listener->keyRepeated(rw.second, key);
                }
                else if(_action == GLFW_RELEASE)
                {
                    listener->keyRepeated(rw.second, key);
                }
                else
                {
                    GLNGINE_ASSERT("Unknown action");
                }
            }
            break;
        }
    }
}

RenderWindow::RenderWindow(const std::string& _name, int _width, int _height, int _sample) :
    IResource(_name),
    m_width(_width),
    m_height(_height),
    m_sample(_sample)
{
    glfwWindowHint(GLFW_SAMPLES, _sample);
    m_window = glfwCreateWindow(_width, _height, m_name.c_str(), m_monitor, nullptr);
    if(!m_window)
    {
        GLNGINE_EXCEPTION("Can't create the render window");
    }

    this->makeCurrent();
    const static Initializer s_INITIALIZER;

    glfwSetWindowSizeCallback(m_window, sizeCallback);
    glfwSetKeyCallback(m_window, keyCallback);
}

RenderWindow::~RenderWindow()
{
    this->destroyAllCompositorChains();
    this->removeAllViewports();
    this->destroyAllSceneManagers();
    glfwDestroyWindow(m_window);
}

}
