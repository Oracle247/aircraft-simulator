#ifndef LIBS_H
#define LIBS_H
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "simulator.h"
#include "renderer.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexbufferlayout.h"
#include "material.h"
#include "vertex.h"
#include "primitive.h"
#include "camera.h"
#endif // LIBS_H

//CODE ARCHIVE
/*******************************************************
 //GLFWwindow* createWindow(
//    const char* title,
//    const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
//    int& fbWidth, int& fbHeight,
//    const int GLmajorVer, const int GLminorVer,
//    bool resizable
//){
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLmajorVer);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLminorVer);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_RESIZABLE, resizable);

//    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, NULL, NULL);

//    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//    glfwMakeContextCurrent(window);
//    return window;
//}
//GLFW INIT
glfwInit();
//WINDOW CREATION
const int GLmajorVer = 3;
const int GLminorVer = 3;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
int framebufferWidth = 0;
int framebufferHeight = 0;

GLFWwindow *window = createWindow(
    "Simulation",
    WINDOW_WIDTH, WINDOW_HEIGHT,
    framebufferWidth, framebufferHeight,
    GLmajorVer, GLminorVer,
    false
);


//GLEW INIT
if(glewInit() != GLEW_OK){
    cout<<"error while trying to initialize glew"<<endl;
    return -1;
}

glEnable(GL_DEPTH_TEST);
// Accept fragment if it closer to the camera than the former one
glDepthFunc(GL_LESS);

//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    glFrontFace(GL_CCW);

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

//glClearColor(0,0,0,0);

//    //MATRIX INIT
//    vec3 position(0.0f);
//    vec3 rotation(0.0f);
//    vec3 scaling(1.0f);

//    //projection matrix
//    float fov = 60.0f;
//    float nearPlane = 0.1f;
//    float farPlane = 1000.0f;

//    mat4 proj  = perspective(
//                glm::radians(fov),
//                static_cast<float>(framebufferWidth) / framebufferHeight,
//                nearPlane,
//                farPlane
//         );

//    // Camera matrix
//    vec3 camPosition(0.0f, 0.0f, 2.f);
//    vec3 camFront(0.0f, 0.0f, -1.0f);
//    vec3 worldUp(0.0f, 1.0f, 0.0f);
//    mat4 view = lookAt(
//        camPosition, // Camera is at (4,3,3), in World Space
//        camPosition * camFront, // and looks at the origin
//        worldUp  // Head is up (set to 0,-1,0 to look upside-down)
//    );

//    //model matrix

//    //mat4 mvp = proj * view * model;

//    Mesh mesh = Mesh(
//            Quad(),
//            glm::vec3(1.f, 0.f, 0.f),
//            glm::vec3(0.f),
//            glm::vec3(0.f),
//            glm::vec3(1.f)
//    );
////    //BUFFER ATTRIB


//    //SHADER

//    Shader shader("/home/eresoft/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/basic.shader");
//    shader.Bind();
//    //shader.SetUniform4f("u_color", 1.0f, 0.5f, 0.05f, 1.0f);
//    shader.SetUniform1i("u_texture0", 0);

//    //TEXTURE INIT

//    Texture texture("/home/eresoft/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/textures/pics/container.jpg");

//    //LIGHT
//    vec3 lightPos0(0.0f, 0.0f, -1.0f);
//    shader.SetUniform3f("lightPos0", lightPos0);
//    shader.SetUniform3f("camPosition", camPosition);

//    //MATERIAL INIT
//    vec3 ambient(0.1f);
//    vec3 diffuse(0.5f);
//    vec3 specular(1.0f);
//    float shininess = 35.0f;
//    Material material(ambient, diffuse, specular, shininess);
//    material.sendToShader(shader);

//        glfwPollEvents();
//        updateKeyboardInput(window, position, rotation, scaling);

//        processInput(window);

//        GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
//        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

//        shader.Bind();

//        mesh.setPosition(position);
//        mesh.setScale(scaling);
//        mesh.setRotation(rotation);

//        //mesh.updateModelMatrix();
//        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

//        mat4 proj  = perspective(
//                    glm::radians(fov),
//                    static_cast<float>(framebufferWidth) / framebufferHeight,
//                    nearPlane,
//                    farPlane
//        );

//        //mesh.updateUniforms(shader);
//        //shader.SetUniformMat4f("model", model);
//        shader.SetUniformMat4f("view", view);
//        shader.SetUniformMat4f("projection", proj);

//        texture.Bind();

//        mesh.Draw(shader);

//        glfwSwapBuffers(window);

//void processInput(GLFWwindow *window){
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}

//void framebuffer_size_callback(GLFWwindow* window, int width, int height){
//    glViewport(0, 0, width, height);
//}

//void updateKeyboardInput(GLFWwindow* window, vec3& position, vec3& rotation, vec3& scaling){
//    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
//        position.z -= 0.01f;
//    }
//    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
//        position.z += 0.01f;
//    }
//    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
//        position.x -= 0.01f;
//    }
//    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
//        position.x += 0.01f;
//    }
//    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
//        rotation.y -= 1.f;
//    }
//    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
//        rotation.y += 1.f;
//    }
//    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
//        rotation.x -= 1.f;
//    }
//    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
//        rotation.x += 1.f;
//    }
//    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS){
//        scaling -= 0.01f;
//    }
//    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
//        scaling += 0.01f;
//    }
//}

    //ObjLoader archive
//        vector<Vertex> vertices = {
//            // positions
//            {glm::vec3(-1.0f,  1.0f, -1.0f)},
//            {glm::vec3(-1.0f, -1.0f, -1.0f)},
//            {glm::vec3( 1.0f, -1.0f, -1.0f)},
//            {glm::vec3( 1.0f, -1.0f, -1.0f)},
//            {glm::vec3( 1.0f,  1.0f, -1.0f)},
//            {glm::vec3(-1.0f,  1.0f, -1.0f)},

//            {glm::vec3(-1.0f, -1.0f,  1.0f)},
//            {glm::vec3(-1.0f, -1.0f, -1.0f)},
//            {glm::vec3(-1.0f,  1.0f, -1.0f)},
//            {glm::vec3(-1.0f,  1.0f, -1.0f)},
//            {glm::vec3(-1.0f,  1.0f,  1.0f)},
//            {glm::vec3(-1.0f, -1.0f,  1.0f)},

//            {glm::vec3( 1.0f, -1.0f, -1.0f)},
//            {glm::vec3( 1.0f, -1.0f,  1.0f)},
//            {glm::vec3( 1.0f,  1.0f,  1.0f)},
//            {glm::vec3( 1.0f,  1.0f,  1.0f)},
//            {glm::vec3( 1.0f,  1.0f, -1.0f)},
//            {glm::vec3( 1.0f, -1.0f, -1.0f)},

//            {glm::vec3(-1.0f, -1.0f,  1.0f)},
//            {glm::vec3(-1.0f,  1.0f,  1.0f)},
//            {glm::vec3( 1.0f,  1.0f,  1.0f)},
//            {glm::vec3( 1.0f,  1.0f,  1.0f)},
//            {glm::vec3( 1.0f, -1.0f,  1.0f)},
//            {glm::vec3(-1.0f, -1.0f,  1.0f)},

//            {glm::vec3(-1.0f,  1.0f, -1.0f)},
//            {glm::vec3( 1.0f,  1.0f, -1.0f)},
//            {glm::vec3( 1.0f,  1.0f,  1.0f)},
//            {glm::vec3( 1.0f,  1.0f,  1.0f)},
//            {glm::vec3(-1.0f,  1.0f,  1.0f)},
//            {glm::vec3(-1.0f,  1.0f, -1.0f)},

//            {glm::vec3(-1.0f, -1.0f, -1.0f)},
//            {glm::vec3(-1.0f, -1.0f,  1.0f)},
//            {glm::vec3( 1.0f, -1.0f, -1.0f)},
//            {glm::vec3( 1.0f, -1.0f, -1.0f)},
//            {glm::vec3(-1.0f, -1.0f,  1.0f)},
//            {glm::vec3( 1.0f, -1.0f,  1.0f)}
//        };
        //unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
//        sizeOfVer = sizeof (vertices) * sizeof (Vertex);
//        unsigned long sizeOfInd = 0;


    //HEIGHT MAP
//std::vector<glm::vec3> Heightmap::generateRandomHeightData(const HillAlgorithmParameters& params)
//{
//	std::vector<double> heightData(params.rows, std::vector<double>(params.columns, 0.0f));

//	std::random_device rd;
//	std::mt19937 generator(rd());
//	std::uniform_int_distribution hillRadiusDistribution(params.hillRadiusMin, params.hillRadiusMax);
//	std::uniform_real_distribution hillHeightDistribution(params.hillMinHeight, params.hillMaxHeight);
//	std::uniform_int_distribution hillCenterRowIntDistribution(0, params.rows - 1);
//	std::uniform_int_distribution hillCenterColIntDistribution(0, params.columns - 1);

//	for (int i = 0; i < params.numHills; i++)
//	{
//		const auto hillCenterRow = hillCenterRowIntDistribution(generator);
//		const auto hillCenterCol = hillCenterColIntDistribution(generator);
//		const auto hillRadius = hillRadiusDistribution(generator);
//		const auto hillHeight = hillHeightDistribution(generator);

//		for (auto r = hillCenterRow - hillRadius; r < hillCenterRow + hillRadius; r++)
//		{
//			for (auto c = hillCenterCol - hillRadius; c < hillCenterCol + hillRadius; c++)
//			{
//				if (r < 0 || r >= params.rows || c < 0 || c >= params.columns) {
//					continue;
//				}
//				const auto r2 = hillRadius * hillRadius; // r*r term
//				const auto x2x1 = hillCenterCol - c; // (x2-x1) term
//				const auto y2y1 = hillCenterRow - r; // (y2-y1) term
//				const auto height = float(r2 - x2x1 * x2x1 - y2y1 * y2y1);
//				if (height < 0.0f) {
//					continue;
//				}
//				const auto factor = height / r2;
//				heightData[r][c] += hillHeight * factor;
//				if (heightData[r][c] > 1.0f) {
//					heightData[r][c] = 1.0f;
//				}
//			}
//		}
//	}
//	return heightData;
//}
************************************************/
