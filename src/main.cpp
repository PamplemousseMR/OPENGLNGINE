#include "GL/Program.hpp"
#include "GL/Shader.hpp"
#include "GL/Texture.hpp"
#include "GL/Uniform.hpp"
#include "GL/FrameBuffer.hpp"
#include "GL/RenderBuffer.hpp"
#include "GL/Viewport.hpp"
#include "GL/PixelOperation.hpp"

#include "Assets/Group.hpp"
#include "Assets/Map.hpp"
#include "Assets/Material.hpp"
#include "Assets/Object.hpp"
#include "Assets/OBJFile.hpp"

#include "Component/Component.hpp"
#include "Component/Mesh.hpp"
#include "Component/Light.hpp"
#include "Component/Quad.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

static const int s_width = 800;
static const int s_height = 450;
static const int s_sample = 4;

static void keyCallback(GLFWwindow* window, int key, int, int action, int)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void windowSizeCallback(GLFWwindow*, int _width, int _height)
{
    GL::Viewport::setViewport(_width,_height);
}

void exitHandler()
{
    glfwTerminate();
}

int main()
{
    try
    {
        if(std::atexit(exitHandler) != 0)
        {
            cerr << endl << "Probleme : appuyer sur une touche pour continuer.." << endl;
            return EXIT_FAILURE;
        }

        /*========================================
         * =======================================
         *
         *      Init glfw
         *
         * =======================================
         * =======================================
         */

        int nmonitors;
        const GLFWvidmode* mode;
        GLFWmonitor **monitors;
        GLFWwindow* window;

        if (!glfwInit())
        {
            cerr << "[GLFW] Can't initialize glfw."<< endl;
            return EXIT_FAILURE;
        }

        glfwWindowHint(GLFW_SAMPLES, s_sample);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        monitors = glfwGetMonitors(&nmonitors);
        mode = glfwGetVideoMode(*monitors);
        //window = glfwCreateWindow(mode->width, mode->height, "3DNIGINE", *monitors, NULL);
        window = glfwCreateWindow(s_width, s_height, "OPENGLNGINE", nullptr, nullptr);
        if (window == nullptr)
        {
            cerr << "[GLFW] Can't create Window." << endl;
            return EXIT_FAILURE;
        }

        glfwMakeContextCurrent(window);
        glewExperimental = true;

        if (glewInit() != GLEW_OK)
        {
            cerr << "[GLEW] Can't initialize glew." << endl;
            return EXIT_FAILURE;
        }

        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetKeyCallback(window, keyCallback);
        glfwSetWindowSizeCallback(window, windowSizeCallback);

        /*========================================
         * =======================================
         *
         *      Init standar shader
         *
         * =======================================
         * =======================================
         */

        GL::Shader deferredShadingVertex(GL::Shader::TYPE_VERTEX);
        deferredShadingVertex.setSourceFromFile("GLSL/deferredShadingVertex.glsl");
        deferredShadingVertex.compile();

        GL::Shader deferredShadingFragment(GL::Shader::TYPE_FRAGMENT);
        deferredShadingFragment.setSourceFromFile("GLSL/deferredShadingFragment.glsl");
        deferredShadingFragment.compile();

        GL::Program deferredShadingProgram;
        deferredShadingProgram.attach(deferredShadingVertex);
        deferredShadingProgram.attach(deferredShadingFragment);
        deferredShadingProgram.link();

        GL::Uniform u_m4Model("u_m4Model", deferredShadingProgram.getId());
        GL::Uniform u_m4View("u_m4View", deferredShadingProgram.getId());
        GL::Uniform u_m4Projection("u_m4Projection", deferredShadingProgram.getId());

        GL::Uniform u_tAmbient("u_tAmbient", deferredShadingProgram.getId());
        GL::Uniform u_tDiffuse("u_tDiffuse", deferredShadingProgram.getId());
        GL::Uniform u_tSpecular("u_tSpecular", deferredShadingProgram.getId());

        GL::Uniform u_bAmbient("u_bAmbient", deferredShadingProgram.getId());
        GL::Uniform u_bDiffuse("u_bDiffuse", deferredShadingProgram.getId());
        GL::Uniform u_bSpecular("u_bSpecular", deferredShadingProgram.getId());

        GL::Uniform u_fSpecularExponent("u_fSpecularExponent", deferredShadingProgram.getId());
        GL::Uniform u_f3AmbientCol("u_f3AmbientCol", deferredShadingProgram.getId());
        GL::Uniform u_f3DiffuseCol("u_f3DiffuseCol", deferredShadingProgram.getId());
        GL::Uniform u_f3SpecularCol("u_f3SpecularCol", deferredShadingProgram.getId());

        /*========================================
         * =======================================
         *
         *      Init quad shader
         *
         * =======================================
         * =======================================
         */

        GL::Shader quadBlinnPhongVertex(GL::Shader::TYPE_VERTEX);
        quadBlinnPhongVertex.setSourceFromFile("GLSL/quadBlinnPhongVertex.glsl");
        quadBlinnPhongVertex.compile();

        GL::Shader quadBlinnPhongFragment(GL::Shader::TYPE_FRAGMENT);
        quadBlinnPhongFragment.setSourceFromFile("GLSL/quadBlinnPhongFragment.glsl");
        quadBlinnPhongFragment.compile();

        GL::Program quadBlinnPhonProgram;
        quadBlinnPhonProgram.attach(quadBlinnPhongVertex);
        quadBlinnPhonProgram.attach(quadBlinnPhongFragment);
        quadBlinnPhonProgram.link();

        GL::Uniform u_tPositionCor_Vs("u_tPositionCor_Vs", quadBlinnPhonProgram.getId());
        GL::Uniform u_tOutNormalDir_Vs("u_tNormalDir_Vs", quadBlinnPhonProgram.getId());
        GL::Uniform u_tOutAmbientCol_Vs("u_tAmbientCol_Vs", quadBlinnPhonProgram.getId());
        GL::Uniform u_tOutDiffuseCol_Vs("u_tDiffuseCol_Vs", quadBlinnPhonProgram.getId());
        GL::Uniform u_tOutSpecularCol_Vs("u_tSpecularCol_Vs", quadBlinnPhonProgram.getId());
        GL::Uniform u_tSpecularExp("u_tSpecularExp", quadBlinnPhonProgram.getId());

        GL::Uniform u_m4ViewDeferred("u_m4View", quadBlinnPhonProgram.getId());

        GL::Uniform u_f3LightPos_Ws("u_f3LightPos_Ws", quadBlinnPhonProgram.getId());
        GL::Uniform u_f3LightAmbientCol("u_f3LightAmbientCol", quadBlinnPhonProgram.getId());
        GL::Uniform u_f3LightDiffuseCol("u_f3LightDiffuseCol", quadBlinnPhonProgram.getId());
        GL::Uniform u_f3LightSpecularCol("u_f3LightSpecularCol", quadBlinnPhonProgram.getId());

        GL::Uniform u_sample("u_sample", quadBlinnPhonProgram.getId());

        /*========================================
         * =======================================
         *
         *      Init normal shader
         *
         * =======================================
         * =======================================
         */

        GL::Shader normalVertex(GL::Shader::TYPE_VERTEX);
        normalVertex.setSourceFromFile("GLSL/normalVertex.glsl");
        normalVertex.compile();

        GL::Shader normalFragment(GL::Shader::TYPE_FRAGMENT);
        normalFragment.setSourceFromFile("GLSL/normalFragment.glsl");
        normalFragment.compile();

        GL::Shader normalGeometry(GL::Shader::TYPE_GEOMETRY);
        normalGeometry.setSourceFromFile("GLSL/normalGeometry.glsl");
        normalGeometry.compile();

        GL::Program normalProgram;
        normalProgram.attach(normalVertex);
        normalProgram.attach(normalGeometry);
        normalProgram.attach(normalFragment);
        normalProgram.link();

        GL::Uniform u_m4ModelNormal("u_m4Model", normalProgram.getId());
        GL::Uniform u_m4ViewNormal("u_m4View", normalProgram.getId());
        GL::Uniform u_m4ProjectionNormal("u_m4Projection", normalProgram.getId());

        /*========================================
         * =======================================
         *
         *      Init frame buffer
         *
         * =======================================
         * =======================================
         */

        GL::Texture renderPositionTexture(GL::Texture::TYPE_2DMULTISAMPLE);
        renderPositionTexture.bind();
        renderPositionTexture.allocateMultisample(s_width, s_height, GL::Texture::INTERNALFORMAT_RGB32F, GL::Texture::FORMAT_RGB, s_sample);

        GL::Texture renderNormalTexture(GL::Texture::TYPE_2DMULTISAMPLE);
        renderNormalTexture.bind();
        renderNormalTexture.allocateMultisample(s_width, s_height, GL::Texture::INTERNALFORMAT_RGBA32F, GL::Texture::FORMAT_RGBA, s_sample);

        GL::Texture renderAmbientTexture(GL::Texture::TYPE_2DMULTISAMPLE);
        renderAmbientTexture.bind();
        renderAmbientTexture.allocateMultisample(s_width, s_height, GL::Texture::INTERNALFORMAT_RGB, GL::Texture::FORMAT_RGB, s_sample);

        GL::Texture renderDiffuseTexture(GL::Texture::TYPE_2DMULTISAMPLE);
        renderDiffuseTexture.bind();
        renderDiffuseTexture.allocateMultisample(s_width, s_height, GL::Texture::INTERNALFORMAT_RGB, GL::Texture::FORMAT_RGB, s_sample);

        GL::Texture renderSpecularTexture(GL::Texture::TYPE_2DMULTISAMPLE);
        renderSpecularTexture.bind();
        renderSpecularTexture.allocateMultisample(s_width, s_height, GL::Texture::INTERNALFORMAT_RGB, GL::Texture::FORMAT_RGB, s_sample);

        GL::RenderBuffer renderDepthStencilBuffer;
        renderDepthStencilBuffer.bind();
        renderDepthStencilBuffer.allocateMultisample(s_width, s_height, GL::RenderBuffer::FORMAT_DEPTH_STENCIL, s_sample);

        GL::FrameBuffer frameBuffer;
        frameBuffer.bind();
        frameBuffer.attachColorTexture(renderPositionTexture, 0);
        frameBuffer.attachColorTexture(renderNormalTexture, 1);
        frameBuffer.attachColorTexture(renderAmbientTexture, 2);
        frameBuffer.attachColorTexture(renderDiffuseTexture, 3);
        frameBuffer.attachColorTexture(renderSpecularTexture, 4);
        frameBuffer.attachDepthStencilBuffer(renderDepthStencilBuffer);
        frameBuffer.checkStatus();
        frameBuffer.unbind();

        /*========================================
         * =======================================
         *
         *      Add realocation to the viewport listeners
         *
         * =======================================
         * =======================================
         */

        GL::Viewport::addListener([&](int _width, int _height){
            renderPositionTexture.bind();
            renderPositionTexture.allocateMultisample(_width, _height, GL::Texture::INTERNALFORMAT_RGB32F, GL::Texture::FORMAT_RGB, s_sample);
            renderNormalTexture.bind();
            renderNormalTexture.allocateMultisample(_width, _height, GL::Texture::INTERNALFORMAT_RGBA32F, GL::Texture::FORMAT_RGBA, s_sample);
            renderAmbientTexture.bind();
            renderAmbientTexture.allocateMultisample(_width, _height, GL::Texture::INTERNALFORMAT_RGB, GL::Texture::FORMAT_RGB, s_sample);
            renderDiffuseTexture.bind();
            renderDiffuseTexture.allocateMultisample(_width, _height, GL::Texture::INTERNALFORMAT_RGB, GL::Texture::FORMAT_RGB, s_sample);
            renderSpecularTexture.bind();
            renderSpecularTexture.allocateMultisample(_width, _height, GL::Texture::INTERNALFORMAT_RGB, GL::Texture::FORMAT_RGB, s_sample);
            renderDepthStencilBuffer.bind();
            renderDepthStencilBuffer.allocateMultisample(_width, _height, GL::RenderBuffer::FORMAT_DEPTH_STENCIL, s_sample);
        });

        /*========================================
         * =======================================
         *
         *      Init component
         *
         * =======================================
         * =======================================
         */

        Assets::OBJFile file;
        file.load("obj/Flamethrower/Flamethrower.obj");

        Component::Quad quad("QuadRenderer");

        Component::Light light("light");
        light.setPosition(glm::vec3(0, 0, 100));

        /*========================================
         * =======================================
         *
         *      Init camera
         *
         * =======================================
         * =======================================
         */

        glm::mat4 P = glm::perspective(glm::radians(45.0f), (s_width+.0f) / (s_height+.0f), 0.1f, 1000.0f);
        GL::Viewport::addListener([&] (int _width, int _height)
        {
            P = glm::perspective(glm::radians(45.0f), (_width+.0f) / (_height+.0f), 0.1f, 1000.0f);
        });
        glm::mat4 V = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        /*========================================
         * =======================================
         *
         *      Init standar gl enable
         *
         * =======================================
         * =======================================
         */

        GL::Viewport::setViewport(s_width, s_height);

        while (!glfwWindowShouldClose(window))
        {
            /*========================================
             * =======================================
             *
             *      First pass
             *
             * =======================================
             * =======================================
             */

            frameBuffer.bind();
            GL::PixelOperation::enableDepthTest(true);
            GL::PixelOperation::enableDepthWrite(true);
            GL::PixelOperation::setDepthFunc(GL::PixelOperation::DEPTH_LESS);

            GL::PixelOperation::enableStencilTest(true);
            GL::PixelOperation::setStencilMask(0xFF);
            GL::PixelOperation::setStencilFunc(GL::PixelOperation::STENCIL_ALWAYS, 1, 0xFF);
            GL::PixelOperation::setStencilOperation(GL::PixelOperation::STENCIL_KEEP, GL::PixelOperation::STENCIL_KEEP, GL::PixelOperation::STENCIL_REPLACE);

            GL::PixelOperation::enableBlendTest(false);

            GL::PixelOperation::setColorClearValue(0.0f, 0.0f, 0.0f, 1.0f);
            GL::PixelOperation::clear(GL::PixelOperation::CLEAR_ALL);

            frameBuffer.attachDrawBuffers();

            deferredShadingProgram.bind();
            {
                u_m4View = V;
                u_m4Projection = P;

                for (size_t a = file.getObjects().size()-1 ; a != std::numeric_limits<size_t>::max() ; --a)
                {
                    Assets::Object* ob = file.getObjects()[a];
                    for (size_t b = ob->getGroups().size()-1; b != std::numeric_limits<size_t>::max() ; --b)
                    {
                        Assets::Group* gp = ob->getGroups()[b];
                        for (size_t c = gp->getMeshs().size() - 1; c != std::numeric_limits<size_t>::max() ; --c)
                        {
                            Component::Mesh* me = gp->getMeshs()[c];

                            u_m4Model = me->getPositionMatrix() * me->getRotationMatrix();
                            me->setRotation(glm::vec3(0, me->getRotationData().y+0.01f, 0));

                            Assets::Material* material = me->getMaterial();

                            Assets::Map* kaMap = material->getKamap();
                            if (kaMap)
                            {
                                GL::Texture* ambient = kaMap->getTexture();
                                ambient->bind();
                                u_tAmbient = ambient->getLocation();
                                u_bAmbient = true;
                            }
                            else
                            {
                                u_bAmbient = false;
                            }

                            Assets::Map* kdMap = material->getKdmap();
                            if (kdMap)
                            {
                                GL::Texture* diffuse = kdMap->getTexture();
                                diffuse->bind();
                                u_tDiffuse = diffuse->getLocation();
                                u_bDiffuse = true;
                            }
                            else
                            {
                                u_bDiffuse = false;
                            }

                            Assets::Map* ksMap = material->getKsmap();
                            if (ksMap)
                            {
                                GL::Texture* specular = ksMap->getTexture();
                                specular->bind();
                                u_tSpecular = specular->getLocation();
                                u_bSpecular = true;
                            }
                            else
                            {
                                u_bSpecular = false;
                            }

                            u_fSpecularExponent = material->getSpecularExponent();
                            u_f3SpecularCol = material->getSpecular();
                            u_f3DiffuseCol = material->getDiffuse();
                            u_f3AmbientCol = material->getAmbient();

                            me->bind();
                            me->draw();
                            me->unbind();

                            if(material->getKamap() != nullptr)
                            {
                                material->getKamap()->getTexture()->unbind();
                            }
                            if(material->getKdmap() != nullptr)
                            {
                                material->getKdmap()->getTexture()->unbind();
                            }
                            if(material->getKsmap() != nullptr)
                            {
                                material->getKsmap()->getTexture()->unbind();
                            }
                            if(material->getBumpmap() != nullptr)
                            {
                                material->getBumpmap()->getTexture()->unbind();
                            }
                        }
                    }
                }
            }
            deferredShadingProgram.unbind();
            frameBuffer.unbind();

            /*========================================
             * =======================================
             *
             *      Copy stencil buffer to default frame buffer
             *
             * =======================================
             * =======================================
             */

            frameBuffer.bindRead();
            GL::FrameBuffer::bindDrawDefault();
            GL::FrameBuffer::blit(GL::Viewport::getWidth(), GL::Viewport::getHeight(), GL::FrameBuffer::MASK_STENCIL);
            GL::FrameBuffer::blit(GL::Viewport::getWidth(), GL::Viewport::getHeight(), GL::FrameBuffer::MASK_DEPTH);
            GL::FrameBuffer::unbindDrawDefault();
            frameBuffer.unbindRead();

            /*========================================
             * =======================================
             *
             *      Second pass
             *
             * =======================================
             * =======================================
             */

            GL::FrameBuffer::bindDefault();

            GL::PixelOperation::enableDepthTest(false);
            GL::PixelOperation::enableDepthWrite(false);

            GL::PixelOperation::enableStencilTest(true);
            GL::PixelOperation::setStencilMask(0xFF);
            GL::PixelOperation::setStencilFunc(GL::PixelOperation::STENCIL_EQUAL, 1, 0xFF);
            GL::PixelOperation::setStencilOperation(GL::PixelOperation::STENCIL_KEEP, GL::PixelOperation::STENCIL_KEEP, GL::PixelOperation::STENCIL_KEEP);

            GL::PixelOperation::enableBlendTest(false);

            GL::PixelOperation::setColorClearValue(0.75f, 0.75f, 0.75f, 1.0f);
            GL::PixelOperation::clear(GL::PixelOperation::CLEAR_COLOR);

            quadBlinnPhonProgram.bind();
            {
                renderPositionTexture.bind();
                u_tPositionCor_Vs = renderPositionTexture.getLocation();
                renderNormalTexture.bind();
                u_tOutNormalDir_Vs = renderNormalTexture.getLocation();
                renderAmbientTexture.bind();
                u_tOutAmbientCol_Vs = renderAmbientTexture.getLocation();
                renderDiffuseTexture.bind();
                u_tOutDiffuseCol_Vs = renderDiffuseTexture.getLocation();
                renderSpecularTexture.bind();
                u_tOutSpecularCol_Vs = renderSpecularTexture.getLocation();

                u_m4ViewDeferred = V;

                u_f3LightPos_Ws = light.getPositionData();
                u_f3LightAmbientCol = light.getAmbient();
                u_f3LightDiffuseCol = light.getDiffuse();
                u_f3LightSpecularCol = light.getSpecular();

                u_sample = s_sample;

                quad.bind();
                quad.draw();
                quad.unbind();

                renderPositionTexture.unbind();
                renderNormalTexture.unbind();
                renderAmbientTexture.unbind();
                renderDiffuseTexture.unbind();
                renderSpecularTexture.unbind();
            }
            quadBlinnPhonProgram.unbind();
            GL::FrameBuffer::unbindDefault();

            /*========================================
             * =======================================
             *
             *      Normal pass
             *
             * =======================================
             * =======================================
             */

            GL::FrameBuffer::bindDefault();
            GL::PixelOperation::enableDepthTest(true);
            GL::PixelOperation::enableDepthWrite(true);
            GL::PixelOperation::setDepthFunc(GL::PixelOperation::DEPTH_LESS);

            GL::PixelOperation::enableStencilTest(false);

            GL::PixelOperation::enableBlendTest(false);

            normalProgram.bind();
            {
                u_m4ViewNormal = V;
                u_m4ProjectionNormal = P;

                for (size_t a = file.getObjects().size()-1 ; a != std::numeric_limits<size_t>::max() ; --a)
                {
                    Assets::Object* ob = file.getObjects()[a];
                    for (size_t b = ob->getGroups().size()-1; b != std::numeric_limits<size_t>::max() ; --b)
                    {
                        Assets::Group* gp = ob->getGroups()[b];
                        for (size_t c = gp->getMeshs().size() - 1; c != std::numeric_limits<size_t>::max() ; --c)
                        {
                            Component::Mesh* me = gp->getMeshs()[c];

                            u_m4ModelNormal = me->getPositionMatrix() * me->getRotationMatrix();

                            me->bind();
                            me->draw();
                            me->unbind();
                        }
                    }
                }
            }
            normalProgram.unbind();
            GL::FrameBuffer::unbindDefault();

            /*========================================
             * =======================================
             *
             *      End
             *
             * =======================================
             * =======================================
             */

            GLenum err;
            while ((err = glGetError()) != GL_NO_ERROR)
            {
                    cerr << "[OpenGL] error: " << err << endl;
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        return EXIT_SUCCESS;
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
        cerr << endl << "Probleme : appuyer sur une touche pour continuer.." << endl;
        return EXIT_FAILURE;
    }
}
