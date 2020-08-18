#include "pch.h"
#include "ImGuiLayer.h"

#include "Engine/Application.h"

#include "imgui.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

namespace Engine
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer") {}

	ImGuiLayer::~ImGuiLayer() {}

	void ImGuiLayer::onAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach()
	{

	}

	void ImGuiLayer::onUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0 ? (time - m_time) : 1.0f / 60.0f;
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onEvent(Event& p_event)
	{
		EventDispatcher dispatcher(p_event);
		dispatcher.dispatch<MouseButtonPressedEvent>(BIND_EVENT_FCT(ImGuiLayer::onMouseButtonPressed));
		dispatcher.dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FCT(ImGuiLayer::onMouseButtonReleased));
		dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FCT(ImGuiLayer::onMouseMoved));
		dispatcher.dispatch<MouseScrolledEvent>(BIND_EVENT_FCT(ImGuiLayer::onMouseScrolled));
		dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FCT(ImGuiLayer::onKeyPressed));
		dispatcher.dispatch<KeyReleasedEvent>(BIND_EVENT_FCT(ImGuiLayer::onKeyReleased));
		dispatcher.dispatch<KeyTypedEvent>(BIND_EVENT_FCT(ImGuiLayer::onKeyTyped));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FCT(ImGuiLayer::onWindowResize));
	}

	bool ImGuiLayer::onMouseButtonPressed(MouseButtonPressedEvent& p_event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[p_event.getButton()] = true;

		return false;
	}

	bool ImGuiLayer::onMouseButtonReleased(MouseButtonReleasedEvent& p_event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[p_event.getButton()] = false;

		return false;
	}

	bool ImGuiLayer::onMouseMoved(MouseMovedEvent& p_event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(p_event.getMouseX(), p_event.getMouseY());

		return false;
	}

	bool ImGuiLayer::onMouseScrolled(MouseScrolledEvent& p_event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += p_event.getOffsetX();
		io.MouseWheel += p_event.getOffsetY();

		return false;
	}

	bool ImGuiLayer::onKeyPressed(KeyPressedEvent& p_event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[p_event.getKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_RIGHT_CONTROL] || io.KeysDown[GLFW_KEY_LEFT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_RIGHT_SHIFT] || io.KeysDown[GLFW_KEY_LEFT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_RIGHT_ALT] || io.KeysDown[GLFW_KEY_LEFT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_RIGHT_SUPER] || io.KeysDown[GLFW_KEY_LEFT_SUPER];

		return false;
	}

	bool ImGuiLayer::onKeyReleased(KeyReleasedEvent& p_event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[p_event.getKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::onKeyTyped(KeyTypedEvent& p_event)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (p_event.getKeyCode() > 0 && p_event.getKeyCode() < 0x10000)
			io.AddInputCharacter((unsigned short)p_event.getKeyCode());

		return false;
	}

	bool ImGuiLayer::onWindowResize(WindowResizeEvent& p_event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(p_event.getWidth(), p_event.getHeight());
		io.DisplayFramebufferScale = ImVec2(1, 1);
		glViewport(0, 0, p_event.getWidth(), p_event.getHeight());

		return false;
	}
}