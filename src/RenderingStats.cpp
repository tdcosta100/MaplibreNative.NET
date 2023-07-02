#include "RenderingStats.h"
#include <mbgl/gfx/rendering_stats.hpp>

namespace DOTNET_NAMESPACE
{
    RenderingStats::RenderingStats() : NativeWrapper(new mbgl::gfx::RenderingStats())
    {
    }

    RenderingStats::RenderingStats(NativePointerHolder<mbgl::gfx::RenderingStats>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    RenderingStats::~RenderingStats()
    {
    }

    System::Boolean RenderingStats::Zero::get()
    {
        return NativePointer->isZero();
    }

    System::Int32 RenderingStats::NumDrawCalls::get()
    {
        return NativePointer->numDrawCalls;
    }

    System::Void RenderingStats::NumDrawCalls::set(System::Int32 value)
    {
        NativePointer->numDrawCalls = value;
    }

    System::Int32 RenderingStats::NumActiveTextures::get()
    {
        return NativePointer->numActiveTextures;
    }

    System::Void RenderingStats::NumActiveTextures::set(System::Int32 value)
    {
        NativePointer->numActiveTextures = value;
    }

    System::Int32 RenderingStats::NumCreatedTextures::get()
    {
        return NativePointer->numCreatedTextures;
    }

    System::Void RenderingStats::NumCreatedTextures::set(System::Int32 value)
    {
        NativePointer->numCreatedTextures;
    }

    System::Int32 RenderingStats::NumBuffers::get()
    {
        return NativePointer->numBuffers;
    }

    System::Void RenderingStats::NumBuffers::set(System::Int32 value)
    {
        NativePointer->numBuffers;
    }

    System::Int32 RenderingStats::NumFrameBuffers::get()
    {
        return NativePointer->numFrameBuffers;
    }

    System::Void RenderingStats::NumFrameBuffers::set(System::Int32 value)
    {
        NativePointer->numFrameBuffers;
    }

    System::Int32 RenderingStats::MemTextures::get()
    {
        return NativePointer->memTextures;
    }

    System::Void RenderingStats::MemTextures::set(System::Int32 value)
    {
        NativePointer->memTextures;
    }

    System::Int32 RenderingStats::MemIndexBuffers::get()
    {
        return NativePointer->memIndexBuffers;
    }

    System::Void RenderingStats::MemIndexBuffers::set(System::Int32 value)
    {
        NativePointer->memIndexBuffers;
    }

    System::Int32 RenderingStats::MemVertexBuffers::get()
    {
        return NativePointer->memVertexBuffers;
    }

    System::Void RenderingStats::MemVertexBuffers::set(System::Int32 value)
    {
        NativePointer->memVertexBuffers = value;
    }
}
