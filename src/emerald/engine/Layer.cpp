#include "engine/empch.h"
#include "engine/Layer.h"

namespace Emerald {

    Layer::Layer(const std::string& debugName)
        : m_DebugName(debugName) 
    {
    }

    Layer::~Layer()
    {
    }
}
