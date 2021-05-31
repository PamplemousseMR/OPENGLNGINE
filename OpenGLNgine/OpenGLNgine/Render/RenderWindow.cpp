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
        ::GL::Rasterizer::setViewport(size[0], size[1], size[2], size[3]);
        ::GL::Rasterizer::enableScissorTest(true);
        ::GL::Rasterizer::setScissor(size[0], size[1], size[2], size[3]);

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
                            pass->lock();

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
                                case ::Hardware::PP_LIGHT_AMBIENT_COLOR_ARRAY:
                                {
                                    std::vector< ::glm::vec3 > lightAmbientColors;
                                    lightAmbientColors.reserve(sm->getLights().size());
                                    for(const std::pair< const std::string, Light* >& light : sm->getLights())
                                    {
                                        lightAmbientColors.push_back(light.second->getAmbient());
                                    }
                                    parameter.second = lightAmbientColors;
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
                                default:
                                    GLNGINE_EXCEPTION("Unhandle program parameter");
                                }
                            }

                            for(const std::pair< const std::string, std::pair< ::GL::Uniform, ::Hardware::TEXTUREUNITSTATE_SEMANTIC > >& parameter : pass->getTextureConstants())
                            {
                                parameter.second.first = static_cast< int >(parameter.second.second);
                            }

                            const ::Hardware::Pass::TextureUnitStateList& textureUnitStates = pass->getTextureUnitStates();
                            for(::Hardware::TextureUnitState* const textureUnitState : textureUnitStates)
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

                            ::GL::PixelOperation::enableDepthTest(pass->depthTest);
                            ::GL::PixelOperation::enableDepthWrite(pass->depthWrite);
                            ::GL::PixelOperation::setDepthFunc(::Hardware::Pass::getType(pass->depthFunc));
                            ::GL::PixelOperation::enableBlendTest(pass->blendTest);
                            ::GL::PixelOperation::setBlendFunc(::Hardware::Pass::getType(pass->sourceFactor), ::Hardware::Pass::getType(pass->destinationFactor));
                            ::GL::PixelOperation::setColorMask(pass->colorMask[0], pass->colorMask[1], pass->colorMask[2], pass->colorMask[3]);

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
                                    vertexData->m_vertexDeclaration->unlock();
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
    glfwDestroyWindow(m_window);
}

}
