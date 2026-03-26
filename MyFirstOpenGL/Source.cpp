#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

struct ShaderProgram {

    GLuint vertexShader = 0;
    GLuint geometryShader = 0;
    GLuint fragmentShader = 0;
};

void ResizeWindow(GLFWwindow* window, int iNewFrameBufferWidth, int iNewFrameBufferHeight) {

    // Es defineix la mida del viewport
    glViewport(0, 0, iNewFrameBufferWidth, iNewFrameBufferHeight);
}

// Retorna una string per a retrornar el shader a carregar a la GPU
std::string Load_File(const std::string& filePath) {
    std::ifstream file(filePath);

    std::string fileContent;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "No s'ha pogut obrir l'arxiu" << filePath << std::endl;
        std::exit(EXIT_FAILURE);
    }

    //Llegim el fitxer i el carreguem a fileContent.
    while (std::getline(file, line)) {
        fileContent += line + "\n";
    }

    // Tanquem Stream de dades i retornem el contingut

    file.close();
    return fileContent;
}

GLuint LoadVertexShader(const std::string& filePath) {

    // Crear un vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Usamos la funcion creada para leer el vertex shader y almacenarlo 
    std::string sShaderCode = Load_File(filePath);
    const char* cShaderSource = sShaderCode.c_str();

    //Vinculamos el vertex shader con su código fuente
    glShaderSource(vertexShader, 1, &cShaderSource, nullptr);

    // Compilar el vertex shader
    glCompileShader(vertexShader);

    // Verificar errores de compilación
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    //Si la compilacion ha sido exitosa devolvemos el vertex shader
    if (success) {

        return vertexShader;

    }
    else {

        //Obtenemos longitud del log
        GLint logLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

        //Obtenemos el log
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(vertexShader, logLength, nullptr, errorLog.data());

        //Mostramos el log y finalizamos programa
        std::cerr << "Se ha producido un error al cargar el vertex shader:  " << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }

}

GLuint LoadGeometryShader(const std::string& filePath) {

    // Crear un vertex shader
    GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

    //Usamos la funcion creada para leer el vertex shader y almacenarlo 
    std::string sShaderCode = Load_File(filePath);
    const char* cShaderSource = sShaderCode.c_str();

    //Vinculamos el vertex shader con su código fuente
    glShaderSource(geometryShader, 1, &cShaderSource, nullptr);

    // Compilar el vertex shader
    glCompileShader(geometryShader);

    // Verificar errores de compilación
    GLint success;
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

    //Si la compilacion ha sido exitosa devolvemos el vertex shader
    if (success) {
        return geometryShader;
    }
    else {

        //Obtenemos longitud del log
        GLint logLength;
        glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &logLength);

        //Obtenemos el log
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(geometryShader, logLength, nullptr, errorLog.data());

        //Mostramos el log y finalizamos programa
        std::cerr << "Se ha producido un error al cargar el GEOMETRY shader:  " << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}


