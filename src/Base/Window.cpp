#include "pch.h"
#include <iostream>
namespace tw
{
    std::unique_ptr<Window> Window::s_instance;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        // camera.set_wh(width, height);
    }

    static void APIENTRY gl_debug_output(GLenum source, GLenum type, GLuint id, GLenum severity,
        GLsizei length, const GLchar* message, const void* userParam)
    {
        // 忽略一些不重要的错误/警告代码
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        std::cout << "---------------" << std::endl;
        std::cout << "Debug message (" << id << "): " << message << std::endl;

        switch (source)
        {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
        } std::cout << std::endl;

        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
        } std::cout << std::endl;

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
        } std::cout << std::endl;
        std::cout << std::endl;
    }

    void Window::start()
    {
        Window& window = instance();
    }

    void Window::stop()
    {
        s_instance = nullptr;
    }

    Window::~Window()
    {
        m_life = 0;
        while (m_life == true) {}
        m_thread.join();
    }

    Window& Window::instance()
    {
        if (s_instance == nullptr)
            s_instance.reset(new Window);
        return *s_instance;
    }

    void Window::loop()
    {
        Window& window = instance();
        window.m_life = true;
        WhenDestructing wd([&] {window.m_life = false; });
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 64); //抗齿锯
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        window.m_window = glfwCreateWindow(window.m_with, window.m_height, window.m_name.c_str(), NULL, NULL);
        if (window.m_window == NULL)
        {
            std::cout << "Failed to create GLFW window";
            return;
        }
        glfwMakeContextCurrent(window.m_window);
        glfwSetFramebufferSizeCallback(window.m_window, framebuffer_size_callback);
        // load all opengl function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD";
            return;
        }
        /* debug */
        GLint flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(gl_debug_output, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
        // 绘图窗口大小
        glEnable(GL_MULTISAMPLE);
        glViewport(0, 0, window.m_with, window.m_height);
        double lastFrame = glfwGetTime();
        while (!glfwWindowShouldClose(window.m_window))
        {
            if (window.m_life == 0)
                break;
            float currentFrame = glfwGetTime();
            window.m_deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            std::cout << "Hi" << std::endl;

            glFlush();
            glfwSwapBuffers(window.m_window);
            glfwPollEvents();
        }
        glfwTerminate();
    }

    Window::Window() :
        m_window(nullptr),
        m_name("YouQixiaowu"),
        m_with(1000),
        m_height(1000),
        m_deltaTime(0.0),
        m_life(0),
        m_thread(Window::loop)
    {
    }
}