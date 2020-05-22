#include "libs.h"

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) {
    glViewport(0, 0, fbW, fbH);
}

bool loadShader(GLuint& program) {
    bool ret = true;
    char infoLog[512];
    GLint success;

    std::string temp = "";
    std::string src = "";
    
    std::ifstream in_file;

    //vertex
    in_file.open("vertex_core.glsl");
    if (in_file.is_open()) {
        while (std::getline(in_file, temp)) {
            src += temp + "\n";
        }
    }
    else {
        std::cout << "ERROR::LOADSHADER::Could_not_open_file" << std::endl;
        ret = false;
    }
    in_file.close();

    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* shaderSrc = src.c_str();
    glShaderSource(shader, 1, &shaderSrc, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::LOADSHADER::Could_not_compile" << std::endl;
        std::cout << infoLog << std::endl;
        ret = false;
    }

    src = "";
    temp = "";
    //fragment
    in_file.open("fragment_core.glsl");
    if (in_file.is_open()) {
        while (std::getline(in_file, temp)) {
            src += temp + "\n";
        }
    }
    else {
        std::cout << "ERROR::LOADSHADER::Could_not_open_file" << std::endl;
        ret = false;
    }
    in_file.close();

    GLuint shader2 = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* shaderSrc2 = src.c_str();
    glShaderSource(shader2, 1, &shaderSrc2, NULL);
    glCompileShader(shader2);

    glGetShaderiv(shader2, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader2, 512, NULL, infoLog);
        std::cout << "ERROR::LOADSHADER::Could_not_compile" << std::endl;
        std::cout << infoLog << std::endl;
        ret = false;
    }

    program = glCreateProgram();
    glAttachShader(program, shader);
    glAttachShader(program, shader2);
    glLinkProgram(program);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::LOADSHADER::Could_not_link0" << std::endl;
        std::cout << infoLog << std::endl;
        ret = false;
    }
     
    glGetProgramiv(program, GL_LINK_STATUS, &success);


    glUseProgram(0);
    glDeleteShader(shader);
    glDeleteShader(shader2);

    return ret;
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

    //Shader Init
    GLuint core_program;
    loadShader(core_program);

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
    glfwDestroyWindow(window);
    glfwTerminate();
    glDeleteProgram(core_program);

      
    return 0;
}
 