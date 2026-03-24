#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
using namespace ImGui;

int main() {
    if (!glfwInit()) return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1600, 900, "ImGui Docking Demo", NULL, NULL);
    if (!window) return 1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO& io = GetIO();

    // DOCKING AKTIVIEREN!
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    StyleColorsDark();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGuiStyle& style = GetStyle();
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool show_demo = true;
    bool show_tools = true;
    bool show_settings = true;
    bool show_scene = true;

    static float slider_value = 0.5f;
    static int color_choice = 0;
    static bool checkbox_value = true;
    static char text_input[128] = "Hello ImGui!";
    static float positions[3] = { 0.0f, 0.0f, 0.0f };
    static float rotation = 0.0f;

    const char* colors[] = { "Rot", "Grün", "Blau", "Gelb" };

    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        NewFrame();

        // DOCKING SPACE über das ganze Fenster
        DockSpaceOverViewport();

        if (show_demo) ShowDemoWindow(&show_demo);

        if (show_tools) {
            Begin("Tools", &show_tools);
            SliderFloat3("Position", positions, -10.0f, 10.0f);
            SliderFloat("Rotation", &rotation, -180.0f, 180.0f);
            SliderFloat("Wert", &slider_value, 0.0f, 1.0f);
            Checkbox("Option", &checkbox_value);
            InputText("Text", text_input, sizeof(text_input));
            Combo("Farbe", &color_choice, colors, IM_ARRAYSIZE(colors));
            End();
        }

        if (show_settings) {
            Begin("Settings", &show_settings);
            Checkbox("Demo Fenster", &show_demo);
            Checkbox("Tools", &show_tools);
            Checkbox("Scene", &show_scene);
            Text("FPS: %.1f", io.Framerate);
            End();
        }

        if (show_scene) {
            Begin("Scene", &show_scene);
            Text("Position: (%.2f, %.2f, %.2f)", positions[0], positions[1], positions[2]);
            Text("Rotation: %.2f°", rotation);
            Text("Text: %s", text_input);
            Text("Farbe: %s", colors[color_choice]);
            End();
        }

        Render();

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup = glfwGetCurrentContext();
            UpdatePlatformWindows();
            RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}