export module Vite.Util.ThreadPool;

import Vite.Base;
import Vite.Logger;

export namespace Hedron {

///
/// @brief Thread Pool
/// @note  This is a very simple implementation of a thread pool, but enough for us.
/// @todo Add a lot of syntactic sugar, priority queue, etc.
///
/// @example: Collect the results
/// auto threadPool = CreateScope<ThreadPool>();
/// auto taskA = pool.Enqueue([]() { return 1; });
/// auto taskB = pool.Enqueue([]() { return 2; });
/// auto result = taskA.get() + taskB.get();
/// std::print("{}", result);
/// 
/// @example: Wait for the result
/// auto threadPool = CreateScope<ThreadPool>();
/// auto task = pool.Enqueue([]() { return 1; });
/// while (task.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready) {
///     std::this_thread::sleep_for(std::chrono::milliseconds(100));
///     std::cout << "Waiting for the result..." << std::endl;
/// }
/// 
///
class ThreadPool {
public:
    // Default
    ThreadPool(size threads = thread::hardware_concurrency()): mStop(false) {
        for (size i = 0; i < threads; i++) {
            mWorkers.emplace_back([this] {
                while (true) {
                    function<void()> task;
                    {
                        std::unique_lock<mutex> lock(this->mQueueMutex);
                        this->mCondition.wait(lock, [this] {
                            return this->mStop || !this->mTasks.empty();
                        });
                        if (this->mStop && this->mTasks.empty()) return;
                        task = std::move(this->mTasks.front());
                        this->mTasks.pop();

                    }
                    task();
                }
            });
        }
    }
    ~ThreadPool() {
        {
            std::unique_lock<mutex>lock(mQueueMutex);
            mStop = true;
        }
        mCondition.notify_all();
        for (auto &worker : mWorkers) {
            worker.join();
        }
    }
    
    ///
    /// @brief Enqueue a task
    /// @tparam <F>:    Any supported callable type.
    /// @tparam <Args>: Any supported argument types.
    ///
    template<typename F, typename ...Args>
    auto Enqueue(F &&f, Args &&...args) -> future<typename std::invoke_result<F, Args...>::type> {
        using return_type = std::invoke_result<F, Args...>::type;
        using result_type = future<return_type>;
        using task_type = packaged_task<return_type()>;

        auto task = std::make_shared<task_type>(
            [f = std::forward<F>(f), ...args = std::forward<Args>(args)]() mutable {
                return f(std::move(args)...);
            }
        );

        result_type resource = task->get_future();
        {
            std::unique_lock<mutex> lock(mQueueMutex);

            while (mTasks.size() >= mMaxTasks && !mStop) {
                LogWarning("Detected ThreadPool overload: Too many tasks enqueued, waiting...\n");
                Log("\tCurrent Limit: {}\n\tCurrent Timeout: {} ms\n", mMaxTasks, mMaxTimeout);
                if (mCondition.wait_for(lock, std::chrono::milliseconds(mMaxTimeout)) == std::cv_status::timeout) {
                    Log("\tTimeout has been reached, consider optimizing your code!\n");
                }
            }

            if (mStop) throw std::runtime_error("Enqueue on stopped thread pool!");
            mTasks.emplace([task]() { (*task)(); });
        }

        mCondition.notify_one();
        return resource;
    }

private:
    // Data
    queue<function<void()>> mTasks;
    vector<thread> mWorkers;

    // Limits
    static constexpr size mMaxTasks = 2048; // ToDo: Find the optimal value
    static constexpr size mMaxTimeout = 4;  // ToDo: Find the optimal value (4 ms = 240 fps)

    // Properties
    bool mStop;
    condition_variable mCondition;
    mutex mQueueMutex;
};

}
