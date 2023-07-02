#pragma once
#include <mbgl/util/geometry.hpp>

namespace DOTNET_NAMESPACE
{
    generic <typename T>
    public value struct Point
    {
        Point(T x, T y)
        {
            X = x;
            Y = y;
        }

        Point(mbgl::Point<double>& point)
        {
            X = (T)point.x;
            Y = (T)point.y;
        }

        Point(mbgl::Point<int16_t>& point)
        {
            X = (T)point.x;
            Y = (T)point.y;
        }

        property T X;
        property T Y;
    };

    //using ScreenCoordinate = Point<System::Double>;
    //using TileCoordinatePoint = Point<System::Double>;
    //using GeometryCoordinate = Point<System::Int16>;

    public value struct ScreenCoordinate
    {
        ScreenCoordinate(System::Double x, System::Double y)
        {
            X = x;
            Y = y;
        }

        ScreenCoordinate(mbgl::Point<double>& point)
        {
            X = point.x;
            Y = point.y;
        }

        property System::Double X;
        property System::Double Y;
    };

    public value struct TileCoordinatePoint
    {
        TileCoordinatePoint(System::Double x, System::Double y)
        {
            X = x;
            Y = y;
        }

        TileCoordinatePoint(mbgl::Point<double>& point)
        {
            X = point.x;
            Y = point.y;
        }

        property System::Double X;
        property System::Double Y;
    };

    public value struct GeometryCoordinate
    {
        GeometryCoordinate(System::Int16 x, System::Int16 y)
        {
            X = x;
            Y = y;
        }

        GeometryCoordinate(mbgl::Point<int16_t>& point)
        {
            X = point.x;
            Y = point.y;
        }

        property System::Int16 X;
        property System::Int16 Y;
    };
}
