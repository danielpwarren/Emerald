#include <include/Emerald.h>

class ExampleLayer : public Emerald::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
    {
		m_VertexArray.reset(Emerald::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Emerald::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Emerald::VertexBuffer::Create(vertices, sizeof(vertices)));
		Emerald::BufferLayout layout = {
			{ Emerald::ShaderDataType::Float3, "a_Position" },
			{ Emerald::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Emerald::IndexBuffer> indexBuffer;
		indexBuffer.reset(Emerald::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Emerald::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Emerald::VertexBuffer> squareVB;
		squareVB.reset(Emerald::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Emerald::ShaderDataType::Float3, "a_Position" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Emerald::IndexBuffer> squareIB;
		squareIB.reset(Emerald::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		std::string greyVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string greyFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.25, 0.25, 0.25, 1.0);
			}
		)";

		m_Shader.reset(new Emerald::Shader(vertexSrc, fragmentSrc));
		m_GreyShader.reset(new Emerald::Shader(greyVertexSrc, greyFragmentSrc));
    }

    void OnUpdate() override
    {
		if (Emerald::Input::IsKeyPressed(EM_KEY_W) || Emerald::Input::IsKeyPressed(EM_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed;
		else if (Emerald::Input::IsKeyPressed(EM_KEY_S) || Emerald::Input::IsKeyPressed(EM_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed;

		if (Emerald::Input::IsKeyPressed(EM_KEY_A) || Emerald::Input::IsKeyPressed(EM_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed;
		else if (Emerald::Input::IsKeyPressed(EM_KEY_D) || Emerald::Input::IsKeyPressed(EM_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed;

		if (Emerald::Input::IsKeyPressed(EM_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Emerald::Input::IsKeyPressed(EM_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed;

        Emerald::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Emerald::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Emerald::Renderer::BeginScene(m_Camera);

        Emerald::Renderer::Submit(m_GreyShader, m_SquareVA);
        Emerald::Renderer::Submit(m_Shader, m_VertexArray);

        Emerald::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
    }

    void OnEvent(Emerald::Event& event) override
    {
    }

private:
    std::shared_ptr<Emerald::Shader> m_Shader;
    std::shared_ptr<Emerald::VertexArray> m_VertexArray;

    std::shared_ptr<Emerald::Shader> m_GreyShader;
    std::shared_ptr<Emerald::VertexArray> m_SquareVA;

    Emerald::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.5f;
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
