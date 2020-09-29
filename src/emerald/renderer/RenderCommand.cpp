#include "core/empch.h"
#include "renderer/RenderCommand.h"

#include "platform/opengl/OpenGLRendererAPI.h"

namespace Emerald {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();

}