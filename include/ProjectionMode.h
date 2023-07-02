#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    struct ProjectionMode;
}

namespace DOTNET_NAMESPACE
{
    /// <summary>
    /// Holds values for Axonometric rendering. All properties are optional.
    /// </summary>
    public ref class ProjectionMode : NativeWrapper<mbgl::ProjectionMode>
    {
    public:
        ProjectionMode();
        ~ProjectionMode();

        ProjectionMode^ WithAxonometric(bool o);
        ProjectionMode^ WithXSkew(double o);
        ProjectionMode^ WithYSkew(double o);

        /// <summary>
        /// Set to <see langword="true"/> to enable axonometric rendering, <see langword="false"/> otherwise.
        /// </summary>
        property System::Nullable<System::Boolean> Axonometric { System::Nullable<System::Boolean> get(); System::Void set(System::Nullable<System::Boolean> value); }

        /// <summary>
        /// The X skew value represents how much to skew on the x-axis.
        /// </summary>
        property System::Nullable<System::Double> XSkew { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }

        /// <summary>
        /// The Y skew value represents how much to skew on the y-axis.
        /// </summary>
        property System::Nullable<System::Double> YSkew { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }
    internal:
        ProjectionMode(NativePointerHolder<mbgl::ProjectionMode>^ nativePointerHolder);
    };
}
