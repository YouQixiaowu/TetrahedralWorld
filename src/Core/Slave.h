#pragma once
namespace tw
{
    class Slave
    {
    public:
        Slave();
        ~Slave();
        void push(const std::string& taskName);
    private:
        void loop();
        // 任务队列
        std::queue<std::string> m_tasks;
        // 线程退出标志
        std::atomic<bool> m_life;
        // 线程
        std::thread m_thread;
    };
}


template<typename T>
class lock_free_stack
{
private:
    struct node
    {
        T data;
        node* next;

        node(T const& data_) :
            data(data_)
        {}
    };

    std::atomic<node*> head;
public:
    void push(T const& data)
    {
        node* const new_node = new node(data);
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node));
    }
};