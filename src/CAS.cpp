#include <iostream>
#include <string>
#include <thread>
#include <random>
#include <atomic>
#include <vector>
#include "windows.h"
size_t N = 5;
class RingLibrary
{
private:
public:
    const size_t m_size;
    std::vector<int> m_task_stack;          // 任务栈
    std::atomic<size_t> m_producer_head;    // 生产者_头位置
    std::atomic<size_t> m_producer_tail;    // 生产者_尾位置
    std::atomic<size_t> m_consumer_head;    // 消费者_头位置
    std::atomic<size_t> m_consumer_tail;    // 消费者_尾位置
public:
    RingLibrary(size_t size) :
        m_size(size),
        m_task_stack(),
        m_consumer_tail(0),
        m_producer_head(0),
        m_consumer_head(0),
        m_producer_tail(0)
    {
        m_task_stack.resize(size);
    }
    ~RingLibrary()
    {
    }
    bool push(const std::vector<int>& task)
    {
        size_t head, next;
        do
        {
            head = m_producer_head;
            if (head - m_consumer_tail + task.size() > m_size)
                return false;
            next = head + task.size();
        } while (!m_producer_head.compare_exchange_weak(head, next));
        for (size_t i = 0; i < task.size(); i++)
            m_task_stack.at((head + i) % m_size) = task.at(i);
        while (!m_producer_tail.compare_exchange_weak(head, next)) {}
        if (m_producer_head - m_producer_tail > m_size)
            std::cout << "error" << std::endl;
        return true;
    }
    std::vector<int> pop(size_t number = 1)
    {
        std::vector<int> res;
        res.resize(number);
        if (number == 0)
            return std::vector<int>();
        size_t head, next;
        do
        {
            head = m_consumer_head;
            if (head + number > m_producer_tail)
                return std::vector<int>();
            next = head + number;
        } while (!m_consumer_head.compare_exchange_weak(head, next));
        for (size_t i = 0; i < number; i++)
            res.at(i) = m_task_stack.at((head + i) % m_size);
        while (!m_consumer_tail.compare_exchange_weak(head, next)) {};
        return res;
    }
    size_t occupied()
    {
        return m_producer_tail - m_consumer_head;
    }
    size_t unoccupied()
    {
        return m_consumer_tail - m_producer_head + m_size;
    }
};

/*
                                    producer_head
                                    producer_tail
|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
                                consumer_head
            consumer_tail
*/



class Consumer // 消费者
{
private:
public:
    RingLibrary& m_rl;
    std::vector<int> m_count;
    std::atomic<bool> m_life;
    std::thread m_thread;
public:
    Consumer(RingLibrary& rl) :
        m_rl(rl),
        m_count(),
        m_life(true),
        m_thread([&] {
        m_count.resize(N);
        for (size_t i = 0; i < N; i++)
            m_count.at(i) = 0;
        while (m_life)
        {
            std::vector<int> out_task = m_rl.pop();
            for (auto iter : out_task)
                m_count.at(iter)++;
        }
            })
    {

    }
            ~Consumer()
            {
                m_life = false;
                m_thread.join();
            }
};

class Producer // 生产者
{
private:
public:
    RingLibrary& m_rl;
    std::vector<int> m_count;
    std::atomic<bool> m_life;
    std::thread m_thread;
public:
    Producer(RingLibrary& rl) :
        m_rl(rl),
        m_count(),
        m_life(true),
        m_thread([&] {
        m_count.resize(N);
        for (size_t i = 0; i < N; i++)
            m_count.at(i) = 0;
        while (m_life)
        {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            static std::default_random_engine generator;
            static std::uniform_int_distribution<int> distribution(0, N - 1);
            int i = distribution(generator);
            if (distribution(generator) > 0)
            {
                i = 0;
            }
            if (m_rl.push({ i }))
            {
                m_count.at(i)++;
            }
        }
            })
    {

    }
            ~Producer()
            {
                m_life = false;
                m_thread.join();
            }
};

