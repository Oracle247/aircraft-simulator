#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "libs.h"
#include "objloader.h"


//ENUMERATIONS
enum shader_enum { SHADER_CORE_PROGRAM = 0, SHADER_TERRAIN, SHADER_ORTHO, SHADER_SKYBOX, SHADER_TERRAIN1, SHADER_MODEL };
enum texture_enum { TEX_PUSHEEN = 0, TEX_PUSHEEN_SPECULAR, TEX_CONTAINER, TEX_CONTAINER_SPECULAR };
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_CUBE = 0, MESH_TERRAIN, MESH_PYRAMID, MESH_QUAD, MESH_SKYBOX, MESH_TERRAIN2, MESH_OBJ };
enum light_enum {LIGHT_POS0 = 0};

class Simulator
{
private:
//Variables
    //Window
    GLFWwindow* window;
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    int framebufferWidth;
    int framebufferHeight;

    //OpenGL Context
    const int GL_VERSION_MAJOR;
    const int GL_VERSION_MINOR;

    //Delta time
    float dt;
    float curTime;
    float lastTime;


    //Mouse Input
    double lastMouseX;
    double lastMouseY;
    double mouseX;
    double mouseY;
    double mouseOffsetX;
    double mouseOffsetY;
    bool firstMouse;

    //Airplane stuff
    double pitch;
    double roll;
    double yaw;

    //Matrices
    glm::mat4 ViewMatrix;
    glm::vec3 camPosition;
    glm::vec3 worldUp;
    glm::vec3 camFront;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scaling;

    glm::mat4 SkyViewMatrix;
    glm::mat4 ProjectionMatrix2D;
    glm::mat4 ProjectionMatrix;
    float fov;
    float nearPlane;
    float farPlane;

    //materials init
    float light;
    glm::vec3 ambient;
    glm::vec3 SBambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    //glm::vec3 lightPos;

    //Shaders
    std::vector<Shader*> shaders;

    //Textures
    std::vector<Texture*> textures;

    //Materials
    std::vector<Material*> materials;

    //Meshes
    std::vector<Mesh*> meshes;

    //Lights
    std::vector<glm::vec3*> lights;

    //Camaras
    Camera camera;

    //skyBox initialization
    std::vector<string> paths;

//Private functions
    void initGLFW();
    void initWindow(
        const char* title,
        bool resizable
    );
    void initGLEW(); //AFTER CONTEXT CREATION!!!
    void initOpenGLOptions();
    void initMatrices();
    void initShaders();
    void initTextures();
    void initMaterials();
    void initMeshes();
    void initOBJModels();
    void initModels();
    void initPointLights();
    void initLights();
    void initUniforms();

    void updateUniforms();

public:
//Constructors / Destructors
    Simulator(
        const char* title,
        const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
        const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
        bool resizable
    );
    virtual ~Simulator();

//Accessors
    int getWindowShouldClose();

//Modifiers
    void setWindowShouldClose();

    void updatePlane();
    void updateDt();
    void updateMouseInput();
    void updateKeyboardInput(GLFWwindow *window, Mesh &mesh);
    void updateInput();
    void update();
    void render();
    void processInput(GLFWwindow *window);

//Static functions
    static void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);\
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif // SIMULATOR_H
