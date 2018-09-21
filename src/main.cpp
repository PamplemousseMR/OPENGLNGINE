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

static int s_width = 800;
static int s_height = 450;

static void keyCallback(GLFWwindow* window, int key, int, int action, int)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void windowSizeCallback(GLFWwindow*, int _width, int _height)
{
    s_width = _width;
    s_height = _height;
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

        GL::Shader blinnPhongVertex(GL::Shader::TYPE_VERTEX);
        blinnPhongVertex.setSourceFromFile("GLSL/blinnPhongVertex.glsl");
        blinnPhongVertex.compile();

        GL::Shader blinnPhongFragment(GL::Shader::TYPE_FRAGMENT);
        blinnPhongFragment.setSourceFromFile("GLSL/blinnPhongFragment.glsl");
        blinnPhongFragment.compile();

        GL::Program standarProgram;
        standarProgram.attach(blinnPhongVertex);
        standarProgram.attach(blinnPhongFragment);
        standarProgram.link();

        GL::Uniform u_m4Projection("u_m4Projection", standarProgram.getId());
        GL::Uniform u_m4Model("u_m4Model", standarProgram.getId());
        GL::Uniform u_m4View("u_m4View", standarProgram.getId());

        GL::Uniform u_f3LightPos_Ws("u_f3LightPos_Ws", standarProgram.getId());
        GL::Uniform u_f3LightCol("u_f3LightCol", standarProgram.getId());

        GL::Uniform u_tAmbient("u_tAmbient", standarProgram.getId());
        GL::Uniform u_tDiffuse("u_tDiffuse", standarProgram.getId());
        GL::Uniform u_tSpecular("u_tSpecular", standarProgram.getId());
        GL::Uniform u_tNormal("u_tNormal", standarProgram.getId());

        GL::Uniform u_bAmbient("u_bAmbient", standarProgram.getId());
        GL::Uniform u_bDiffuse("u_bDiffuse", standarProgram.getId());
        GL::Uniform u_bSpecular("u_bSpecular", standarProgram.getId());
        GL::Uniform u_bNormal("u_bNormal", standarProgram.getId());

        GL::Uniform u_fSpecularExponent("u_fSpecularExponent", standarProgram.getId());
        GL::Uniform u_f3AmbientCol("u_f3AmbientCol", standarProgram.getId());
        GL::Uniform u_f3DiffuseCol("u_f3DiffuseCol", standarProgram.getId());
        GL::Uniform u_f3SpecularCol("u_f3SpecularCol", standarProgram.getId());

        /*========================================
         * =======================================
         *
         *      Init quad shader
         *
         * =======================================
         * =======================================
         */

        GL::Shader quadVertex(GL::Shader::TYPE_VERTEX);
        quadVertex.setSourceFromFile("GLSL/quadVertex.glsl");
        quadVertex.compile();

        GL::Shader quadFragment(GL::Shader::TYPE_FRAGMENT);
        quadFragment.setSourceFromFile("GLSL/quadFragment.glsl");
        quadFragment.compile();

        GL::Program quadProgram;
        quadProgram.attach(quadVertex);
        quadProgram.attach(quadFragment);
        quadProgram.link();

        GL::Uniform u_tTexture("u_tTexture", quadProgram.getId());

        /*========================================
         * =======================================
         *
         *      Init frame buffer
         *
         * =======================================
         * =======================================
         */

        GL::Texture renderTexture(GL::Texture::TYPE_2D);
        renderTexture.bind();
        renderTexture.allocate(s_width, s_height, GL::Texture::FORMAT_RGBA);
        renderTexture.setMagFilter(GL::Texture::FILTER_NEAREST);
        renderTexture.setMinFilter(GL::Texture::FILTER_NEAREST);

        GL::RenderBuffer renderDepthBuffer;
        renderDepthBuffer.bind();
        renderDepthBuffer.allocate(s_width, s_height, GL::RenderBuffer::FORMAT_DEPTH);

        GL::FrameBuffer frameBuffer;
        frameBuffer.bind();
        frameBuffer.attachColorTexture2D(renderTexture, 0);
        frameBuffer.attachDepthBuffer(renderDepthBuffer);
        frameBuffer.checkStatus();
        frameBuffer.unbind();

        /*========================================
         * =======================================
         *
         *      Init component
         *
         * =======================================
         * =======================================
         */

        Assets::OBJFile files;
        files.load("obj/Flamethrower/Flamethrower.obj");
        Assets::OBJFile filess(files);
        Assets::OBJFile filesss;
        filesss = filess;
        Assets::OBJFile file(std::move(filesss));

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
        GL::Viewport viewport;

        /*========================================
         * =======================================
         *
         *      Init standar gl enable
         *
         * =======================================
         * =======================================
         */

        glEnable(GL_MULTISAMPLE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.75f, 0.75f, 0.75f, 1.0f);

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
            viewport.setViewport(s_width,s_height);
            renderTexture.bind();
            renderTexture.allocate(s_width, s_height, GL::Texture::FORMAT_RGBA);
            renderDepthBuffer.bind();
            renderDepthBuffer.allocate(s_width, s_height, GL::RenderBuffer::FORMAT_DEPTH);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            frameBuffer.attachDrawBuffers();

            standarProgram.bind();
            {
                u_m4View = V;
                u_m4Projection = P;
                u_f3LightPos_Ws = light.getPositionData();
                u_f3LightCol = light.getAmbient();

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

                            Assets::Map* bumpMap = material->getBumpmap();
                            if (bumpMap)
                            {
                                GL::Texture* normal = bumpMap->getTexture();
                                normal->bind();
                                u_tNormal = normal->getLocation();
                                u_bNormal = true;
                            }
                            else
                            {
                                u_bNormal = false;
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
            standarProgram.unbind();

            /*========================================
             * =======================================
             *
             *      Second pass
             *
             * =======================================
             * =======================================
             */
            frameBuffer.unbind();
            viewport.setViewport(s_width,s_height);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            quadProgram.bind();
            {
                renderTexture.bind();
                u_tTexture = renderTexture.getLocation();

                quad.bind();
                quad.draw();
                quad.unbind();

                renderTexture.unbind();
            }
            quadProgram.unbind();

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
