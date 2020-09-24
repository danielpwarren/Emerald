#include "include/Emerald.h"
#include "platform/opengl/OpenGLShader.h"

#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class ExampleLayer : public Emerald::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		m_SquareVA = Emerald::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
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

		std::string flatVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		
		std::string flatFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatShader = Emerald::Shader::Create(flatVertexSrc, flatFragmentSrc);
		m_TextureShader = Emerald::Shader::Create("assets/shaders/Texture.glsl");

		m_EmeraldLogoTexture = Emerald::Texture2D::Create("assets/textures/Emerald.png");

		std::dynamic_pointer_cast<Emerald::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Emerald::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(const Emerald::Timestep& timestep) override
	{
		m_Framerate = 1 / timestep;

		if (Emerald::Input::IsKeyPressed(EM_KEY_W) || Emerald::Input::IsKeyPressed(EM_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * timestep;

		if (Emerald::Input::IsKeyPressed(EM_KEY_S) || Emerald::Input::IsKeyPressed(EM_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * timestep;

		if (Emerald::Input::IsKeyPressed(EM_KEY_A) || Emerald::Input::IsKeyPressed(EM_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * timestep;

		if (Emerald::Input::IsKeyPressed(EM_KEY_D) || Emerald::Input::IsKeyPressed(EM_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * timestep;

		if (Emerald::Input::IsKeyPressed(EM_KEY_Q))
		{
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
			if (m_CameraRotation > 360.0f || m_CameraRotation <= 0.0f)
				m_CameraRotation = 360.0f;
		}

		if (Emerald::Input::IsKeyPressed(EM_KEY_E))
		{
			m_CameraRotation += m_CameraRotationSpeed * timestep;
			if (m_CameraRotation > 360.0f || m_CameraRotation < 0.0f)
				m_CameraRotation = 0.0f;
		}

		Emerald::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Emerald::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Emerald::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Emerald::OpenGLShader>(m_FlatShader)->Bind();
		std::dynamic_pointer_cast<Emerald::OpenGLShader>(m_FlatShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = -5; y <= 5; y++)
		{
			for (int x = -10; x <= 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Emerald::Renderer::Submit(m_FlatShader, m_SquareVA, transform);
			}
		}

		m_EmeraldLogoTexture->Bind();
		Emerald::Renderer::Submit(m_TextureShader, m_SquareVA);

		Emerald::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::LabelText("Framerate", "FPS: %d", m_Framerate);
		ImGui::InputFloat3("Camera position", glm::value_ptr(m_CameraPosition), 3);
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::SliderFloat("Camera rotation", &m_CameraRotation, 0.0f, 360.0f);
		ImGui::End();
	}

	void OnEvent(Emerald::Event& event) override
	{
	}

private:
	Emerald::Ref<Emerald::Shader> m_FlatShader, m_TextureShader;
	Emerald::Ref<Emerald::VertexArray> m_SquareVA;

	Emerald::Ref<Emerald::Texture2D> m_Texture, m_EmeraldLogoTexture;

	Emerald::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 2.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 45.0f;

	int m_Framerate;

	glm::vec3 m_SquarePosition;
	glm::vec3 m_SquareColor = { 0.2f, 0.2f, 0.2f };
};

class Sandbox : public Emerald::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{
	}

};

Emerald::Application* Emerald::CreateApplication()
{
	return new Sandbox();
}
