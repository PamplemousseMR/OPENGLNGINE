#include "GL/Program.hpp"
#include "GL/Shader.hpp"
#include "GL/Texture.hpp"
#include "GL/Uniform.hpp"
#include "GL/FrameBuffer.hpp"
#include "GL/RenderBuffer.hpp"
#include "GL/Viewport.hpp"

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

        glfwWindowHint(GLFW_SAMPLES, 4);
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

        GL::Uniform u_m4ViewDeferred("u_m4View", quadBlinnPhonProgram.getId());
        GL::Uniform u_f3LightPos_Ws("u_f3LightPos_Ws", quadBlinnPhonProgram.getId());
        GL::Uniform u_f3LightCol("u_f3LightCol", quadBlinnPhonProgram.getId());

        /*========================================
         * =======================================
         *
         *      Init frame buffer
         *
         * =======================================
         * =======================================
         */

        GL::Texture renderPositionTexture(GL::Texture::TYPE_2D);
        renderPositionTexture.bind();
        renderPositionTexture.allocate(s_width, s_height, GL::Texture::INTERNALFORMAT_RGB32F, GL::Texture::FORMAT_RGB, GL::Texture::DATA_FLOAT);
        renderPositionTexture.setMagFilter(GL::Texture::FILTER_NEAREST);
        renderPositionTexture.setMinFilter(GL::Texture::FILTER_NEAREST);

        GL::Texture renderNormalTexture(GL::Texture::TYPE_2D);
        renderNormalTexture.bind();
        renderNormalTexture.allocate(s_width, s_height, GL::Texture::INTERNALFORMAT_RGBA32F, GL::Texture::FORMAT_RGBA, GL::Texture::DATA_FLOAT);
        renderNormalTexture.setMagFilter(GL::Texture::FILTER_NEAREST);
        renderNormalTexture.setMinFilter(GL::Texture::FILTER_NEAREST);

        GL::Texture renderAmbientTexture(GL::Texture::TYPE_2D);
        renderAmbientTexture.bind();
        renderAmbientTexture.allocate(s_width, s_height, GL::Texture::INTERNALFORMAT_RGBA, GL::Texture::FORMAT_RGBA, GL::Texture::DATA_UNSIGNED_BYTE);
        renderAmbientTexture.setMagFilter(GL::Texture::FILTER_NEAREST);
        renderAmbientTexture.setMinFilter(GL::Texture::FILTER_NEAREST);

        GL::Texture renderDiffuseTexture(GL::Texture::TYPE_2D);
        renderDiffuseTexture.bind();
        renderDiffuseTexture.allocate(s_width, s_height, GL::Texture::INTERNALFORMAT_RGBA, GL::Texture::FORMAT_RGBA, GL::Texture::DATA_UNSIGNED_BYTE);
        renderDiffuseTexture.setMagFilter(GL::Texture::FILTER_NEAREST);
        renderDiffuseTexture.setMinFilter(GL::Texture::FILTER_NEAREST);

        GL::Texture renderSpecularTexture(GL::Texture::TYPE_2D);
        renderSpecularTexture.bind();
        renderSpecularTexture.allocate(s_width, s_height, GL::Texture::INTERNALFORMAT_RGBA, GL::Texture::FORMAT_RGBA, GL::Texture::DATA_UNSIGNED_BYTE);
        renderSpecularTexture.setMagFilter(GL::Texture::FILTER_NEAREST);
        renderSpecularTexture.setMinFilter(GL::Texture::FILTER_NEAREST);

        GL::RenderBuffer renderDepthStencilBuffer;
        renderDepthStencilBuffer.bind();
        renderDepthStencilBuffer.allocate(s_width, s_height, GL::RenderBuffer::FORMAT_DEPTH_STENCIL);

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
            renderPositionTexture.allocate(_width, _height, GL::Texture::INTERNALFORMAT_RGB32F, GL::Texture::FORMAT_RGB, GL::Texture::DATA_FLOAT);
            renderNormalTexture.bind();
            renderNormalTexture.allocate(_width, _height, GL::Texture::INTERNALFORMAT_RGBA32F, GL::Texture::FORMAT_RGBA, GL::Texture::DATA_FLOAT);
            renderAmbientTexture.bind();
            renderAmbientTexture.allocate(_width, _height, GL::Texture::INTERNALFORMAT_RGBA, GL::Texture::FORMAT_RGBA, GL::Texture::DATA_UNSIGNED_BYTE);
            renderDiffuseTexture.bind();
            renderDiffuseTexture.allocate(_width, _height, GL::Texture::INTERNALFORMAT_RGBA, GL::Texture::FORMAT_RGBA, GL::Texture::DATA_UNSIGNED_BYTE);
            renderSpecularTexture.bind();
            renderSpecularTexture.allocate(_width, _height, GL::Texture::INTERNALFORMAT_RGBA, GL::Texture::FORMAT_RGBA, GL::Texture::DATA_UNSIGNED_BYTE);
            renderDepthStencilBuffer.bind();
            renderDepthStencilBuffer.allocate(_width, _height, GL::RenderBuffer::FORMAT_DEPTH_STENCIL);
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

        glm::mat4 P = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
        glm::mat4 V = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        /*========================================
         * =======================================
         *
         *      Init standar gl enable
         *
         * =======================================
         * =======================================
         */

        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilMask(0xFF);

        glDisable(GL_BLEND);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

        GL::Viewport::init(s_width, s_height);

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
            glEnable(GL_DEPTH_TEST);
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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
            glDisable(GL_DEPTH_TEST);
            glStencilFunc(GL_EQUAL, 1, 0xFF);
            glClear(GL_COLOR_BUFFER_BIT);

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
                u_f3LightCol = light.getAmbient();

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
