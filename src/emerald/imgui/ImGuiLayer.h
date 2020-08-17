#pragma once

#pragma once

#include <engine/Layer.h>

#include <events/ApplicationEvent.h>
#include <events/KeyEvent.h>
#include <events/MouseEvent.h>

namespace Emerald {

    class EM_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };
}