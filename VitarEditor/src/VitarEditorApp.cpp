#include "VitarPCH.h"
#include <Vitar.h>
#include <Vitar/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Vitar 
{
	class VitarEditor : public Application
	{
	public:
		VitarEditor(ApplicationCommandLineArgs args) : Application("Vitar Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~VitarEditor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new VitarEditor(args);
	}
}
