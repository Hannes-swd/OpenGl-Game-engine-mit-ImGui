#include <GLFW/glfw3.h>
#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_glfw.h"
#include "include/imgui/imgui_impl_opengl3.h"
#include <iostream>

// Fehler-Callback für GLFW (optional)
static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main() {
    // GLFW initialisieren
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Fenster erstellen
    const char* glsl_version = "#version 130"; // Passen Sie die GLSL-Version an Ihre OpenGL-Version an
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "OpenGL + ImGui", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-Sync

    // Dear ImGui initialisieren
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Tastaturnavigation aktivieren

    // ImGui-Style (optional)
    ImGui::StyleColorsDark();

    // Plattform- und Renderer-Backends einrichten
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Hauptschleife
    while (!glfwWindowShouldClose(window)) {
        // Neue Frame beginnen
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ----- Hier Ihr ImGui-Code -----
        ImGui::Begin("Hallo Welt!");
        ImGui::Text("Dear ImGui funktioniert!");
        ImGui::End();
        // -------------------------------

        // Rendern
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Aufräumen
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}