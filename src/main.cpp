#include "GL/Buffer.hpp"
#include "GL/Program.hpp"
#include "GL/Shader.hpp"
#include "GL/Texture.hpp"
#include "GL/Uniform.hpp"

#include "Assets/Group.hpp"
#include "Assets/Map.hpp"
#include "Assets/Material.hpp"
#include "Assets/Object.hpp"
#include "Assets/OBJFile.hpp"

#include "Component/Component.hpp"
#include "Component/Mesh.hpp"
#include "Component/Light.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

static void key_callback(GLFWwindow* window, int key, int, int action, int)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void window_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0,0,width,height);
}

int main()
{
    try
    {
        int nmonitors;
        const GLFWvidmode* mode;
        GLFWmonitor **monitors;
        GLFWwindow* window;

        if (!glfwInit())
        {
            cerr << "[GLFW] Can't initialize glfw."<< endl;
            return -1;
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        monitors = glfwGetMonitors(&nmonitors);
        mode = glfwGetVideoMode(*monitors);
        //window = glfwCreateWindow(mode->width, mode->height, "3DNIGINE", *monitors, NULL);
        window = glfwCreateWindow(800, 450, "3DNIGINE", nullptr, nullptr);
        if (window == nullptr)
        {
            cerr << "[GLFW] Can't create Window." << endl;
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);
        glewExperimental = true;

        if (glewInit() != GLEW_OK)
        {
            cerr << "[GLEW] Can't initialize glew." << endl;
            return -1;
        }

        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetKeyCallback(window, key_callback);
        glfwSetWindowSizeCallback(window, window_size_callback);

        GL::Shader standarShader(GL::Shader::VERTEX);
        standarShader.setSourceFromFile("GLSL/standarVertex.glsl");
        standarShader.compile();

        GL::Shader standarFragment(GL::Shader::FRAGMENT);
        standarFragment.setSourceFromFile("GLSL/standarFragment.glsl");
        standarFragment.compile();

        GL::Program standarProgram;
        standarProgram.attach(standarShader);
        standarProgram.attach(standarFragment);
        standarProgram.link();

        Assets::OBJFile file;
        try
        {
            file.load("obj/Flamethrower/Flamethrower.obj");
        }
        catch (exception e)
        {
            cerr << e.what() << endl;
            return -1;
        }

        cout << file << endl;

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

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.75f, 0.75f, 0.75f, 1.0f);

        GL::Texture* ambient = nullptr;
        GL::Texture* diffuse = nullptr;
        GL::Texture* specular = nullptr;
        GL::Texture* normal = nullptr;

        bool hasAmbient = false;
        bool hasDiffuse = false;
        bool hasSpecular = false;
        bool hasNormal = false;

        glm::mat4 P = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
        glm::mat4 V = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        Component::Light light("light");
        light.setPosition(glm::vec3(0, 0, 100));

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            standarProgram.toggle();

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

                        Assets::Map* map = material->getKamap();
                        if (map && map->getTexture())
                        {
                            ambient = map->getTexture();
                            hasAmbient = true;
                        }
                        else
                            hasAmbient = false;

                        map = material->getKdmap();
                        if (map && map->getTexture())
                        {
                            diffuse = map->getTexture();
                            hasDiffuse = true;
                        }
                        else
                            hasDiffuse = false;

                        map = material->getKsmap();
                        if (map && map->getTexture())
                        {
                            specular = map->getTexture();
                            hasSpecular = true;
                        }
                        else
                            hasSpecular = false;

                        map = material->getBumpmap();
                        if (map && map->getTexture())
                        {
                            normal = map->getTexture();
                            hasNormal = true;
                        }
                        else
                            hasNormal = false;

                        if (hasAmbient)
                        {
                            ambient->bind();
                            u_tAmbient = ambient->getLocation();
                            u_bAmbient = true;
                        }
                        else
                            u_bAmbient = false;

                        if (hasDiffuse)
                        {
                            diffuse->bind();
                            u_tDiffuse = diffuse->getLocation();
                            u_bDiffuse = true;
                        }
                        else
                            u_bDiffuse = false;

                        if (hasSpecular)
                        {
                            specular->bind();
                            u_tSpecular = specular->getLocation();
                            u_bSpecular = true;
                        }
                        else
                            u_bSpecular = false;

                        if (hasNormal)
                        {
                            normal->bind();
                            u_tNormal = normal->getLocation();
                            u_bNormal = true;
                        }
                        else
                            u_bNormal = false;

                        u_fSpecularExponent = material->getSpecularExponent();
                        u_f3SpecularCol = material->getSpecular();
                        u_f3DiffuseCol = material->getDiffuse();
                        u_f3AmbientCol = material->getAmbient();

                        me->bind();
                        me->draw();
                        me->unbind();

                        if (hasSpecular)
                            specular->unbind();
                        if(hasDiffuse)
                            diffuse->unbind();
                        if(hasAmbient)
                            ambient->unbind();
                    }
                }
            }

            standarProgram.toggle();

            GLenum err;
            while ((err = glGetError()) != GL_NO_ERROR)
            {
                    cerr << "OpenGL error: " << err << endl;
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        return 0;
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
        cerr << endl << "Probleme : appuyer sur une touche pour continuer.." << endl;
        return -1;
    }
}
