#include "VitarPCH.h"
#include <Vitar.h>
#include <Vitar/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Vitar 
{
	class Vitarnut : public Application
	{
	public:
		Vitarnut() : Application("Vitar Editor")
		{
			PushLayer(new EditorLayer());
		}

		~Vitarnut()
		{
		}
	};

	Application* CreateApplication()
	{
		return new Vitarnut();
	}
}