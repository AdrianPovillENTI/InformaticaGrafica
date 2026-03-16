#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void main()
{
    int iFrameBufferHeight = 0;
    int iFrameBufferWidth = 0;
    
    /* Initialize the library */
    glfwInit();

    // S'adapta a la targeta grafica de l'ordinador i als seus drivers
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Fem servir la versió 4 ja que la 5 es experimental
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // La finrestra és reescalable? 
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Richard", NULL, NULL);
    // Si volem fer pantalla completa podem posar al primer NULL glfwGetPrimaryMonitor()
    // El segon se li pot passar un punter a una altra window per passar-se informació entre windows

    if (!window)
        glfwTerminate();

    // Em retorna el tamany del buffer que puc pintar, normalment es la mida del viewport(la finestra generada)
    glfwGetFramebufferSize(window, &iFrameBufferWidth, &iFrameBufferHeight);



    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}