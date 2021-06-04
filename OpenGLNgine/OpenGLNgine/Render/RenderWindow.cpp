#include "OpenGLNgine/Render/RenderWindow.hpp"

#include "OpenGLNgine/Core/Exception.hpp"
#include "OpenGLNgine/Render/Render.hpp"

namespace Render
{

void RenderWindow::render() const
{
    this->makeCurrent();

    for(const auto& vp : m_viewports)
    {
        const auto& size = vp.second->getViewport();
        ::GL::Rasterizer::setViewport(static_cast< int >(size[0]*m_width), static_cast< int >(size[1]*m_height), static_cast< int >(size[2]*m_width), static_cast< int >(size[3]*m_height));
        ::GL::Rasterizer::enableScissorTest(true);
        ::GL::Rasterizer::setScissor(static_cast< int >(size[0]*m_width), static_cast< int >(size[1]*m_height), static_cast< int >(size[2]*m_width), static_cast< int >(size[3]*m_height));
        const auto& color = vp.second->getClearColor();

        ::GL::PixelOperation::setColorClearValue(color[0], color[1], color[2], color[3]);
        ::GL::DrawCall::clear(::GL::DC_COLOR_DEPTH);
        ::GL::Rasterizer::enableScissorTest(false);

        const Camera* const cam = vp.second->getCamera();

        const SceneManager* const sm = cam->getSceneManager();

        for(const auto& me : sm->getMeshes())
        {
            if(me.second->isAttached())
            {
                SceneNode* node = me.second->getParent();

                for(const SubMesh* subMesh : me.second->getSubMeshes())
                {
                    if(subMesh->m_material != nullptr)
                    {
                        const ::Hardware::MaterialPtr& mat = subMesh->m_material;
                        for(::Hardware::Pass* const pass : mat->getPasses())
                        {
                            const ::Hardware::ProgramPtr program = pass->getProgram();
                            if(program)
                            {
                                program->lock();

                                for(const std::pair< const ::Hardware::PROGRAM_PARAMETER, ::GL::Uniform >& parameter : pass->getAutoConstants())
                                {
                                    switch(parameter.first)
                                    {
                                    case ::Hardware::PP_MODELVIEWPROJ_MATRIX:
                                        parameter.second = cam->getProjection() * cam->getView() * node->getFullTransform();
                                        break;
                                    case ::Hardware::PP_MODELVIEW_MATRIX:
                                        parameter.second = cam->getView() * node->getFullTransform();
                                        break;
                                    case ::Hardware::PP_VIEW_MATRIX:
                                        parameter.second = cam->getView();
                                        break;
                                    case ::Hardware::PP_LIGHT_COUNT:
                                        parameter.second = static_cast< unsigned >(sm->getLights().size());
                                        break;
                                    case ::Hardware::PP_LIGHT_POSITION_WORLD_SPACE_ARRAY:
                                    {
                                        std::vector< ::glm::vec4 > lightPositionWorldSpaces;
                                        lightPositionWorldSpaces.reserve(sm->getLights().size());
                                        for(const std::pair< const std::string, Light* >& light : sm->getLights())
                                        {
                                            lightPositionWorldSpaces.push_back(light.second->getShaderPosition());
                                        }
                                        parameter.second = lightPositionWorldSpaces;
                                        break;
                                    }
                                    case ::Hardware::PP_LIGHT_POSITION_VIEW_SPACE_ARRAY:
                                    {
                                        std::vector< ::glm::vec4 > lightPositionViewSpaces;
                                        lightPositionViewSpaces.reserve(sm->getLights().size());
                                        for(const std::pair< const std::string, Light* >& light : sm->getLights())
                                        {
                                            lightPositionViewSpaces.push_back(cam->getView() * light.second->getShaderPosition());
                                        }
                                        parameter.second = lightPositionViewSpaces;
                                        break;
                                    }
                                    case ::Hardware::PP_LIGHT_DIFFUSE_COLOR_ARRAY:
                                    {
                                        std::vector< ::glm::vec3 > lightDiffuseColors;
                                        lightDiffuseColors.reserve(sm->getLights().size());
                                        for(const std::pair< const std::string, Light* >& light : sm->getLights())
                                        {
                                            lightDiffuseColors.push_back(light.second->getDiffuse());
                                        }
                                        parameter.second = lightDiffuseColors;
                                        break;
                                    }
                                    case ::Hardware::PP_LIGHT_SPECULAR_COLOR_ARRAY:
                                    {
                                        std::vector< ::glm::vec3 > lightSpecularColors;
                                        lightSpecularColors.reserve(sm->getLights().size());
                                        for(const std::pair< const std::string, Light* >& light : sm->getLights())
                                        {
                                            lightSpecularColors.push_back(light.second->getSpecular());
                                        }
                                        parameter.second = lightSpecularColors;
                                        break;
                                    }
                                    case ::Hardware::PP_MATERIAL_SHININESS:
                                        parameter.second = pass->m_shininess;
                                        break;
                                    case ::Hardware::PP_MATERIAL_AMBIENT:
                                        parameter.second = pass->m_ambient;
                                        break;
                                    case ::Hardware::PP_MATERIAL_HAS_TS_AMBIENT:
                                        parameter.second = pass->findTextureUnitStateBySemantic(::Hardware::TS_AMBIENT) ? 1.f : 0.f;
                                        break;
                                    case ::Hardware::PP_MATERIAL_DIFFUSE:
                                        parameter.second = pass->m_diffuse;
                                        break;
                                    case ::Hardware::PP_MATERIAL_HAS_TF_DIFFUSE:
                                        parameter.second = pass->findTextureUnitStateBySemantic(::Hardware::TS_DIFFUSE) ? 1.f : 0.f;
                                        break;
                                    case ::Hardware::PP_MATERIAL_SPECULAR:
                                        parameter.second = pass->m_specular;
                                        break;
                                    case ::Hardware::PP_MATERIAL_HAS_TS_SPECULAR:
                                        parameter.second = pass->findTextureUnitStateBySemantic(::Hardware::TS_SPECULAR) ? 1.f : 0.f;
                                        break;
                                    default:
                                        GLNGINE_EXCEPTION("Unhandle program parameter");
                                    }
                                }

                                for(const std::pair< const std::string, std::pair< ::GL::Uniform, ::Hardware::TEXTUREUNITSTATE_SEMANTIC > >& parameter : pass->getTextureConstants())
                                {
                                    parameter.second.first = static_cast< int >(parameter.second.second);
                                    ::Hardware::TextureUnitState* textureUnitState = pass->findTextureUnitStateBySemantic(parameter.second.second);
                                    if(textureUnitState)
                                    {
                                        const ::Hardware::TexturePtr texture = textureUnitState->getTexture();
                                        if(texture)
                                        {
                                            ::GL::Texture::setActiveTexture(textureUnitState->m_semantic);
                                            texture->lock();
                                            texture->setMagFilter(textureUnitState->magFilter);
                                            texture->setMinFilter(textureUnitState->minFilter);
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
    }
}

void RenderWindow::swapBuffers()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void RenderWindow::addListener(RenderWindowListener* const _listener)
{
    GLNGINE_ASSERT_IF(!_listener, "The listener mustn't be null");
    m_listeners.push_back(_listener);
}


SceneManager* RenderWindow::createSceneManager(const std::string& _name)
{
    if(m_sceneManagers.find(_name) != m_sceneManagers.end())
    {
        GLNGINE_EXCEPTION("A scene manager with the name '" + _name + "' already exists");
    }

    auto sm = new SceneManager(_name);
    m_sceneManagers.emplace(_name, sm);
    return sm;
}

void RenderWindow::destroySceneManager(const SceneManager* const _sceneManager)
{
    GLNGINE_ASSERT_IF(!_sceneManager, "The scene manager mustn't be null");

    SceneManagerList::const_iterator it = m_sceneManagers.find(_sceneManager->getName());
    if(it == m_sceneManagers.end())
    {
        GLNGINE_EXCEPTION("A scene manager with the name '" + _sceneManager->getName() + "' doesn't exists");
    }

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

    Viewport* viewport = new Viewport(this, _camera, _name);
    m_viewports.emplace(_name, viewport);
    return viewport;
}

void RenderWindow::removeViewport(const Viewport* const _viewport)
{
    GLNGINE_ASSERT_IF(!_viewport, "The viewport mustn't be null");

    ViewportList::const_iterator it = m_viewports.find(_viewport->getName());
    if(it == m_viewports.end())
    {
        GLNGINE_EXCEPTION("A viewport with the name '" + _viewport->getName() + "' doesn't exists");
    }

    m_viewports.erase(it);
    delete _viewport;
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

RenderWindow::RenderWindow(const std::string& _name, int _width, int _height) :
    IResource(_name),
    m_width(_width),
    m_height(_height)
{
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
    this->removeAllViewports();
    this->destroyAllSceneManagers();
    glfwDestroyWindow(m_window);
}

}
