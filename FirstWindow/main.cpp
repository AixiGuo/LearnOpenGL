#include "libs.h"

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) {
    glViewport(0, 0, fbW, fbH);
}

int main()
{
    // Init GLFW
    glfwInit();

    // Create Window
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    int framebufferWidth = 0;
    int framebufferHeight = 0;
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"IC3D",NULL,NULL);

    glfwMakeContextCurrent(window); //Important
     
    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::MAIN.CPP::Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    } 

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    //glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    //glViewport(0, 0, framebufferWidth, framebufferHeight);

    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        //UPDATE INPUT
        glfwPollEvents();

        //UPDATE
       
        //DRAW

        //clear
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //draw

        //ENDDRAW
        glfwSwapBuffers(window);
        glFlush();
    }

    // End of Program
    glfwTerminate();

      
    return 0;
}
 