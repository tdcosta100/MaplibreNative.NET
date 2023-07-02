#pragma once
#include "NativeWrapper.h"
#include <algorithm>
#include <msclr/gcroot.h>

namespace mbgl
{
    struct AnimationOptions;
}

namespace DOTNET_NAMESPACE
{
    ref class UnitBezier;

    public delegate void TransitionFrameFunction(System::Double t);
    public delegate void TransitionFinishFunction();

    using TransitionFrameFunction_ = TransitionFrameFunction;
    using TransitionFinishFunction_ = TransitionFinishFunction;
    
    class NativeTransitionFunctionsHelper
    {
    public:
        void NativeTransitionFrameFunction(double t);
        void NativeTransitionFinishFunction();

        msclr::gcroot<TransitionFrameFunction_^> ManagedTransitionFrameFunction;
        msclr::gcroot<TransitionFinishFunction_^> ManagedTransitionFinishFunction;
    };

    /// <summary>
    /// Various options for describing a transition between viewpoints with
    /// animation. All properties are optional; the default values depend on how this
    /// struct is used.
    /// </summary>
    public ref class AnimationOptions : NativeWrapper<mbgl::AnimationOptions>
    {
    public:
        /// <summary>
        /// Creates an animation with no options specified.
        /// </summary>
        AnimationOptions();

        /// <summary>
        /// Creates an animation with the specified duration.
        /// </summary>
        /// <param name="d"></param>
        AnimationOptions(System::TimeSpan d);
        ~AnimationOptions();

        /// <summary>
        /// Time to animate to the viewpoint defined herein.
        /// </summary>
        property System::Nullable<System::TimeSpan> Duration { System::Nullable<System::TimeSpan> get(); System::Void set(System::Nullable<System::TimeSpan> value); }

        /// <summary>
        /// Average velocity of a flyTo() transition, measured in screenfuls per
        /// second, assuming a linear timing curve.
        /// 
        /// A <i>screenful</i> is the visible span in pixels. It does not correspond
        /// to a fixed physical distance but rather varies by zoom level.
        /// </summary>
        property System::Nullable<System::Double> Velocity { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }

        /// <summary>
        /// Zero-based zoom level at the peak of the flyTo() transition’s flight
        /// path.
        /// </summary>
        property System::Nullable<System::Double> MinZoom { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }

        /// <summary>
        /// The easing timing curve of the transition.
        /// </summary>
        property UnitBezier^ Easing { UnitBezier^ get(); System::Void set(UnitBezier^ value); }

        /// <summary>
        /// A function that is called on each frame of the transition, just before a
        /// screen update, except on the last frame. The first parameter indicates
        /// the elapsed time as a percentage of the duration.
        /// </summary>
        property TransitionFrameFunction^ TransitionFrameFn { TransitionFrameFunction^ get(); System::Void set(TransitionFrameFunction^ value); }

        /// <summary>
        /// A function that is called once on the last frame of the transition, just
        /// before the corresponding screen update.
        /// </summary>
        property TransitionFinishFunction^ TransitionFinishFn { TransitionFinishFunction^ get(); System::Void set(TransitionFinishFunction^ value); }
    internal:
        AnimationOptions(NativePointerHolder<mbgl::AnimationOptions>^ nativePointerHolder);
    private:
        NativeTransitionFunctionsHelper* _TransitionFunctionsHelper = new NativeTransitionFunctionsHelper();
    };
}
