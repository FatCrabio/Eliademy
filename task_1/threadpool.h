#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <future>

class ThreadPool {
       public:
       ThreadPool(unsigned num_threads = std::thread::hardware_concurrency()) {
           while (num_threads--) {
               m_threads.emplace_back([this] {
                   while(true) {
                       std::unique_lock<std::mutex> lock(m_mutex);
                       m_condVariable.wait(lock, [this] {return !m_tasksQueue.empty();});
                       auto task = std::move(m_tasksQueue.front());
                       if (task.valid()) {
                           m_tasksQueue.pop();
                           lock.unlock();
						   
                           task();
                       } else {
                           break;
                       }
                   }
               });
           }
       }

       template<typename F, typename R = std::result_of_t<F&&()>>
       std::future<R> run(F&& f) const {
           auto task = std::packaged_task<R()>(std::forward<F>(f));
           auto future = task.get_future();
           {
               std::unique_lock<std::mutex> lock(m_mutex);
               m_tasksQueue.push(std::packaged_task<void()>(std::move(task)));
           }
           m_condVariable.notify_one();
           return future;
       }

       ~ThreadPool() {
           {
               std::unique_lock<std::mutex> lock(m_mutex);
               m_tasksQueue.push({});
           }
           m_condVariable.notify_all();
           for (auto& thread : m_threads) {
               thread.join();
           }
       }

       private:
       std::vector<std::thread> m_threads;
       mutable std::queue<std::packaged_task<void()>> m_tasksQueue;
       mutable std::mutex m_mutex;
       mutable std::condition_variable m_condVariable;
};
#endif // THREADPOOL_H
