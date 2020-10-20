#include "include/Emerald.h"
#include "core/EntryPoint.h"

#include "EditorLayer.h"

namespace Emerald {

	class EmeraldEditor : public Application
	{
	public:
		EmeraldEditor()
			: Application("Emerald Editor")
		{
			PushLayer(new EditorLayer());
		}

		~EmeraldEditor()
		{
		}
	private:
	};

	Application* CreateApplication()
	{
		return new EmeraldEditor();
	}
}


