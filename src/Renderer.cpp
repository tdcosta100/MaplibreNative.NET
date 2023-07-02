#include "Renderer.h"
#include "RendererObserver.h"
#include "UpdateParameters.h"
#include <mbgl/renderer/renderer.hpp>

namespace DOTNET_NAMESPACE
{
    Renderer::Renderer(NativePointerHolder<mbgl::Renderer>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    Renderer::~Renderer()
    {
    }

    System::Void Renderer::MarkContextLost()
    {
        NativePointer->markContextLost();
    }

    System::Void Renderer::SetObserver(RendererObserver^ observer)
    {
        NativePointer->setObserver(observer->NativePointer);
    }

    System::Void Renderer::Render(UpdateParameters^ updateParameters)
    {
        NativePointer->render(*updateParameters->NativePointer);
    }

    System::Void Renderer::DumpDebugLogs()
    {
        NativePointer->dumpDebugLogs();
    }

    System::Void Renderer::ReduceMemoryUse()
    {
        NativePointer->reduceMemoryUse();
    }

    System::Void Renderer::ClearData()
    {
        NativePointer->clearData();
    }
}
