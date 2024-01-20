#include "EditorLayer.h"
#include "RBEngine.h"
#include "EditorCamera.h"
#include "RBEditorUI/GUIInternal.h"
#include "Windows/Viewport.h"
#include "Windows/Hierarchy.h"
#include "Windows/Inspector.h"
#include "Windows/ContentBrowser.h"

#include <imgui.h>
#include <yaml-cpp/yaml.h>

namespace RB::Editor
{
    void EditorLayer::OnAttach()
    {
        PushWindow(new Viewport());
        PushWindow(new Hierarchy());
        PushWindow(new Inspector());
        PushWindow(new ContentBrowser());

        m_ActiveScene = Scene::Create();
        m_ActiveScene->SetState(SceneState::Editing);

        Window::OnKeyPressed += RB_BIND_FNC(_OnKeyPressed);
    }

    void EditorLayer::OnDetach()
    {

    }

    void EditorLayer::OnUpdate()
    {
        for (auto& window : m_Windows)
        {
            window->OnUpdate();
        }

        if (m_ActiveScene && m_ActiveScene->GetState() == SceneState::Editing)
        {
            m_ActiveScene->OnEditorUpdate(*m_Camera, m_Camera->GetTransform());
        }
    }

    void EditorLayer::OnRenderUI()
    {
        _DrawMainMenuBar();

        for (auto& window : m_Windows)
        {
            window->BeginRender();
            window->OnGUIRender();
            window->EndRender();
        }
    }

    void EditorLayer::PushWindow(EditorWindow* window)
    {
        auto it = std::find(m_Windows.begin(), m_Windows.end(), window);
        if (it == m_Windows.end())
        {
            m_Windows.push_back(window);
            window->OnAttach();
        }
    }

    void EditorLayer::PopWindow(EditorWindow* window)
    {
        for (size_t i = 0; i < m_Windows.size(); i++)
        {
            if (strcmp(m_Windows[i]->GetWindowTitle(), window->GetWindowTitle()))
            {
                m_Windows.erase(m_Windows.begin() + i);
                window->OnDetach();
                break;
            }
        }
    }

    void EditorLayer::SetEditorCamera(EditorCamera* camera)
    {
        Get().m_Camera = camera;
    }

    void EditorLayer::_DrawMainMenuBar()
    {
        static bool showImGuiDemo = false;
        if (showImGuiDemo)
            ImGui::ShowDemoWindow();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.0f, 10.0f });
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::IsWindowHovered())
            {
                _MoveWindow();
            }

            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("Save Scene", "CTRL+S"))
                    m_ActiveScene->Save();

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Editor"))
            {
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Debug"))
            {
                if (ImGui::MenuItem("Show ImGui Demo"))
                    showImGuiDemo = !showImGuiDemo;

                ImGui::EndMenu();
            }

            { // Set Window Title
                float width = ImGui::CalcTextSize(Application::GetWindow()->GetTitle().c_str()).x + ImGui::GetStyle().FramePadding.x * 2.0f;
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - width / 2);

                if (m_ActiveScene->GetDataState() == SceneDataState::Synced)
                    ImGui::Text(Application::GetWindow()->GetTitle().c_str());
                else
                    ImGui::Text(std::string(Application::GetWindow()->GetTitle() + "*").c_str());
            }

            { // Window Operation Buttons
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
                float width = ImGui::CalcTextSize(" - ").x + ImGui::GetStyle().FramePadding.x * 2.0f;
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() - width * 3);
                if (ImGui::Button(" - "))
                    Application::GetWindow()->MinimizeWindow();

                if (ImGui::Button("[ ]"))
                    Application::GetWindow()->MaximizeWindow();

                if (ImGui::Button(" X "))
                    Application::Get().Close();
                ImGui::PopStyleVar();
            }

            ImGui::EndMainMenuBar();
        }
        ImGui::PopStyleVar();
    }

    void EditorLayer::_MoveWindow()
    {
        if (Input::IsKeyPressed(KeyCode::LeftMouseButton) && Application::GetWindow()->GetWindowState() == WindowState::Windowed)
        {
            Vector2 mousePos = Input::GetMouseScreenPosition();
            if (m_MouseToWindowOffset.x == 0 && m_MouseToWindowOffset.y == 0)
            {
                IVector2 windPos = Application::GetWindow()->GetWindowPosition();
                m_MouseToWindowOffset = { windPos.x - mousePos.x, windPos.y - mousePos.y };
            }

            Application::GetWindow()->SetWindowPosition(IVector2(mousePos.x + m_MouseToWindowOffset.x, mousePos.y + m_MouseToWindowOffset.y));
        }
        else
        {
            m_MouseToWindowOffset = { 0, 0 };
        }
    }

    bool EditorLayer::_OnKeyPressed(int key)
    {
        if (key == KeyCode::S && Input::IsKeyPressed(KeyCode::LeftControl))
            m_ActiveScene->Save();

        return false;
    }
}