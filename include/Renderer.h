#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    class Renderer;
}

namespace DOTNET_NAMESPACE
{
    ref class RendererBackend;
    ref class RendererObserver;
    ref class UpdateParameters;

    public ref class Renderer : NativeWrapper<mbgl::Renderer>
    {
    public:
        ~Renderer();

        System::Void MarkContextLost();
        System::Void SetObserver(RendererObserver^ observer);
        System::Void Render(UpdateParameters^ updateParameters);
        System::Void DumpDebugLogs();
        System::Void ReduceMemoryUse();
        System::Void ClearData();
    internal:
        Renderer(NativePointerHolder<mbgl::Renderer>^ nativePointerHolder);
    };
}
