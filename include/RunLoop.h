#pragma once
#include "NativeWrapper.h"
#include <memory>

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

    private:
        std::unique_ptr<mbgl::util::RunLoop> _runLoop;
    };
}
