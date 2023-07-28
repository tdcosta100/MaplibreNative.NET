#include "Convert.h"
#include "RunLoop.h"
#include <mbgl/util/logging.hpp>
#include <msclr/gcroot.h>

namespace
{
    using namespace ::DOTNET_NAMESPACE;
    
    void ManageException(std::function<void()> action)
    {
        try
        {
            action();
        }
        catch (const std::exception& ex)
        {
            mbgl::Log::Error(mbgl::Event::Crash, std::string("Runtime error: ") + ex.what());
        }
        catch (System::Exception^ ex)
        {
            mbgl::Log::Error(mbgl::Event::Crash, std::string("Runtime error: ") + Convert::ToStdString(ex->Message));
        }
    }

    void SystemActionHelper(
        msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^> taskCompletionSource,
        msclr::gcroot<System::Action^> action
    )
    {
        action->Invoke();
        taskCompletionSource->SetResult(true);
    }
}

namespace DOTNET_NAMESPACE
{
    RunLoop::RunLoop() : NativeWrapper(new NativeRunLoop())
    {
        RegisterInThread();

        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &RunLoop::RegisterInThread))
            )
        );

        taskCompletionSource->Task->Wait();
    }

    RunLoop::RunLoop(Type type) : NativeWrapper(new NativeRunLoop((NativeRunLoop::Type)type))
    {
        RegisterInThread();

        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &RunLoop::RegisterInThread))
            )
        );

        taskCompletionSource->Task->Wait();
    }

    RunLoop::~RunLoop()
    {
        delete PointerHolder;
    }

    System::Void RunLoop::Run()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();
        
        NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &RunLoop::RunInThread))
            )
        );
        
        taskCompletionSource->Task->Wait();
    }

    System::Void RunLoop::RunOnce()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &RunLoop::RunOnceInThread))
            )
        );
        
        taskCompletionSource->Task->Wait();
    }

    System::Void RunLoop::Stop()
    {
        System::Threading::Tasks::TaskCompletionSource<System::Boolean>^ taskCompletionSource = gcnew System::Threading::Tasks::TaskCompletionSource<System::Boolean>();

        NativePointer->ExecuteInThread(
            std::bind(
                &SystemActionHelper,
                msclr::gcroot<System::Threading::Tasks::TaskCompletionSource<System::Boolean>^>(taskCompletionSource),
                msclr::gcroot<System::Action^>(gcnew System::Action(this, &RunLoop::StopInThread))
            )
        );

        taskCompletionSource->Task->Wait();
    }

    RunLoop^ RunLoop::Get()
    {
        return _ThreadLocal->Value;
    }

    System::Void RunLoop::RegisterInThread()
    {
        _ThreadLocal->Value = this;
    }

    System::Void RunLoop::RunInThread()
    {
        NativePointer->Run();
    }

    System::Void RunLoop::RunOnceInThread()
    {
        NativePointer->RunOnce();
    }

    System::Void RunLoop::StopInThread()
    {
        NativePointer->Stop();
    }
}

#pragma managed(push, off)
#undef _M_CEE
#include <mbgl/util/logging.hpp>
#include <mbgl/util/run_loop.hpp>
#define _M_CEE
#include <thread>

namespace DOTNET_NAMESPACE
{
    class ThreadID
    {
    public:
        ThreadID()
        {
            id = std::this_thread::get_id();
        }

        std::thread::id id;
    };

    NativeRunLoop::NativeRunLoop() : NativeRunLoop(Type::New)
    {
    }

    NativeRunLoop::NativeRunLoop(Type type)
        :
        _StopProcessingQueue(false),
        _mutex(std::make_unique<std::mutex>()),
        _condition_variable(std::make_unique<std::condition_variable>()),
        _actionQueue(std::make_unique<std::queue<std::function<void()>>>())
    {
        _processActionQueueThread = std::make_unique<std::thread>([this, &type] {
            std::unique_lock<std::mutex> lock(*_mutex);
            _tid = std::make_unique<ThreadID>(ThreadID());
            _runLoop = std::make_unique<mbgl::util::RunLoop>((mbgl::util::RunLoop::Type)type);
            lock.unlock();
            _condition_variable->notify_all();

            ProcessActionQueue();

            _runLoop.reset();
        });

        std::unique_lock<std::mutex> lock(*_mutex);
        _condition_variable->wait(lock, [this] { return static_cast<bool>(_runLoop); });
        lock.unlock();
    }

    NativeRunLoop::~NativeRunLoop()
    {
        {
            std::lock_guard<std::mutex> guard(*_mutex);
            _StopProcessingQueue = true;
        }

        _condition_variable->notify_all();
        _processActionQueueThread->join();
    }

    void NativeRunLoop::Run()
    {
        _runLoop->run();
    }

    void NativeRunLoop::RunOnce()
    {
        _runLoop->runOnce();
    }

    void NativeRunLoop::Stop()
    {
        _runLoop->stop();
    }

    void NativeRunLoop::ExecuteInThread(std::function<void()> action)
    {
        if (_tid->id == std::this_thread::get_id())
        {
            ManageException(action);
        }
        else
        {
            {
                std::lock_guard<std::mutex> guard(*_mutex);
                _actionQueue->push(std::bind(&ManageException, action));
            }

            _condition_variable->notify_all();
        }
    }

    void NativeRunLoop::ProcessActionQueue()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(*_mutex);
            _condition_variable->wait(lock, [this] { return _StopProcessingQueue || _actionQueue->size() > 0; });

            if (_StopProcessingQueue)
            {
                lock.unlock();
                break;
            }
            
            std::function<void()> action = _actionQueue->front();
            _actionQueue->pop();
            lock.unlock();

            _condition_variable->notify_all();

            action();
        }
    }
}
#pragma managed(pop)
