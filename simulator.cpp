#include "simulator.h"
#include<math.h>


void Simulator::initGLFW()
{
    glfwInit();
}

void Simulator::initWindow(const char *title, bool resizable)
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); MAC OS

    this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

    if (this->window == nullptr)
    {
        std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
        glfwTerminate();
    }

    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
    glfwSetFramebufferSizeCallback(window, Simulator::framebuffer_resize_callback);
    //IMPORTANT WITH PERSPECTIVE MATRIX!!!

    glViewport(0, 0, framebufferWidth, framebufferHeight);

    glfwMakeContextCurrent(this->window); //IMPORTANT!!
}

void Simulator::initGLEW()
{
    //INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
    glewExperimental = GL_TRUE;

    //Error
    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
        glfwTerminate();
    }
}

void Simulator::initOpenGLOptions()
{
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //Input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Simulator::initMatrices()
{
    this->SkyViewMatrix = glm::mat4(1.f);
    this->SkyViewMatrix = glm::lookAt(this->position, this->position + this->camFront, this->worldUp);

    this->ViewMatrix = glm::mat4(1.f);
    this->ViewMatrix = this->camera.GetViewMatrix();

    this->ProjectionMatrix = glm::mat4(1.f);
    this->ProjectionMatrix = glm::perspective(
            glm::radians(this->fov),
            static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
            this->nearPlane,
            this->farPlane
                );
    this->ProjectionMatrix2D = glm::mat4(1.f);
    this->ProjectionMatrix2D = glm::ortho(0.0f, 2.0f, 0.0f, 2.0f);
}

void Simulator::initShaders()
{
    this->shaders.push_back( new Shader("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/basic.shader"));
    this->shaders.push_back( new Shader("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/terrain1.shader"));
    this->shaders.push_back( new Shader("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/ortho_2D.shader"));
    this->shaders.push_back( new Shader("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/model.shader"));
    this->shaders.push_back( new Shader("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/terrain2.shader"));
    this->shaders.push_back( new Shader("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/objmodel.shader"));
}

void Simulator::initTextures()
{
    this->paths = {
        "/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/right.jpg",
        "/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/left.jpg",
        "/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/top.jpg",
        "/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/bottom.jpg",
        "/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/front.jpg",
        "/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/back.jpg"
    };
//TEXTURE0
   this->textures.push_back(new Texture("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/container.jpg"));
//TEXTURE1
   this->textures.push_back(new Texture("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/badge.png"));
//TEXTURE2
   this->textures.push_back(new Texture("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/dark.png"));
//TEXTURE3
   this->textures.push_back(new Texture("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/path.png"));
//TEXTURE4
   this->textures.push_back(new Texture("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/pavement.jpg"));
//TEXTURE5
   this->textures.push_back(new Texture("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/snow.png"));
//TEXTURE6
   this->textures.push_back(new Texture("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/grass1.jpg"));
//TEXTURE6
   this->textures.push_back(new Texture("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/christmas_tree.png"));
//TEXTURE6
   this->textures.push_back(new Texture("/home/oracle247/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/snowflake.png"));
//TEXTURE7
   this->textures.push_back(new Texture(paths));

}

void Simulator::initMaterials()
{
    this->materials.push_back(new Material(ambient, diffuse, specular, shininess));


}

void Simulator::initMeshes()
{


    this->meshes.push_back(new Mesh(
            Cube(),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
    ));
    this->meshes.push_back(new Mesh(
            Terrain(),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
    ));
    this->meshes.push_back(new Mesh(
            Pyramid(),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
    ));
    this->meshes.push_back(new Mesh(
            Quad(),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
    ));
    this->meshes.push_back(new Mesh(
            SkyBox(),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
    ));
    this->meshes.push_back(new Mesh(
            Terrain2(),
            glm::vec3(0.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
    ));

    this->meshes.push_back(new Mesh(
            Plane(),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(2.f)));
}

void Simulator::initOBJModels()
{
    vector<Vertex> temp;
    //temp = loadOBJ("/home/eresoft/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/model/donut.obj");
}

void Simulator::initLights()
{
    this->lights.push_back(new glm::vec3(0.0f, 0.0f, -3.0f));

}

void Simulator::initUniforms()
{
    this->shaders[SHADER_CORE_PROGRAM]->Bind();
    this->shaders[SHADER_CORE_PROGRAM]->SetUniform1i("u_texture0", 0);
    this->shaders[SHADER_CORE_PROGRAM]->SetUniform3f("ambient", this->ambient);
    this->shaders[SHADER_CORE_PROGRAM]->SetUniform3f("diffuse", this->diffuse);
    this->shaders[SHADER_CORE_PROGRAM]->SetUniform3f("lightPos0", *this->lights[LIGHT_POS0]);
    this->shaders[SHADER_CORE_PROGRAM]->SetUniform3f("camPosition", this->camPosition);

    this->shaders[SHADER_TERRAIN]->Bind();
    this->shaders[SHADER_TERRAIN]->SetUniform1i("u_texture0", 0);
    this->shaders[SHADER_TERRAIN]->SetUniform1i("u_texture1", 1);
    this->shaders[SHADER_TERRAIN]->SetUniform1i("u_texture2", 2);
    this->shaders[SHADER_TERRAIN]->SetUniform3f("u_ambient", this->ambient);
    this->shaders[SHADER_TERRAIN]->SetUniform3f("u_diffuse", this->diffuse);
    this->shaders[SHADER_TERRAIN]->SetUniform3f("lightPos1", *this->lights[LIGHT_POS0]);
    this->shaders[SHADER_TERRAIN]->SetUniform3f("camPosition1", this->camPosition);

    this->shaders[SHADER_ORTHO]->Bind();
    this->shaders[SHADER_ORTHO]->SetUniform1i("u_texture0", 0);
    this->materials[MAT_1]->sendToShader(*this->shaders[SHADER_TERRAIN]);

    this->shaders[SHADER_SKYBOX]->Bind();
    this->shaders[SHADER_SKYBOX]->SetUniform1i("u_texture0", 0);
    this->shaders[SHADER_SKYBOX]->SetUniform4f("u_color", 0.6f, 0.6f, 0.9f, 1.f);

    this->shaders[SHADER_TERRAIN1]->Bind();
    this->shaders[SHADER_TERRAIN1]->SetUniform1i("u_texture0", 0);
    this->shaders[SHADER_TERRAIN1]->SetUniform3f("u_ambient", this->ambient);
    this->shaders[SHADER_TERRAIN1]->SetUniform3f("u_diffuse", this->diffuse);
    this->shaders[SHADER_TERRAIN1]->SetUniform3f("lightPos1", *this->lights[LIGHT_POS0]);
    this->shaders[SHADER_TERRAIN1]->SetUniform3f("camPosition1", this->camPosition);

    this->shaders[SHADER_MODEL]->Bind();
    this->shaders[SHADER_MODEL]->SetUniform1i("u_texture0", 0);

}


Simulator::Simulator(
        const char *title,
        const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
        const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
        bool resizable
)
        :
        WINDOW_WIDTH(WINDOW_WIDTH),
        WINDOW_HEIGHT(WINDOW_HEIGHT),
        GL_VERSION_MAJOR(GL_VERSION_MAJOR),
        GL_VERSION_MINOR(GL_VERSION_MINOR),
        camera(glm::vec3(0.f, 1.f, 5.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f))
{

//Init variables
    this->window = nullptr;
    this->framebufferWidth = this->WINDOW_WIDTH;
    this->framebufferHeight = this->WINDOW_HEIGHT;

    this->camPosition = glm::vec3(0.f, 1.f, 5.0f);
    this->worldUp = glm::vec3(0.f, 1.f, 0.f);
    this->camFront = glm::vec3(0.f, 0.f, -1.f);

    this->fov = 60.f;
    this->nearPlane = 0.5f;
    this->farPlane = 1000.f;

    this->dt = 0.f;
    this->curTime = 0.f;
    this->lastTime = 0.f;

    this->lastMouseX = 0.0;
    this->lastMouseY = 0.0;
    this->mouseX = 0.0;
    this->mouseY = 0.0;
    this->mouseOffsetX = 0.0;
    this->mouseOffsetY = 0.0;
    this->firstMouse = true;

    this->light = 0.6;
    this->ambient = vec3(light);
    this->SBambient = vec3(0.6f);
    this->diffuse = vec3(0.5f);
    this->specular = vec3(1.0f);
    this->shininess = 35.0f;

    this->initGLFW();
    this->initWindow(title, resizable);
    this->initGLEW();
    this->initOpenGLOptions();

    this->initMatrices();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
    this->initMeshes();
    //this->initOBJModels();
//        this->initModels();
    this->initLights();
    this->initUniforms();
}

Simulator::~Simulator()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();

    for (size_t i = 0; i < this->shaders.size(); i++)
        delete this->shaders[i];

    for (size_t i = 0; i < this->textures.size(); i++)
        delete this->textures[i];

    for (size_t i = 0; i < this->materials.size(); i++)
        delete this->materials[i];

    for (size_t i = 0; i < this->meshes.size(); i++)
        delete this->meshes[i];

    for (size_t i = 0; i < this->lights.size(); i++)
        delete this->lights[i];
}

int Simulator::getWindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

void Simulator::setWindowShouldClose()
{
    glfwSetWindowShouldClose(this->window, GL_TRUE);
}

void Simulator::updatePlane()
{

}

void Simulator::updateDt()
{
    this->curTime = static_cast<float>(glfwGetTime());
    this->dt = curTime - this->lastTime;
    this->lastTime = this->curTime;
}

void Simulator::updateMouseInput()
{
    glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

    if(this->firstMouse){
        this->lastMouseX = this->mouseX;
        this->lastMouseY = this->mouseY;
        this->firstMouse = false;
    }

    //calc offset
    this->mouseOffsetX = this->mouseX - this->lastMouseX;
    this->mouseOffsetY = this->mouseY - this->lastMouseY;

    //set last y and x
    this->lastMouseX = this->mouseX;
    this->lastMouseY = this->mouseY;

    camera.ProcessMouseMovement(this->dt, mouseOffsetX, mouseOffsetY);
}

void Simulator::updateInput()
{

}

void Simulator::update()
{
    //UPDATE INPUT
    glfwPollEvents();
    this->updateDt();
    this->updateMouseInput();
    this->updateKeyboardInput(this->window, *this->meshes[6]);

    //UPDATE WINDOW SIZE
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

    this->ViewMatrix = glm::mat4(1.f);
    this->ViewMatrix = this->camera.GetViewMatrix();

    this->ProjectionMatrix  = perspective(
                glm::radians(this->fov),
                 static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
                this->nearPlane,
                this->farPlane
    );
    shaders[SHADER_CORE_PROGRAM]->Bind();
    this->shaders[SHADER_CORE_PROGRAM]->SetUniform3f("ambient", this->ambient);
    shaders[SHADER_CORE_PROGRAM]->SetUniformMat4f("view", this->ViewMatrix);
    shaders[SHADER_CORE_PROGRAM]->SetUniformMat4f("projection", this->ProjectionMatrix);
}

void Simulator::render()
{

    processInput(window);

    GLCall(glClearColor(0.f, 0.f, 0.72f, 1.f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


    //render skyBox

    glDepthMask(GL_FALSE);
    shaders[SHADER_SKYBOX]->Bind();
    this->textures[7]->Bind();
    this->SkyViewMatrix = glm::mat4(glm::mat3(camera.GetSkyViewMatrix()));
    shaders[SHADER_SKYBOX]->SetUniformMat4f("view", this->SkyViewMatrix);
    shaders[SHADER_SKYBOX]->SetUniformMat4f("projection", this->ProjectionMatrix);
    this->meshes[4]->Draw(*this->shaders[SHADER_SKYBOX]);

    glDepthMask(GL_TRUE);

    //render terrain

    this->textures[3]->Bind();
    this->textures[6]->Bind(1);
    this->textures[5]->Bind(2);
    shaders[SHADER_TERRAIN]->Bind();
    this->shaders[SHADER_TERRAIN]->SetUniform3f("u_ambient", this->ambient);
    shaders[SHADER_TERRAIN]->SetUniformMat4f("view", this->ViewMatrix);
    shaders[SHADER_TERRAIN]->SetUniformMat4f("projection", this->ProjectionMatrix);
    this->meshes[1]->Draw(*this->shaders[SHADER_TERRAIN]);


    {
        //render terrain1
        this->textures[6]->Bind(0);
        shaders[SHADER_TERRAIN1]->Bind();
        this->shaders[SHADER_TERRAIN1]->SetUniform3f("u_ambient", this->ambient);
        shaders[SHADER_TERRAIN1]->SetUniformMat4f("view", this->ViewMatrix);
        shaders[SHADER_TERRAIN1]->SetUniformMat4f("projection", this->ProjectionMatrix);
        this->meshes[5]->Draw(*this->shaders[SHADER_TERRAIN1]);
    }

        this->textures[0]->Bind();
        this->meshes[6]->Draw(*this->shaders[SHADER_CORE_PROGRAM]);

    //    //draw houses

    for(int i = 0; i < 5; i++){
        this->textures[0]->Bind();
        this->meshes[0]->setPosition(vec3(-3.f, -0.5f, -i * 2.f));
        this->meshes[0]->Draw(*this->shaders[SHADER_CORE_PROGRAM]);

        this->textures[2]->Bind();
        this->meshes[2]->setPosition(vec3(-3.f, 0.5f, -i * 2.f));
        this->meshes[2]->Draw(*this->shaders[SHADER_CORE_PROGRAM]);
    }
    for(int i = 0; i < 5; i++){
        this->textures[0]->Bind();
        this->meshes[0]->setPosition(vec3(5.f, -0.5f, -i * 2.f));
        this->meshes[0]->Draw(*this->shaders[SHADER_CORE_PROGRAM]);

        this->textures[2]->Bind();
        this->meshes[2]->setPosition(vec3(5.f, 0.5f, -i * 2.f));
        this->meshes[2]->Draw(*this->shaders[SHADER_CORE_PROGRAM]);
    }
    //render 2D image
    this->textures[7]->Bind();
    shaders[SHADER_ORTHO]->Bind();
    this->meshes[3]->setPosition(vec3( 0.f, 0.f, 0.f));
    shaders[SHADER_ORTHO]->SetUniformMat4f("projection", this->ProjectionMatrix2D);
    this->meshes[3]->Draw(*this->shaders[SHADER_ORTHO]);

    this->textures[8]->Bind();
    this->meshes[3]->setPosition(vec3( 1.5f, 0.f, 0.f));
    this->meshes[3]->Draw(*this->shaders[SHADER_ORTHO]);


    glfwSwapBuffers(window);

}

void Simulator::processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Simulator::framebuffer_resize_callback(GLFWwindow *window, int fbW, int fbH)
{
    glViewport(0, 0, fbW, fbH);
}

void Simulator::framebuffer_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

void Simulator::updateKeyboardInput(GLFWwindow *window, Mesh &mesh){

    if(glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS){
        mesh.move(-0.01, true);
        camera.move(this->dt, 0);
    }
    if(glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS){
        camera.move(this->dt, 1);
    }
    if(glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS){
        camera.move(this->dt, 2);
        cout<<"a is pressed"<<endl;
    }
    if(glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS){
        camera.move(this->dt, 3);
    }
    if(glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS){
        mesh.Rotate(vec3(0.f, -0.1f,  0.f), true);
    }
    if(glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS){
        mesh.Rotate(vec3(0.f, 0.1f,  0.f), true);
    }
    if(glfwGetKey(this->window, GLFW_KEY_R) == GLFW_PRESS){
        mesh.Rotate(vec3(-0.1f, 0.f,  0.f), true);
    }
    if(glfwGetKey(this->window, GLFW_KEY_F) == GLFW_PRESS){
        mesh.Rotate(vec3(0.1f, 0.f,  0.f), true);
    }
    if(glfwGetKey(this->window, GLFW_KEY_Z) == GLFW_PRESS){
        this->ambient -= 0.001f;
        this->ambient -= 0.001f;
        this->SBambient -= 0.001f;
   }
    if(glfwGetKey(this->window, GLFW_KEY_X) == GLFW_PRESS){
        this->ambient += 0.001f;
        this->SBambient += 0.001f;
    }
};

