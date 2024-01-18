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
    Vector3 position{ 0.0f, 0.0f, 0.0f };

    void EditorLayer::OnAttach()
    {
        PushWindow(new Viewport());
        PushWindow(new Hierarchy());
        PushWindow(new Inspector());
        PushWindow(new ContentBrowser());

        m_ActiveScene = Scene::Create();

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

        if (m_Camera && m_ActiveScene)
        {
            m_ActiveScene->OnEditorUpdate(*m_Camera, m_Camera->GetTransform());
        }
    }

    void EditorLayer::OnRenderUI()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("Save Scene", "CTRL+S"))
                    _SaveScene();

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

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

    bool EditorLayer::_OnKeyPressed(int key)
    {
        if (key == KeyCode::S && Input::IsKeyPressed(KeyCode::LeftControl))
            _SaveScene();

        return false;
    }

    void EditorLayer::_SaveScene()
    {
        SceneSerializer serial(m_ActiveScene);
        serial.Serialize();
        if (Debug::Result result = serial.Serialize(); result & Debug::ResultCode::Success)
        {
            Debug::Log::Info("Saved Scene!");
        }
        else
        {
            Debug::Log::Error(result.Message.c_str());
        }
    }
}