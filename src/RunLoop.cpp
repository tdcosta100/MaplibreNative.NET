#include "RunLoop.h"

namespace DOTNET_NAMESPACE
{
    RunLoop::RunLoop() : NativeWrapper(new NativeRunLoop())
    {
    }

    RunLoop::RunLoop(Type type) : NativeWrapper(new NativeRunLoop((NativeRunLoop::Type)type))
    {
    }

    RunLoop::~RunLoop()
    {
    }

    System::Void RunLoop::Run()
    {
        NativePointer->Run();
    }

    System::Void RunLoop::RunOnce()
    {
        NativePointer->RunOnce();
    }

    System::Void RunLoop::Stop()
    {
        NativePointer->Stop();
    }
}

#pragma managed(push, off)
#undef _M_CEE
#include <mbgl/util/run_loop.hpp>
#define _M_CEE

namespace DOTNET_NAMESPACE
{
    NativeRunLoop::NativeRunLoop() : NativeRunLoop(Type::New)
    {
    }

    NativeRunLoop::NativeRunLoop(Type type) : _runLoop(std::make_unique<mbgl::util::RunLoop>((mbgl::util::RunLoop::Type)type))
    {
    }

    NativeRunLoop::~NativeRunLoop()
    {
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
}
#pragma managed(pop)
