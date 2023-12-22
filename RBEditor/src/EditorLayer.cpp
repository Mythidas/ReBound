#include "EditorLayer.h"
#include "RBEngine.h"
#include "EditorCamera.h"
#include "Windows/Viewport.h"
#include "Windows/Hierarchy.h"
#include "Windows/Inspector.h"
#include "Windows/ContentBrowser.h"

#include <imgui.h>

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

        auto ent = m_ActiveScene->GetRegistry().CreateEntity("Test Emt");
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
            static bool file = false;
            ImGui::MenuItem("File", NULL, file);

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
        m_Camera = camera;
    }
}