#pragma once
#include <mbgl/util/geometry.hpp>

namespace DOTNET_NAMESPACE
{
    public value struct PointDouble
    {
        PointDouble(System::Double x, System::Double y)
        {
            X = x;
            Y = y;
        }

        PointDouble(mbgl::Point<double>& point)
        {
            X = point.x;
            Y = point.y;
        }

        virtual System::String^ ToString() override
        {
            return System::String::Format("{0},{1}", X, Y);
        }

        property System::Double X;
        property System::Double Y;

        static PointDouble operator+(PointDouble lhs, PointDouble rhs)
        {
            return PointDouble(lhs.X + rhs.X, lhs.Y + rhs.Y);
        }

        static PointDouble operator+(PointDouble lhs, System::Double rhs)
        {
            return PointDouble(lhs.X + rhs, lhs.Y + rhs);
        }

        static PointDouble operator-(PointDouble lhs, PointDouble rhs)
        {
            return PointDouble(lhs.X - rhs.X, lhs.Y - rhs.Y);
        }

        static PointDouble operator-(PointDouble lhs, System::Double rhs)
        {
            return PointDouble(lhs.X - rhs, lhs.Y - rhs);
        }

        static PointDouble operator*(PointDouble lhs, PointDouble rhs)
        {
            return PointDouble(lhs.X * rhs.X, lhs.Y * rhs.Y);
        }

        static PointDouble operator*(PointDouble lhs, System::Double rhs)
        {
            return PointDouble(lhs.X * rhs, lhs.Y * rhs);
        }

        static PointDouble operator/(PointDouble lhs, PointDouble rhs)
        {
            return PointDouble(lhs.X / rhs.X, lhs.Y / rhs.Y);
        }

        static PointDouble operator/(PointDouble lhs, System::Double rhs)
        {
            return PointDouble(lhs.X / rhs, lhs.Y / rhs);
        }

        static PointDouble operator+=(PointDouble lhs, PointDouble rhs)
        {
            lhs.X += rhs.X;
            lhs.Y += rhs.Y;
            return lhs;
        }

        static PointDouble operator+=(PointDouble lhs, System::Double rhs)
        {
            lhs.X += rhs;
            lhs.Y += rhs;
            return lhs;
        }

        static PointDouble operator-=(PointDouble lhs, PointDouble rhs)
        {
            lhs.X -= rhs.X;
            lhs.Y -= rhs.Y;
            return lhs;
        }

        static PointDouble operator-=(PointDouble lhs, System::Double rhs)
        {
            lhs.X -= rhs;
            lhs.Y -= rhs;
            return lhs;
        }

        static PointDouble operator*=(PointDouble lhs, PointDouble rhs)
        {
            lhs.X *= rhs.X;
            lhs.Y *= rhs.Y;
            return lhs;
        }

        static PointDouble operator*=(PointDouble lhs, System::Double rhs)
        {
            lhs.X *= rhs;
            lhs.Y *= rhs;
            return lhs;
        }

        static PointDouble operator/=(PointDouble lhs, PointDouble rhs)
        {
            lhs.X /= rhs.X;
            lhs.Y /= rhs.Y;
            return lhs;
        }

        static PointDouble operator/=(PointDouble lhs, System::Double rhs)
        {
            lhs.X /= rhs;
            lhs.Y /= rhs;
            return lhs;
        }
    };

    public value struct PointShort
    {
        PointShort(System::Int16 x, System::Int16 y)
        {
            X = x;
            Y = y;
        }

        PointShort(mbgl::Point<int16_t>& point)
        {
            X = point.x;
            Y = point.y;
        }

        property System::Int16 X;
        property System::Int16 Y;

        virtual System::String^ ToString() override
        {
            return System::String::Format("{0},{1}", X, Y);
        }

        static PointShort operator+(PointShort lhs, PointShort rhs)
        {
            return PointShort(lhs.X + rhs.X, lhs.Y + rhs.Y);
        }

        static PointShort operator+(PointShort lhs, System::Int16 rhs)
        {
            return PointShort(lhs.X + rhs, lhs.Y + rhs);
        }

        static PointShort operator-(PointShort lhs, PointShort rhs)
        {
            return PointShort(lhs.X - rhs.X, lhs.Y - rhs.Y);
        }

        static PointShort operator-(PointShort lhs, System::Int16 rhs)
        {
            return PointShort(lhs.X - rhs, lhs.Y - rhs);
        }

        static PointShort operator*(PointShort lhs, PointShort rhs)
        {
            return PointShort(lhs.X * rhs.X, lhs.Y * rhs.Y);
        }

        static PointShort operator*(PointShort lhs, System::Int16 rhs)
        {
            return PointShort(lhs.X * rhs, lhs.Y * rhs);
        }

        static PointShort operator/(PointShort lhs, PointShort rhs)
        {
            return PointShort(lhs.X / rhs.X, lhs.Y / rhs.Y);
        }

        static PointShort operator/(PointShort lhs, System::Int16 rhs)
        {
            return PointShort(lhs.X / rhs, lhs.Y / rhs);
        }

        static PointShort operator+=(PointShort lhs, PointShort rhs)
        {
            lhs.X += rhs.X;
            lhs.Y += rhs.Y;
            return lhs;
        }

        static PointShort operator+=(PointShort lhs, System::Int16 rhs)
        {
            lhs.X += rhs;
            lhs.Y += rhs;
            return lhs;
        }

        static PointShort operator-=(PointShort lhs, PointShort rhs)
        {
            lhs.X -= rhs.X;
            lhs.Y -= rhs.Y;
            return lhs;
        }

        static PointShort operator-=(PointShort lhs, System::Int16 rhs)
        {
            lhs.X -= rhs;
            lhs.Y -= rhs;
            return lhs;
        }

        static PointShort operator*=(PointShort lhs, PointShort rhs)
        {
            lhs.X *= rhs.X;
            lhs.Y *= rhs.Y;
            return lhs;
        }

        static PointShort operator*=(PointShort lhs, System::Int16 rhs)
        {
            lhs.X *= rhs;
            lhs.Y *= rhs;
            return lhs;
        }

        static PointShort operator/=(PointShort lhs, PointShort rhs)
        {
            lhs.X /= rhs.X;
            lhs.Y /= rhs.Y;
            return lhs;
        }

        static PointShort operator/=(PointShort lhs, System::Int16 rhs)
        {
            lhs.X /= rhs;
            lhs.Y /= rhs;
            return lhs;
        }
    };

