#include "ImGuiManager.h"

#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Engine/EngineSettings.h"

void ImGuiManager::Initialize(GLFWwindow* window, const std::string& glslVersion)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion.c_str());

}

void ImGuiManager::Deconstruct()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiManager::Update(double deltaTime)
{
    ScreenStatistics(deltaTime);
    EngineSettings();

    if (ImGui::GetFrameCount() == 1)
        ImGui::SetWindowFocus(nullptr);
}

void ImGuiManager::Sleep(int milliseconds)
{
    ImGui_ImplGlfw_Sleep(milliseconds);
}

void ImGuiManager::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

static double timeSinceFpsAdd = 0;
static double deltaSum = 0;
static int deltaCount = 0;
static double averageDelta = 0;
static std::vector<float> fpsData;
void ImGuiManager::ScreenStatistics(double deltaTime)
{
    deltaSum += deltaTime;
    deltaCount++;

    if (averageDelta == 0)
        averageDelta = deltaTime;

    const double fps = 1000.0f / averageDelta;

    ImGui::Begin("Screen Statistics");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", averageDelta, fps);

    timeSinceFpsAdd += deltaTime;

    if (deltaSum > 100.0f)
    {
        averageDelta = (double)deltaSum / (double)deltaCount;
        deltaSum = 0;
        deltaCount = 0;
    }

    if (timeSinceFpsAdd > 500)
    {
        if (fpsData.size() < 20)
        {
            fpsData.push_back(fps);
        }
        else
        {
            fpsData.erase(fpsData.begin());
            fpsData.push_back(fps);
        }

        timeSinceFpsAdd = 0;
    }

    ImGui::PlotLines("FPS rates", fpsData.data(), fpsData.size());

    ImGui::End();
}

void ImGuiManager::EngineSettings()
{
    ImGui::Begin("Engine Settings");

    ImGui::Checkbox("Wireframe On", &EngineSettings::g_wireframeOn);
    ImGui::Checkbox("Vsync On", &EngineSettings::g_vsyncOn);
    ImGui::Checkbox("Backface Culling On", &EngineSettings::g_backFaceCullingOn);
    ImGui::ColorEdit3("clear color", (float*)&EngineSettings::g_clearColor);

    ImGui::End();
}