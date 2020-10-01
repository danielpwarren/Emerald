#include "include/Emerald.h"
#include "core/EntryPoint.h"
#include "platform/opengl/OpenGLShader.h"

#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Sandbox2D.h"

class ExampleLayer : public Emerald::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1920.0f / 1080.0f, true)
	{
		m_SquareVA = Emerald::VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Emerald::Ref<Emerald::VertexBuffer> squareVB;
		squareVB = Emerald::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Emerald::ShaderDataType::Float3, "a_Position" },
			{ Emerald::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Emerald::Ref<Emerald::IndexBuffer> squareIB;
		squareIB = Emerald::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_EmeraldLogoTexture = Emerald::Texture2D::Create("assets/textures/Emerald.png");

		std::dynamic_pointer_cast<Emerald::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Emerald::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(const Emerald::Timestep& timestep) override
	{
		m_Framerate = 1 / timestep;

		m_CameraController.OnUpdate(timestep);

		Emerald::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Emerald::RenderCommand::Clear();

		Emerald::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		auto flatColorShader = m_ShaderLibrary.Get("FlatColor");

		std::dynamic_pointer_cast<Emerald::OpenGLShader>(flatColorShader)->Bind();
		std::dynamic_pointer_cast<Emerald::OpenGLShader>(flatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = -5; y <= 5; y++)
		{
			for (int x = -10; x <= 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Emerald::Renderer::Submit(flatColorShader, m_SquareVA, transform);
			}
		}

		m_EmeraldLogoTexture->Bind();
		auto textureShader = m_ShaderLibrary.Get("Texture");
		Emerald::Renderer::Submit(textureShader, m_SquareVA);

		Emerald::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::LabelText("Framerate", "FPS: %.3f", m_Framerate);
		//ImGui::InputFloat3("Camera position", glm::value_ptr(m_CameraPosition), 3);
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		//ImGui::SliderFloat("Camera rotation", &m_CameraController.GetCamera().GetRotation(), 0.0f, 360.0f);
		ImGui::End();
	}

	void OnEvent(Emerald::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

private:
	Emerald::ShaderLibrary m_ShaderLibrary;

	Emerald::Ref<Emerald::VertexArray> m_SquareVA;

	Emerald::Ref<Emerald::Texture2D> m_EmeraldLogoTexture;

	Emerald::OrthographicCameraController m_CameraController;

	float m_Framerate;

	glm::vec3 m_SquarePosition;
	glm::vec3 m_SquareColor = { 0.2f, 0.2f, 0.2f };
};

class Sandbox : public Emerald::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox()
	{
	}

};

Emerald::Application* Emerald::CreateApplication()
{
	return new Sandbox();
}
