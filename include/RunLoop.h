#pragma once
#include "NativeWrapper.h"
#include <functional>
#include <memory>
#include <queue>

namespace std
{
    class condition_variable;
    class mutex;
    class thread;
}

namespace mbgl
{
    namespace util
    {
        class RunLoop;
    }
}

namespace DOTNET_NAMESPACE
{
    class NativeRunLoop;
    class ThreadID;

    public ref class RunLoop : NativeWrapper<NativeRunLoop>
    {
    public:
        enum class Type : System::Byte
        {
            Default,
            New,
        };

        RunLoop();
        RunLoop(Type type);
        ~RunLoop();

        System::Void Run();
        System::Void RunOnce();
        System::Void Stop();

        static RunLoop^ Get();
    private:
        static System::Threading::ThreadLocal<RunLoop^>^ _ThreadLocal = gcnew System::Threading::ThreadLocal<RunLoop^>();

        System::Void RegisterInThread();
        System::Void RunInThread();
        System::Void RunOnceInThread();
        System::Void StopInThread();
    };

    class NativeRunLoop
    {
    public:
        enum class Type : uint8_t
        {
            Default,
            New,
        };

        NativeRunLoop();
        NativeRunLoop(Type type);
        ~NativeRunLoop();

        void Run();
        void RunOnce();
        void Stop();
        void ExecuteInThread(std::function<void()> action);
    private:
        void ProcessActionQueue();

        bool _StopProcessingQueue;
        std::unique_ptr<ThreadID> _tid;
        std::unique_ptr<std::mutex> _mutex;
        std::unique_ptr<std::condition_variable> _condition_variable;
        std::unique_ptr<std::thread> _processActionQueueThread;
        std::unique_ptr<std::queue<std::function<void()>>> _actionQueue;
        std::unique_ptr<mbgl::util::RunLoop> _runLoop;
    };
}
