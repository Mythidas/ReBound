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
    Editor::Viewport* viewport;
    Hierarchy* hierarchy;
    Inspector* inspector;
    ContentBrowser* content;
    Vector3 position{ 0.0f, 0.0f, 0.0f };

    void EditorLayer::OnAttach()
    {
        viewport = new Editor::Viewport();
        hierarchy = new Hierarchy();
        inspector = new Inspector();
        content = new ContentBrowser();
    }

    void EditorLayer::OnDetach()
    {

    }

    void EditorLayer::OnUpdate()
    {
        m_Camera.OnUpdate();
        m_Camera.OnResize({ (uint32_t)viewport->GetSize().x, (uint32_t)viewport->GetSize().y });

        Renderer::BeginFrame(m_Camera, m_Camera.GetTransform());
        Renderer::DrawQuad(position);
        Renderer::EndFrame();
    }

    void EditorLayer::OnRenderUI()
    {
        viewport->BeginRender();
        viewport->OnGUIRender();
        viewport->EndRender();

        hierarchy->BeginRender();
        hierarchy->OnGUIRender();
        hierarchy->EndRender();

        inspector->BeginRender();
        inspector->OnGUIRender();
        inspector->EndRender();

        content->BeginRender();
        content->OnGUIRender();
        content->EndRender();
    }
}