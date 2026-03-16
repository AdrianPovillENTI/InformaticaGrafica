#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void ResizeWindow(GLFWwindow* window, int iNewFrameBufferWidth, int iNewFrameBufferHeight) {

    // Es defineix la mida del viewport
    glViewport(0, 0, iNewFrameBufferWidth, iNewFrameBufferHeight);
}

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
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Richard", NULL, NULL);
    // Si volem fer pantalla completa podem posar al primer NULL glfwGetPrimaryMonitor()
    // El segon se li pot passar un punter a una altra window per passar-se informació entre windows

    if (!window)
        glfwTerminate();

    // Em retorna el tamany del buffer que puc pintar, normalment es la mida del viewport(la finestra generada)
    glfwSetFramebufferSizeCallback(window, ResizeWindow);   // se li passa la finestra que es reescala i 
                                                            // la funció que s'executarà quan es reescali

    // Defineixo la finestra sobre la que treballarem
    glfwMakeContextCurrent(window);

    // Per poder fer servir funcions que per a qui no tingui actualitzats els drivers podrien considerarse
    // experimentals tot i que actualment no ho siguin, per asegurarnos que funcionen en qualsevol tarj.gràf.

    glewExperimental = GL_TRUE;

    if (glewInit() == GLEW_OK) {
        // Ha furulao

        // Li definim el color base del buffer
        glClearColor(1.f, 0.f, 0.f, 1.f/*vermell*/);

        GLuint vaoPuntos, vboPuntos;

        // Genero 1 VAO i l'emmagatzemo a vaoPuntos
        glGenVertexArrays(1, &vaoPuntos); //Li dic la quantitat de VAOs i li dono la variable on vull que els guardi

        // Activo vaopuntos per a treballar
        glBindVertexArray(vaoPuntos);

        // Genero 1 VBO i l'emmagatzemo a vboPuntos
        glGenBuffers(1, &vboPuntos);

        // Indico quin VBO es l'actiu i que aquest emmagatzema un array de dades
        glBindBuffer(GL_ARRAY_BUFFER, vboPuntos);

        // Declaro puntos {x, y}
        GLfloat punto[] = { 0.f, 0.f };

        glBufferData(GL_ARRAY_BUFFER, sizeof(punto), punto, GL_STATIC_DRAW);

        // indico com llegir la informació
        glVertexAttribPointer(0, 2/*de 0 a 2 (2D)*/, 
            GL_FLOAT/*Tipus de dada*/, 
            GL_FALSE /*Si tenim un model escalat, això ho normalitza si esta en true*/,
            2* sizeof(GLfloat) /*Quantes vegades s'ha de desplaçar el punter, 
            com son dos floats s'ha de moure els bits que ocupen dos floats*/, 
            (GLvoid*) 0/*No massa important, millor a 0 sempre*/);

        // Active, les ddades per a que la gpu pugui usar-les
        glEnableVertexAttribArray(0);

        //Desvinculo VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Desvinculo VAO
        glBindVertexArray(0);

        while (!glfwWindowShouldClose(window)) {
            // Detecció de inputs
            glfwPollEvents();

            // Netejem tots els buffers
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            // Activo VAO amb la geometria carregada
            glBindVertexArray(vaoPuntos);

            // Dibuixo la geometria
            glDrawArrays(GL_POINTS, 0, 1);

            // Desactivo VAO amb la geometria carregada
            glBindVertexArray(0);

            // Canviem els Buffers
            glFlush(); // Flush procura la sincronització de Frame Rate i Refresh Rate
            glfwSwapBuffers(window);
        }
    }
    else
    {
        // No funca
        // Tanquem connexió amb la targeta
        glfwTerminate();
    }
    glfwTerminate();
}