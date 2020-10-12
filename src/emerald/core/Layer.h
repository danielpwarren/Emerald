#pragma once

#include "core/Base.h"
#include "core/Timestep.h"

#include "events/Event.h"

namespace Emerald {

	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach(){}
		virtual void OnDetach() {}
		virtual void OnUpdate(const Timestep& timestep) {}
		virtual void OnImGuiRender() {}

		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
	
}
