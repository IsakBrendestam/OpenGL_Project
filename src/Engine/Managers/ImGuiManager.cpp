#include "ImGuiManager.h"

#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Engine/EngineSettings.h"

#include "Objects/ObjectManager.h"

int ImGuiManager::m_selectedObject = -1;

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
    SceneHierarchy();
    ObjectInspector();

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
    ImGui::Checkbox("Render Grid", &EngineSettings::g_renderGrid);
    ImGui::ColorEdit3("clear color", (float*)&EngineSettings::g_clearColor);

    ImGui::End();
}

void ImGuiManager::SceneHierarchy()
{
    ImGui::Begin("Scene Hierarchy");

    for (int i = 0; i < ObjectManager::GetObjectCount(); i++)
	{
		std::string title = ObjectManager::GetObjectName(i);

		if (ImGui::Selectable(title.c_str(), m_selectedObject == i))
            m_selectedObject = i;
	}

    ImGui::End();
}

void ImGuiManager::ObjectInspector()
{
    ImGui::Begin("Object Inspector");

    if (m_selectedObject >= 0 && m_selectedObject < ObjectManager::GetObjectCount())
    {
        const float min = -100.0f;
        const float max = 100.0f;
        const int index = m_selectedObject;

        if (index != -1)
        {
            std::string title = ObjectManager::GetObjectName(index);

            ImGui::Text(title.c_str(), " - settings");
            ImGui::Separator();

            ObjectManager::GetObject(index)->DrawComponentsUI();

            /*
            bool render = ObjectManager::GetRender(index);
            ImGui::Checkbox("Render ", &render);
            ObjectManager::SetRender(render, index);

            ObjectManager::GetObjectByName(title)->DrawUI();
            */

            /*
            if (ImGui::TreeNode("Texture"))
            {
                int textureIndex = -1;

                std::string options;
                std::vector<std::string> textureNames = ContentManager::GetTextureNames();
                for (auto& name : textureNames)
                    options += name + '\0';

                // Set object texture
                if (ImGui::Combo("Textures", &textureIndex, options.c_str()))
                    ObjectManager::GetObjectByName(title)->SetTexture(ContentManager::GetTexture(textureNames[textureIndex]));


                ImGui::BeginChild("Texture Display", ImVec2(-FLT_MIN, ImGui::GetTextLineHeightWithSpacing() * 8), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeY);

                ShaderResourceTextureD3D11* texture = ObjectManager::GetObjectByName(title)->GetTexture();

                float textureRatio =  (float)texture->GetHeight() / (float)texture->GetWidth();

                ImVec2 child_rect_min = ImGui::GetItemRectMin();
                ImVec2 child_rect_max = ImGui::GetItemRectMax();

                float childWidth = (child_rect_max.x - child_rect_min.x) * 0.9f;

                ImGui::Image((ImTextureID)(intptr_t)texture->GetSRV(), ImVec2(childWidth, childWidth * textureRatio));

                ImGui::EndChild();

                ImGui::TreePop();
            }
            */
        }
    }

    ImGui::End();
}