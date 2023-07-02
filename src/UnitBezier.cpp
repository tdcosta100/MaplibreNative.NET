#include "UnitBezier.h"
#include <mbgl/util/unitbezier.hpp>

namespace DOTNET_NAMESPACE
{
    UnitBezier::UnitBezier(System::Double p1x, System::Double p1y, System::Double p2x, System::Double p2y)
        : NativeWrapper(new mbgl::util::UnitBezier(p1x, p1y, p2x, p2y))
    {
    }

    UnitBezier::UnitBezier(NativePointerHolder<mbgl::util::UnitBezier>^ nativePointerHolder)
        : NativeWrapper(nativePointerHolder)
    {
    }

    UnitBezier::~UnitBezier()
    {
    }

    System::ValueTuple<System::Double, System::Double> UnitBezier::GetP1()
    {
        return System::ValueTuple<System::Double, System::Double>(NativePointer->getP1().first, NativePointer->getP1().second);
    }

    System::ValueTuple<System::Double, System::Double> UnitBezier::GetP2()
    {
        return System::ValueTuple<System::Double, System::Double>(NativePointer->getP2().first, NativePointer->getP2().second);
    }

    System::Double UnitBezier::SampleCurveX(System::Double t)
    {
        return NativePointer->sampleCurveX(t);
    }

    System::Double UnitBezier::SampleCurveY(System::Double t)
    {
        return NativePointer->sampleCurveY(t);
    }

    System::Double UnitBezier::SampleCurveDerivativeX(System::Double t)
    {
        return NativePointer->sampleCurveDerivativeX(t);
    }

    System::Double UnitBezier::SolveCurveX(System::Double x, System::Double epsilon)
    {
        return NativePointer->solveCurveX(x, epsilon);
    }

    System::Double UnitBezier::Solve(System::Double x, System::Double epsilon)
    {
        return NativePointer->solve(x, epsilon);
    }

    System::Boolean UnitBezier::operator==(UnitBezier^ rhs)
    {
        return *NativePointer == *rhs->NativePointer;
    }
}