GLuint LoadFragmentShader(const std::string& filePath) {

    // Crear un vertex shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Usamos la funcion creada para leer el vertex shader y almacenarlo 
    std::string sShaderCode = Load_File(filePath);
    const char* cShaderSource = sShaderCode.c_str();

    //Vinculamos el vertex shader con su código fuente
    glShaderSource(fragmentShader, 1, &cShaderSource, nullptr);

    // Compilar el vertex shader
    glCompileShader(fragmentShader);

    // Verificar errores de compilación
    GLint success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    //Si la compilacion ha sido exitosa devolvemos el vertex shader
    if (success) {
        return fragmentShader;
    }
    else {

        //Obtenemos longitud del log
        GLint logLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

        //Obtenemos el log
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(fragmentShader, logLength, nullptr, errorLog.data());

        //Mostramos el log y finalizamos programa
        std::cerr << "Se ha producido un error al cargar el GEOMETRY shader:  " << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

GLuint CreateProgram(const ShaderProgram& shaders) {

    //Crear programa de la GPU
    GLuint program = glCreateProgram();

    //Verificar que existe un vertex shader o un geometry shader y adjuntarlo al programa
    if (shaders.vertexShader != 0)
        glAttachShader(program, shaders.vertexShader);
    if (shaders.geometryShader != 0) 
        glAttachShader(program, shaders.geometryShader);
    if (shaders.fragmentShader != 0) 
        glAttachShader(program, shaders.fragmentShader);

    
    // Linkear el programa
    glLinkProgram(program);

    //Obtener estado del programa
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    //Devolver programa si todo es correcto o mostrar log en caso de error
    if (success) {

        //Liberamos recursos
        if (shaders.vertexShader != 0)
            glDetachShader(program, shaders.vertexShader);
        if (shaders.geometryShader != 0)
            glDetachShader(program, shaders.geometryShader);
        if (shaders.fragmentShader != 0)
            glDetachShader(program, shaders.fragmentShader);

        return program;
    }
    else {

        //Obtenemos longitud del log
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        //Almacenamos log
        std::vector<GLchar> errorLog(logLength);
        glGetProgramInfoLog(program, logLength, nullptr, errorLog.data());

        std::cerr << "Error al linkar el programa:  " << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);
    }
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


    glEnable(GL_CULL_FACE);
    // Per a que els triangles es vegin només per una cara.
    glCullFace(GL_BACK);

    if (glewInit() == GLEW_OK) {
        // Ha furulao

        //Declarar vec2 para definir el offset
        //glm::vec2 offset = glm::vec2(0.f, 0.f);

        //Compilar shaders
        ShaderProgram myFirstProgram;
        myFirstProgram.vertexShader = LoadVertexShader("MyFirstVertexShader.glsl");
        myFirstProgram.geometryShader = LoadGeometryShader("MyFirstGeometryShader.glsl");
        myFirstProgram.fragmentShader = LoadFragmentShader("MyFirstFragmentShader.glsl");

        //Compilar programa
        GLuint myFirstCompiledProgram;
        myFirstCompiledProgram = CreateProgram(myFirstProgram);

        //Obtener referencia a offset
        GLint offsetReference = glGetUniformLocation(myFirstCompiledProgram, "offset");

        // Li definim el color base del buffer
        glClearColor(1.f, 1.f, 1.f, 1.f/*Blanc*/);

        GLuint vaoPuntos, vboPuntos;

        // Genero 1 VAO i l'emmagatzemo a vaoPuntos
        glGenVertexArrays(1, &vaoPuntos); //Li dic la quantitat de VAOs i li dono la variable on vull que els guardi

        // Activo vaopuntos per a treballar
        glBindVertexArray(vaoPuntos);

        // Genero 1 VBO i l'emmagatzemo a vboPuntos
        glGenBuffers(1, &vboPuntos);

        // Indico quin VBO es l'actiu i que aquest emmagatzema un array de dades
        glBindBuffer(GL_ARRAY_BUFFER, vboPuntos);

        //Posición X e Y del punto
        GLfloat punto[] = {
            -0.5f, -0.25f, // Vértice superior izquierdo
             0.5f, -0.25f, // Vértice superior derecho
             0.0f,  0.6f // Vértice inferior derecho
        };

        //Definimos modo de dibujo para cada cara
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

        glUseProgram(myFirstCompiledProgram);

        while (!glfwWindowShouldClose(window)) {
            // Detecció de inputs
            glfwPollEvents();

            // Netejem tots els buffers
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            // Activo VAO amb la geometria carregada
            glBindVertexArray(vaoPuntos);

            // Dibuixo la geometria
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

            // Desactivo VAO amb la geometria carregada
            glBindVertexArray(0);

            // Canviem els Buffers
            glFlush(); // Flush procura la sincronització de Frame Rate i Refresh Rate
            glfwSwapBuffers(window);
        }

        //Desactivar y eliminar programa
        glUseProgram(0);
        glDeleteProgram(myFirstCompiledProgram);
    }
    else
    {
        // No funca
        // Tanquem connexió amb la targeta
        glfwTerminate();
    }
    glfwTerminate();
}