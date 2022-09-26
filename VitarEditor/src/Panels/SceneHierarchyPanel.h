#pragma once

#include "Vitar/Core/Base.h"
#include "Vitar/Core/Log.h"
#include "Vitar/Scene/Scene.h"
#include "Vitar/Scene/Entity.h"

namespace Vitar 
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}
