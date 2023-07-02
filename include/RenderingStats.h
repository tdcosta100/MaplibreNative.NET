#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    namespace gfx
    {
        struct RenderingStats;
    }
}

namespace DOTNET_NAMESPACE
{
    public ref class RenderingStats : NativeWrapper<mbgl::gfx::RenderingStats>
    {
    public:
        RenderingStats();
        ~RenderingStats();

        property System::Boolean Zero { System::Boolean get(); }
        property System::Int32 NumDrawCalls { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 NumActiveTextures { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 NumCreatedTextures { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 NumBuffers { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 NumFrameBuffers { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 MemTextures { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 MemIndexBuffers { System::Int32 get(); System::Void set(System::Int32 value); }
        property System::Int32 MemVertexBuffers { System::Int32 get(); System::Void set(System::Int32 value); }
    internal:
        RenderingStats(NativePointerHolder<mbgl::gfx::RenderingStats>^ nativePointerHolder);
    };
}
