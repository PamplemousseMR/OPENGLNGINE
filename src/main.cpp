#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Component/Mesh.hpp"
#include "GL/Buffer.hpp"
#include "GL/Shader.hpp"
#include "GL/Program.hpp"
#include "GL/Uniform.hpp"
#include "GL/Texture.hpp"
#include "Asset/Group.hpp"
#include "Asset/Material.hpp"
#include "Asset/Map.hpp"
#include "Asset/Object.hpp"
#include "Asset/OBJFile.hpp"
#include "Component/Component.hpp"

using namespace std;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void window_size_callback(GLFWwindow* window, int width, int height)
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
            cout << "[GLFW] cant't initialize glfw."<< endl;
            int i;
            cin >> i;
            return -1;
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
        window = glfwCreateWindow(800, 450, "3DNIGINE", NULL, NULL);
        if (window == NULL)
        {
            cout << "[GLFW] cant't create Window." << endl;
            glfwTerminate();
            int i;
            cin >> i;
            return -1;
        }

        glfwMakeContextCurrent(window);
        glewExperimental = true;

        if (glewInit() != GLEW_OK)
        {
            cout << "[GLEW] cant't initialize glew." << endl;
            int i;
            cin >> i;
            return -1;
        }

        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetKeyCallback(window, key_callback);
        glfwSetWindowSizeCallback(window, window_size_callback);

        GL::Shader standarShader(GL::SHADER_TYPE::VERTEX);
        standarShader.setSourceFromFile("GLSL/standarVertex.glsl");
        standarShader.compile();

        GL::Shader standarFragment(GL::SHADER_TYPE::FRAGMENT);
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
            char var = 0;
            cout << endl << "Probleme : appuyer sur une touche pour continuer..." << endl;
            cin >> var;
            return -1;
        }

        cout << "temps de chargement : " << file.getLoadTime() << endl;

        GL::Uniform standarProjection("u_projection", standarProgram.getId());
        GL::Uniform standarModel("u_model", standarProgram.getId());
        GL::Uniform standarView("u_view", standarProgram.getId());

        GL::Uniform standarAmbientTexture("u_ambientTexture", standarProgram.getId());
        GL::Uniform standarDiffuseTexture("u_diffuseTexture", standarProgram.getId());
        GL::Uniform standarSpecularTexture("u_specularTexture", standarProgram.getId());
        GL::Uniform standarNormalTexture("u_normalTexture", standarProgram.getId());

        GL::Uniform standarHasAmbientTexture("u_hasAmbientTexture", standarProgram.getId());
        GL::Uniform standarHasDiffuseTexture("u_hasDiffuseTexture", standarProgram.getId());
        GL::Uniform standarHasSpecularTexture("u_hasSpecularTexture", standarProgram.getId());
        GL::Uniform standarHasNormalTexture("u_hasNormalTexture", standarProgram.getId());

        GL::Uniform standarSpecularExponent("u_specularExponent", standarProgram.getId());
        GL::Uniform standarAmbient("u_ambient", standarProgram.getId());
        GL::Uniform standarDiffuse("u_diffuse", standarProgram.getId());
        GL::Uniform standarSpecular("u_specular", standarProgram.getId());

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        for (int a((int)file.getObjects().size() - 1); a >= 0; a--)
        {
            Assets::Object* ob = file.getObjects()[a];
            std::cout << *ob << std::endl;
            for (int b((int)ob->getGroups().size() - 1); b >= 0; b--)
            {
                Assets::Group* gp = ob->getGroups()[b];
                for (int c((int)gp->getMeshs().size() - 1); c >= 0; c--)
                {
                    Component::Mesh* me = gp->getMeshs()[c];
                    Assets::Material* material = gp->getMaterials()[c];
                }
            }
        }

        GL::Texture* ambient = NULL;
        GL::Texture* diffuse = NULL;
        GL::Texture* specular = NULL;
        GL::Texture* normal = NULL;

        bool hasAmbient = false;
        bool hasDiffuse = false;
        bool hasSpecular = false;
        bool hasNormal = false;

        Component::Component M("model");
        glm::mat4 P = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
        glm::mat4 V = glm::lookAt(glm::vec3(0, 0, 100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            standarProgram.toggle();

            standarModel = M.getPositionMatrix() * M.getRotationMatrix();
            standarView = V;
            standarProjection = P;

            M.setRotation(glm::vec3(0,M.getRotationData().y+0.01,0));

            for (int a((int)file.getObjects().size()-1) ; a >= 0 ; a--)
            {
                Assets::Object* ob = file.getObjects()[a];
                for (int b((int)ob->getGroups().size()-1); b >= 0; b--)
                {
                    Assets::Group* gp = ob->getGroups()[b];
                    for (int c((int)gp->getMeshs().size() - 1); c >= 0; c--)
                    {
                        Component::Mesh* me = gp->getMeshs()[c];
                        Assets::Material* material = gp->getMaterials()[c];

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
                            standarAmbientTexture = ambient->getLocation();
                            standarHasAmbientTexture = true;
                        }
                        else
                            standarHasAmbientTexture = false;

                        if (hasDiffuse)
                        {
                            diffuse->bind();
                            standarDiffuseTexture = diffuse->getLocation();
                            standarHasDiffuseTexture = true;
                        }
                        else
                            standarHasDiffuseTexture = false;

                        if (hasSpecular)
                        {
                            specular->bind();
                            standarSpecularTexture = specular->getLocation();
                            standarHasSpecularTexture = true;
                        }
                        else
                            standarHasSpecularTexture = false;

                        if (hasNormal)
                        {
                            normal->bind();
                            standarNormalTexture = normal->getLocation();
                            standarHasNormalTexture = true;
                        }
                        else
                            standarHasNormalTexture = false;

                        standarSpecularExponent = material->getSpecularExponent();
                        standarSpecular = material->getSpecular();
                        standarDiffuse = material->getDiffuse();
                        standarAmbient = material->getAmbient();

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

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        return 0;
    }
    catch (exception e)
    {
        cout << e.what() << endl;
        char var = 0;
        cout << endl << "Probleme : appuyer sur une touche pour continuer.." << endl;
        cin >> var;
        return -1;
    }
}
