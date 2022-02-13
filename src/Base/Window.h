#pragma once
namespace tw
{
    class Window
    {
    public:
        /// <summary>
        /// 启动窗口
        /// </summary>
        __declspec(dllexport) static void start();
        /// <summary>
        /// 停止窗口线程
        /// </summary>
        __declspec(dllexport) static void stop();
        ~Window();
    private:
        Window();
        static std::unique_ptr<Window> s_instance;
        static Window& instance();
        static void loop();
        GLFWwindow* m_window;
        std::string m_name;
        size_t m_with;
        size_t m_height;
        double m_deltaTime;
        std::atomic<bool> m_life;
        std::thread m_thread;
    };
}
