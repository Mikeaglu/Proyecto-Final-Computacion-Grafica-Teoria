// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"

// Properties
const GLuint WIDTH = 1800, HEIGHT = 900;
int SCREEN_WIDTH, SCREEN_HEIGHT;


// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(5.0f, 2.0f, -15.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float puerta = 0.0f;
float silla = 0.0f;
int bandera = 0.0f;
int bandera1 = 0.0f;
float ventana1 = 0.0f;
float ventana2 = 0.0f;
int bandera2 = 0.0f;
int bandera3 = 0.0f;
float Cofretapa = 0.0f;
int bandera4 = 0.0f;
float BarrilTapa = 0.0f;
int bandera5 = 0.0f;


int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit()){
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");

    // Load models
    Model CasaCompleta((char*)"Models/Proyecto/CasaFinal.obj");
    Model Puerta((char*)"Models/Proyecto/puertabuena.obj");
    Model Silla((char*)"Models/Proyecto/Silla.obj");
    Model Ventana1((char*)"Models/Proyecto/ventana1.obj");
    Model Ventana2((char*)"Models/Proyecto/ventana2.obj");
    Model CofreTapa((char*)"Models/Proyecto/CofretapaFinal.obj");
    Model Barriltapa((char*)"Models/Proyecto/BarrilTapa.obj");

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Game loop
    while (!glfwWindowShouldClose(window)){

        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        CasaCompleta.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(5.05f, 2.0f, -10.96f));
        model = glm::rotate(model, glm::radians(puerta), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Puerta.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.99f, 6.7f, -10.00f));
        model = glm::rotate(model, glm::radians(Cofretapa), glm::vec3(1.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        CofreTapa.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(6.5f, 1.0f, -1.5f + silla));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Silla.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(4.5f, 6.55f + BarrilTapa, 5.05f ));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Barriltapa.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-7.9f, 3.0f, -4.96f));
        model = glm::rotate(model, glm::radians(ventana1), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ventana1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-7.94f, 3.0f, -2.075f));
        model = glm::rotate(model, glm::radians(ventana2), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        Ventana2.Draw(shader);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement(){
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]){
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]){
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]){
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]){
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (keys[GLFW_KEY_P]){ //Movimiento de la Puerta
        if (puerta > -90.0f && bandera == 0) {
            puerta -= 1.0f;
            if (puerta == -90.0f) {
                bandera = 1;
            }
        }else if (puerta < 0.0f && bandera == 1) {
            puerta += 1.5f;
            if (puerta == 0.0f) {
                bandera = 0;
            }
        }
    }
    if (keys[GLFW_KEY_C]){ //Movimiento de la Silla
        if (silla <= 1.0f && bandera1 == 0) {
            silla += 0.1f;
        }
    }

    if (keys[GLFW_KEY_V]){ //Movimiento de la Ventana 1
        if (ventana1 > -180.0f && bandera2 == 0) {
            ventana1 -= 1.0f;
            if (ventana1 == -180.0f) {
                bandera2 = 1;
            }
        }else if (ventana1 < 0.0f && bandera2 == 1) {
            ventana1 += 1.5f;
            if (ventana1 == 0.0f) {
                bandera2 = 0;
            }
        }
    }

    if (keys[GLFW_KEY_B]){ //Movimiento de la Ventana 2
        if (ventana2 < 180.0f && bandera3 == 0) {
            ventana2 += 1.0f;
            if (ventana2 == 180.0f) {
                bandera3 = 1;
            }
        }else if (ventana2 > 0.0f && bandera3 == 1) {
            ventana2 -= 1.5f;
            if (ventana2 == 0.0f) {
                bandera3 = 0;
            }
        }
    }
    if (keys[GLFW_KEY_T]) { //Movimiento de la Tapa del Cofre
        if (Cofretapa > -90.0f && bandera4 == 0) {
            Cofretapa -= 1.0f;
            if (Cofretapa == -90.0f) {
                bandera4 = 1;
            }
        }
        else if (Cofretapa < 0.0f && bandera4 == 1) {
            Cofretapa += 1.5f;
            if (Cofretapa == 0.0f) {
                bandera4 = 0;
            }
        }
    }
    if (keys[GLFW_KEY_K]) { //Movimiento de la Tapa del Barril
        if (BarrilTapa <= 1.0f && bandera1 == 0) {
            BarrilTapa += 0.1f;
        }
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024){
        if (action == GLFW_PRESS){
            keys[key] = true;
        }else if (action == GLFW_RELEASE){
            keys[key] = false;
        }
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos){
    if (firstMouse){
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}