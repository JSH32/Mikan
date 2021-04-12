#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>

#include "gui.h"
#include "util.h"
#include "version.h"

#include <cmrc/cmrc.hpp>
CMRC_DECLARE(resources);

int main(int argc, char** argv) {
    auto resources = cmrc::resources::get_filesystem();

    if (!glfwInit()) {
        std::cerr << "Initialization failed" << std::endl;
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(480, 432, "Mikan", NULL, NULL);
    if (!window) {
        std::cerr << "Window creation failed" << std::endl;
        return 1;
    }

    glfwSetWindowAspectRatio(window, 10, 9);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Key callback
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    });

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((const char*)glGetString(GLAD_GL_VERSION_4_6));

    ImVec4 clearColor = ImVec4(0.16f, 0.2f, 0.23f, 1.00f);

    cmrc::file aboutFile = resources.open("about.png");

    int aboutW, aboutH;
    GLuint aboutTexture;
    loadTextureFromImage((unsigned char*)aboutFile.begin(), aboutFile.size(), aboutTexture, aboutW, aboutH);
    bool showAbout = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // Write frame/gui code in this scope
        {
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Open")) {
                        
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Help")) {
                    if (ImGui::MenuItem("About"))
                        showAbout = true;
                    ImGui::EndMenu();
                }

                ImGui::EndMainMenuBar();
            }

            showDockspace();

            if (showAbout) {
                ImGui::Begin("About", &showAbout);
                ImGui::Image((void*)(intptr_t)aboutTexture, ImVec2((float)aboutW/3, (float)aboutH/3));
                ImGui::Text(GIT_BRANCH);
                ImGui::Text(GIT_COMMIT_HASH);
                ImGui::Text(GIT_COMMIT_DATE);
                ImGui::End();
            }

            ImGui::Begin("Game");
            ImGui::Text("No game currently loaded");
            ImGui::Button("Open");
            ImGui::End();
        }

        ImGui::EndFrame();

        ImGui::Render();
        int displayW, displayH;
        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    // Delete textures
    glDeleteTextures(1, &aboutTexture);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}