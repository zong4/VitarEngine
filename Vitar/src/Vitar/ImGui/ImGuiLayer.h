#pragma once

#include "Vitar/Layer.h"
#include "Vitar/Events/MouseEvent.h"
#include "Vitar/Events/ApplicationEvent.h"
#include "Vitar/Events/KeyEvent.h"

namespace Vitar 
{
	class VITAR_API ImGuiLayer : public Layer
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