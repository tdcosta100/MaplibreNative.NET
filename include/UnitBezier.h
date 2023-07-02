#pragma once
#include "NativeWrapper.h"

namespace mbgl
{
    namespace util
    {
        struct UnitBezier;
    }
}

namespace DOTNET_NAMESPACE
{
    public ref class UnitBezier : NativeWrapper<mbgl::util::UnitBezier>
    {
    public:
        /// <summary>
        /// Calculate the polynomial coefficients, implicit first and last control points are (0,0) and (1,1).
        /// </summary>
        /// <param name="p1x"></param>
        /// <param name="p1y"></param>
        /// <param name="p2x"></param>
        /// <param name="p2y"></param>
        UnitBezier(System::Double p1x, System::Double p1y, System::Double p2x, System::Double p2y);
        ~UnitBezier();

        System::ValueTuple<System::Double, System::Double> GetP1();
        System::ValueTuple<System::Double, System::Double> GetP2();
        System::Double SampleCurveX(System::Double t);
        System::Double SampleCurveY(System::Double t);
        System::Double SampleCurveDerivativeX(System::Double t);
        System::Double SolveCurveX(System::Double x, System::Double epsilon);
        System::Double Solve(System::Double x, System::Double epsilon);

        System::Boolean operator==(UnitBezier^ rhs);
    internal:
        UnitBezier(NativePointerHolder<mbgl::util::UnitBezier>^ nativePointerHolder);
    };
}
