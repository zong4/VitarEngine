#pragma once

#include "Vitar/Core/Layer.h"

#include "Vitar/Events/ApplicationEvent.h"
#include "Vitar/Events/KeyEvent.h"
#include "Vitar/Events/MouseEvent.h"

namespace Vitar 
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	
	private:
		bool m_BlockEvents = true;
	};
}