    public value struct PointUInt
    {
        PointUInt(System::UInt32 x, System::UInt32 y)
        {
            X = x;
            Y = y;
        }

        PointUInt(mbgl::Point<uint32_t>& point)
        {
            X = point.x;
            Y = point.y;
        }

        property System::UInt32 X;
        property System::UInt32 Y;

        virtual System::String^ ToString() override
        {
            return System::String::Format("{0},{1}", X, Y);
        }

        static PointUInt operator+(PointUInt lhs, PointUInt rhs)
        {
            return PointUInt(lhs.X + rhs.X, lhs.Y + rhs.Y);
        }

        static PointUInt operator+(PointUInt lhs, System::UInt32 rhs)
        {
            return PointUInt(lhs.X + rhs, lhs.Y + rhs);
        }

        static PointUInt operator-(PointUInt lhs, PointUInt rhs)
        {
            return PointUInt(lhs.X - rhs.X, lhs.Y - rhs.Y);
        }

        static PointUInt operator-(PointUInt lhs, System::UInt32 rhs)
        {
            return PointUInt(lhs.X - rhs, lhs.Y - rhs);
        }

        static PointUInt operator*(PointUInt lhs, PointUInt rhs)
        {
            return PointUInt(lhs.X * rhs.X, lhs.Y * rhs.Y);
        }

        static PointUInt operator*(PointUInt lhs, System::UInt32 rhs)
        {
            return PointUInt(lhs.X * rhs, lhs.Y * rhs);
        }

        static PointUInt operator/(PointUInt lhs, PointUInt rhs)
        {
            return PointUInt(lhs.X / rhs.X, lhs.Y / rhs.Y);
        }

        static PointUInt operator/(PointUInt lhs, System::UInt32 rhs)
        {
            return PointUInt(lhs.X / rhs, lhs.Y / rhs);
        }

        static PointUInt operator+=(PointUInt lhs, PointUInt rhs)
        {
            lhs.X += rhs.X;
            lhs.Y += rhs.Y;
            return lhs;
        }

        static PointUInt operator+=(PointUInt lhs, System::UInt32 rhs)
        {
            lhs.X += rhs;
            lhs.Y += rhs;
            return lhs;
        }

        static PointUInt operator-=(PointUInt lhs, PointUInt rhs)
        {
            lhs.X -= rhs.X;
            lhs.Y -= rhs.Y;
            return lhs;
        }

        static PointUInt operator-=(PointUInt lhs, System::UInt32 rhs)
        {
            lhs.X -= rhs;
            lhs.Y -= rhs;
            return lhs;
        }

        static PointUInt operator*=(PointUInt lhs, PointUInt rhs)
        {
            lhs.X *= rhs.X;
            lhs.Y *= rhs.Y;
            return lhs;
        }

        static PointUInt operator*=(PointUInt lhs, System::UInt32 rhs)
        {
            lhs.X *= rhs;
            lhs.Y *= rhs;
            return lhs;
        }

        static PointUInt operator/=(PointUInt lhs, PointUInt rhs)
        {
            lhs.X /= rhs.X;
            lhs.Y /= rhs.Y;
            return lhs;
        }

        static PointUInt operator/=(PointUInt lhs, System::UInt32 rhs)
        {
            lhs.X /= rhs;
            lhs.Y /= rhs;
            return lhs;
        }
    };


    typedef PointDouble ScreenCoordinate;
    typedef PointDouble TileCoordinatePoint;
    typedef PointShort GeometryCoordinate;
}
