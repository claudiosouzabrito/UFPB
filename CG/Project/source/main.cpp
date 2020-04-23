#include "include.hpp"
#include "functions.hpp"
#include "renderer.hpp"
#include "model.hpp"
#include "loader.hpp"
#include "player.hpp"
#include <stdlib.h>
using namespace std;

//ESSAS SAO AS CORES QUE CORRESPONDEM AOS VERTICES
float timeValue;
float greenValue;
float redValue;
float blueValue;

int main()
{
    // função pra instanciar a janela do GLFW
    glfwInit();
    glwindowhint();

    //objeto janela
    GLFWwindow *window = glfwCreateWindow(800, 600, "janelinha da alegria", NULL, NULL);

    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // função glad para carregar a função do openGL

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /* -------------------------------------------
        CLOUD NE */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //Shader ourShader("./source/texture.vs", "./source/texture.fs");

    Loader loader = Loader();
    std::vector<float> vertices = {-0.5f, 0.5f, -0.5f,
                                   -0.5f, -0.5f, -0.5f,
                                   0.5f, -0.5f, -0.5f,
                                   0.5f, 0.5f, -0.5f,

                                   -0.5f, 0.5f, 0.5f,
                                   -0.5f, -0.5f, 0.5f,
                                   0.5f, -0.5f, 0.5f,
                                   0.5f, 0.5f, 0.5f,

                                   0.5f, 0.5f, -0.5f,
                                   0.5f, -0.5f, -0.5f,
                                   0.5f, -0.5f, 0.5f,
                                   0.5f, 0.5f, 0.5f,

                                   -0.5f, 0.5f, -0.5f,
                                   -0.5f, -0.5f, -0.5f,
                                   -0.5f, -0.5f, 0.5f,
                                   -0.5f, 0.5f, 0.5f,

                                   -0.5f, 0.5f, 0.5f,
                                   -0.5f, 0.5f, -0.5f,
                                   0.5f, 0.5f, -0.5f,
                                   0.5f, 0.5f, 0.5f,

                                   -0.5f, -0.5f, 0.5f,
                                   -0.5f, -0.5f, -0.5f,
                                   0.5f, -0.5f, -0.5f,
                                   0.5f, -0.5f, 0.5f};

    std::vector<float> normalVec = {0.0f, 0.0f, -1.0f,
                                    0.0f, 0.0f, -1.0f,
                                    0.0f, 0.0f, -1.0f,
                                    0.0f, 0.0f, -1.0f,

                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,

                                    1.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,

                                    -1.0f, 0.0f, 0.0f,
                                    -1.0f, 0.0f, 0.0f,
                                    -1.0f, 0.0f, 0.0f,
                                    -1.0f, 0.0f, 0.0f,

                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f,

                                    0.0f, -1.0f, 0.0f,
                                    0.0f, -1.0f, 0.0f,
                                    0.0f, -1.0f, 0.0f,
                                    0.0f, -1.0f, 0.0f};

    std::vector<unsigned int> indices = {0, 1, 3,
                                         3, 1, 2,
                                         4, 5, 7,
                                         7, 5, 6,
                                         8, 9, 11,
                                         11, 9, 10,
                                         12, 13, 15,
                                         15, 13, 14,
                                         16, 17, 19,
                                         19, 17, 18,
                                         20, 21, 23,
                                         23, 21, 22};
    std::vector<float> textureCoords = {
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0,
        0, 0,
        0, 1,
        1, 1,
        1, 0};

    int numeroArvores = 200;
    Renderer renderer = Renderer();
    //textura arvore
    unsigned int texture2 = loader.loadTexture("./Textura/tree.jpg");

    std::vector<Model> modelos;
    for (int i = 0; i < numeroArvores; i++)
    {
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        Model modelo = loader.loadObj("./Modelos/tree.obj");

        modelo.setPosition(glm::vec3(static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 800 - 400, 0.0, static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 800 - 400));
        modelo.setScale(glm::vec3(10.0f, 10.0f, 10.0f));
        modelo.setTexture(texture2);
        
        modelos.push_back(modelo);
    }

    //pedras

    int nPedras = 20; 
    unsigned int texturaPedra = loader.loadTexture("./Textura/rock.jpg");

     for (int i = 0; i < nPedras; i++)
    {
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        Model modelo = loader.loadObj("./Modelos/rocha.obj");

        modelo.setPosition(glm::vec3(static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 800 - 400, 0.0, static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 800 - 400));
        modelo.setScale(glm::vec3(10.0f, 10.0f, 10.0f));
        modelo.setTexture(texturaPedra);
        
        modelos.push_back(modelo);
    }

     //grama
    int nGrama = 400; 
    unsigned int texturaGrama = loader.loadTexture("./Textura/grass.jpg");

     for (int i = 0; i < nPedras; i++)
    {
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        Model modelo = loader.loadObj("./Modelos/grass.obj");
        modelo.setPosition(glm::vec3(static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 800 - 400, 0.0, static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 800 - 400));
        modelo.setScale(glm::vec3(5.0f, 5.0f, 5.0f));
        modelo.setTexture(texturaGrama);

        modelos.push_back(modelo);
    }


    // textura dinossauro
    unsigned int texture1 = loader.loadTexture("./Textura/skin.jpg");
    Player player = loader.loadObjPlayer("./Modelos/trex2.obj");
    player.setPosition(glm::vec3(0.0f, 0.0, 0.0));
    player.setScale(glm::vec3(2.0, 2.0, 2.0));

    player.setTexture(texture1);


    //textura do chão
    unsigned int textureChao = loader.loadTexture("./Textura/terrain.jpg");
    Model chao = loader.loadVAO(vertices, indices, textureCoords, normalVec);
    chao.setTexture(textureChao);
    chao.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    chao.setScale(glm::vec3(1000.0f, 0.5f, 1000.0f));
    modelos.push_back(chao);
    /*
    glm::vec3 scale = modelos.at(modelos.size() - 1).getScale();
    cout << scale.x << " " << scale.y << " " << scale.z << endl;*/
    // textura do sol
    glm::vec3 lightPos(.0f, 20.0f, .0f);
    //ourShader.use();

    // loop de renderização

    Camera camera = Camera(player);
    float lastFrame = 0.0f;
    float deltaTime = 0.0;
    glfwSetScrollCallback(window, camera.calculateZoom);
    glfwSetWindowUserPointer(window, &camera);

    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        renderer.clear();
        camera.move(window);
        camera.processInput(window);
        //camera.handleMouse(window);
        player.move(window, deltaTime, modelos);
        //ourShader.use();

        //unsigned int shaderProgram = glGetUniformLocation(ourShader.ID, "transform");
        //glUniformMatrix4fv(shaderProgram, 1, GL_FALSE, glm::value_ptr(transform));
        renderer.render(camera, modelos, player);

        // // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderer.cleanUp();

    //limpar memoria
    glfwTerminate();
    return 0;
}
