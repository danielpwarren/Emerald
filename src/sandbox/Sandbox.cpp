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
		/*
		m_VertexArray.reset(Emerald::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		Emerald::Ref<Emerald::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Emerald::VertexBuffer::Create(vertices, sizeof(vertices)));
		Emerald::BufferLayout layout = {
			{ Emerald::ShaderDataType::Float3, "a_Position" },
			{ Emerald::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Emerald::Ref<Emerald::IndexBuffer> indexBuffer;
		indexBuffer.reset(Emerald::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		*/
		m_SquareVA.reset(Emerald::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Emerald::Ref<Emerald::VertexBuffer> squareVB;
		squareVB.reset(Emerald::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Emerald::ShaderDataType::Float3, "a_Position" },
			{ Emerald::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Emerald::Ref<Emerald::IndexBuffer> squareIB;
		squareIB.reset(Emerald::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			void main()
			{
				color = vec4(v_TexCoord, 0.0, 1.0);
			}
		)";
		
		m_TextureShader.reset(Emerald::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

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

		m_FlatShader.reset(Emerald::Shader::Create(flatVertexSrc, flatFragmentSrc));
	}

	void OnUpdate(const Emerald::Timestep& timestep) override
	{
		EM_TRACE("Delta time: {0} ({1}ms)", timestep, timestep.GetMilliseconds());

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

		for (int y = -5; y <= 5; y++)
		{
			for (int x = -10; x <= 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				std::dynamic_pointer_cast<Emerald::OpenGLShader>(m_FlatShader)->UploadUniformFloat3("u_Color", m_SquareColor);
				Emerald::Renderer::Submit(m_FlatShader, m_SquareVA, transform);
			}
		}

		Emerald::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Emerald::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::InputFloat3("Camera position", glm::value_ptr(m_CameraPosition), 3);
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::SliderFloat("Camera rotation", &m_CameraRotation, 0.0f, 360.0f);
		ImGui::End();
	}

	void OnEvent(Emerald::Event& event) override
	{
	}

private:
	//Emerald::Ref<Emerald::Shader> m_Shader;
	//Emerald::Ref<Emerald::VertexArray> m_VertexArray;

	Emerald::Ref<Emerald::Shader> m_FlatShader, m_TextureShader;
	Emerald::Ref<Emerald::VertexArray> m_SquareVA;

	Emerald::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 2.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 45.0f;

	glm::vec3 m_SquarePosition;
	glm::vec3 m_SquareColor = { 1.0f, 1.0f, 1.0f };
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
