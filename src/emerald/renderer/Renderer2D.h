#pragma once

#include "renderer/Camera.h"

namespace Emerald {

	class Renderer2D
	{
	public:
		Renderer2D() = delete;
		Renderer2D(const Renderer2D&) = delete;
		~Renderer2D() = delete;

		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4 color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4 color);
	};
}