void test()
{

    RingLibrary rl(10); //10

    std::vector<Consumer*> consumers;
    for (size_t i = 0; i < 1; i++) // 4
        consumers.push_back(new Consumer(rl));

    std::vector<Producer*> producers;
    for (size_t i = 0; i < 2; i++) // 8
        producers.push_back(new Producer(rl));



    for (size_t i = 0; i < 100; i++)
    {

        std::cout <<
            "occupied:" << rl.occupied() <<
            "\tunoccupied:" << rl.unoccupied() <<
            "\tproducer(head, tail):" << rl.m_producer_head << ", " << rl.m_producer_tail <<
            "\tconsumer(head, tail):" << rl.m_consumer_head << "，" << rl.m_consumer_tail <<
            "\t1" << std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    }
    for (size_t ii = 0; ii < producers.size(); ii++)
        producers.at(ii)->m_life = false;
    do {
        std::cout <<
            "occupied:" << rl.occupied() <<
            "\tunoccupied:" << rl.unoccupied() <<
            "\tproducer(head, tail):" << rl.m_producer_head << ", " << rl.m_producer_tail <<
            "\tconsumer(head, tail):" << rl.m_consumer_head << "，" << rl.m_consumer_tail <<
            "\t0" << std::endl;
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    } while (rl.occupied() != 0);
    size_t size_producer = 0;
    std::vector<int> count_producer;
    count_producer.resize(N);
    for (size_t i = 0; i < N; i++)
        count_producer.at(i) = 0;
    for (size_t i = 0; i < N; i++)
    {
        for (size_t ii = 0; ii < producers.size(); ii++)
        {
            count_producer.at(i) += producers.at(ii)->m_count.at(i);
            size_producer += producers.at(ii)->m_count.at(i);
        }
    }

    size_t size_consumer = 0;
    std::vector<int> count_consumer;
    count_consumer.resize(N);
    for (size_t i = 0; i < N; i++)
        count_consumer.at(i) = 0;
    for (size_t i = 0; i < N; i++)
    {
        for (size_t ii = 0; ii < consumers.size(); ii++)
        {
            count_consumer.at(i) += consumers.at(ii)->m_count.at(i);
            size_consumer += consumers.at(ii)->m_count.at(i);
        }
    }

    for (size_t ii = 0; ii < producers.size(); ii++)
        delete producers.at(ii);
    producers.clear();
    for (size_t ii = 0; ii < consumers.size(); ii++)
        delete consumers.at(ii);
    consumers.clear();
}

int main()
{
    while (true)
    {
        test();
    }
    return 0;
}



/*
=======================================================================
c = 9 (容量)
C = 10
------||----------------------------||
      ||                            ||
------||----------------------------||
      ||   |0|1|2|3|4|5|6|7|8|9|    ||
      ||              h             ||
空    ||   |-|-|-|-|-|-|-|-|-|-|    || 0  0 -1
      ||              t             || 0  9
      ||   |0|1|2|3|4|5|6|7|8|9|    ||
------||----------------------------||
      ||   |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|    ||
      ||              h                                 ||
满    ||   |*|*|*|*|-|*|*|*|*|*|*|*|*|*|-|-|-|-|-|-|    || -1 1 0
      ||            t                   t               || 9  0
      ||   |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|    || 14-5 = 9 + 1 > 9
------||----------------------------||
      ||   |0|1|2|3|4|5|6|7|8|9|    ||
      ||          h                 ||
区间  ||   |-|-|-|*|*|*|*|*|*|-|    || 6 -6 -7
      ||                      t     || 6  3
      ||   |0|1|2|3|4|5|6|7|8|9|    ||
------||----------------------------||
      ||   |0|1|2|3|4|5|6|7|8|9|    ||
      ||                  h         ||
跨界  ||   |*|*|*|-|-|-|-|*|*|*|    || -4 4 3
      ||          t                 ||  6 3
      ||   |0|1|2|3|4|5|6|7|8|9|    ||
======================================================================

占用  || t-h
剩余  || h-t-1

=======================================================================
      ||   |0|1|2|3|4|5|6|7|8|9|    ||            ||           ||
      ||              h             ||            ||           ||
      ||   |-|-|-|-|-|*|-|-|-|-|    ||            ||           ||
push  ||                t           ||            ||           ||
      ||   |-|-|-|-|-|*|*|*|-|-|    ||            ||           ||
      ||                    t'      ||            ||           ||
      ||   |0|1|2|3|4|5|6|7|8|9|    ||            ||           ||
=======================================================================
      tail

      ||   |0|1|2|3|4|5|6|7|8|9|    ||
      ||              h             ||
满    ||   |*|*|*|*|-|*|*|*|*|*|    ||
      ||            t               ||
      ||   |0|1|2|3|4|5|6|7|8|9|    ||
      ||              h             ||
满    ||   |*|*|*|-|-|*|*|*|*|*|    ||
      ||          t                 ||
      ||   |0|1|2|3|4|5|6|7|8|9|    ||


*/
