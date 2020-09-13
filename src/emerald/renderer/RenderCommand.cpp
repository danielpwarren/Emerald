#include "core/empch.h"
#include "renderer/RenderCommand.h"

#include "platform/opengl/OpenGLRendererAPI.h"

namespace Emerald {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}