#include "VitarPCH.h"
#include <Vitar.h>
#include <Vitar/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Vitar 
{
	class VitarEditor : public Application
	{
	public:
		VitarEditor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Vitar Editor";
		spec.CommandLineArgs = args;

		return new VitarEditor(spec);
	}
}
