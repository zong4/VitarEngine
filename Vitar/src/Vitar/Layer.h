#pragma once

#include "Vitar/Core.h"
#include "Vitar/Core/Timestep.h"
#include "Vitar/Events/Event.h"

namespace Vitar
{
	class VITAR_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(Timestep timeStep){}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& event){}

		inline const std::string& GetName() const { return m_DebugName; }
	
	protected:
		std::string m_DebugName;
	};
}
