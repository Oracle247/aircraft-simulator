


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

#include "vendor/stb_image/stb_image.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

int main()
{

//1024 680
    Simulator simulator(
                "simulator",
                1024, 700,
                3, 3,
                false
    );


    while (!simulator.getWindowShouldClose()){
        
        simulator.update();
        simulator.render();
        
    }
    
    glfwTerminate();
    
return 0;
}
