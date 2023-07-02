#include "AnimationOptions.h"
#include "Convert.h"
#include "UnitBezier.h"
#include <mbgl/map/camera.hpp>

namespace DOTNET_NAMESPACE
{
    AnimationOptions::AnimationOptions() : NativeWrapper(new mbgl::AnimationOptions())
    {
    }

    AnimationOptions::AnimationOptions(System::TimeSpan d) : NativeWrapper(new mbgl::AnimationOptions(Convert::ToDuration<mbgl::Duration>(d)))
    {
    }

    AnimationOptions::AnimationOptions(NativePointerHolder<mbgl::AnimationOptions>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    AnimationOptions::~AnimationOptions()
    {
    }

    System::Nullable<System::TimeSpan> AnimationOptions::Duration::get()
    {
        if (NativePointer->duration.has_value())
        {
            return System::Nullable<System::TimeSpan>(Convert::ToSystemTimeSpan(NativePointer->duration.value()));
        }

        return System::Nullable<System::TimeSpan>();
    }

    System::Void AnimationOptions::Duration::set(System::Nullable<System::TimeSpan> value)
    {
        if (value.HasValue)
        {
            NativePointer->duration = Convert::ToDuration<mbgl::Duration>(value.Value);
        }
        else
        {
            NativePointer->duration = std::nullopt;
        }
    }

    System::Nullable<System::Double> AnimationOptions::Velocity::get()
    {
        if (NativePointer->velocity.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->velocity.value());
        }
        
        return System::Nullable<System::Double>();
    }

    System::Void AnimationOptions::Velocity::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->velocity = value.Value;
        }
        else
        {
            NativePointer->velocity = std::nullopt;
        }
    }

    System::Nullable<System::Double> AnimationOptions::MinZoom::get()
    {
        if (NativePointer->minZoom.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->minZoom.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void AnimationOptions::MinZoom::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->minZoom = value.Value;
        }
        else
        {
            NativePointer->minZoom = std::nullopt;
        }
    }

    UnitBezier^ AnimationOptions::Easing::get()
    {
        if (NativePointer->easing.has_value())
        {
            return gcnew UnitBezier(UnitBezier::CreateNativePointerHolder(NativePointer->easing.value()));
        }

        return nullptr;
    }

    System::Void AnimationOptions::Easing::set(UnitBezier^ value)
    {
        if (value)
        {
            NativePointer->easing.emplace(*value->NativePointer);
        }
        else
        {
            NativePointer->easing = std::nullopt;
        }
    }

    TransitionFrameFunction_^ AnimationOptions::TransitionFrameFn::get()
    {
        if (static_cast<TransitionFrameFunction_^>(_TransitionFunctionsHelper->ManagedTransitionFrameFunction))
        {
            return _TransitionFunctionsHelper->ManagedTransitionFrameFunction;
        }

        return nullptr;
    }

    System::Void AnimationOptions::TransitionFrameFn::set(TransitionFrameFunction_^ value)
    {
        if (value)
        {
            _TransitionFunctionsHelper->ManagedTransitionFrameFunction = value;
            NativePointer->transitionFrameFn = std::bind(&NativeTransitionFunctionsHelper::NativeTransitionFrameFunction, *_TransitionFunctionsHelper, std::placeholders::_1);
        }
        else
        {
            _TransitionFunctionsHelper->ManagedTransitionFrameFunction = nullptr;
            NativePointer->transitionFrameFn = nullptr;
        }
    }

    TransitionFinishFunction_^ AnimationOptions::TransitionFinishFn::get()
    {
        if (static_cast<TransitionFinishFunction_^>(_TransitionFunctionsHelper->ManagedTransitionFinishFunction))
        {
            return _TransitionFunctionsHelper->ManagedTransitionFinishFunction;
        }

        return nullptr;
    }

    System::Void AnimationOptions::TransitionFinishFn::set(TransitionFinishFunction^ value)
    {
        if (value)
        {
            _TransitionFunctionsHelper->ManagedTransitionFinishFunction = value;
            NativePointer->transitionFinishFn = std::bind(&NativeTransitionFunctionsHelper::NativeTransitionFinishFunction, *_TransitionFunctionsHelper);
        }
        else
        {
            _TransitionFunctionsHelper->ManagedTransitionFinishFunction = nullptr;
            NativePointer->transitionFinishFn = nullptr;
        }
    }

    void NativeTransitionFunctionsHelper::NativeTransitionFrameFunction(double t)
    {
        if (static_cast<TransitionFrameFunction_^>(ManagedTransitionFrameFunction))
        {
            ManagedTransitionFrameFunction->Invoke(t);
        }
    }

    void NativeTransitionFunctionsHelper::NativeTransitionFinishFunction()
    {
        if (static_cast<TransitionFinishFunction_^>(ManagedTransitionFinishFunction))
        {
            ManagedTransitionFinishFunction->Invoke();
        }
    }
}
