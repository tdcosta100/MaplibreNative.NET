#pragma once
#include "Enums.h"
#include "LatLng.h"
#include "NativeWrapper.h"
#include "Point.h"

namespace mbgl
{
    class TransformState;
    struct TransformStateProperties;
}

namespace DOTNET_NAMESPACE
{
    ref class CameraOptions;
    ref class EdgeInsets;
    ref class FreeCameraOptions;
    ref class Size;
    ref class TileCoordinate;
    ref class UnwrappedTileID;
    ref class Vec3;
    ref class Vec4;
    ref class Mat4;

    using ConstrainMode_ = ConstrainMode;
    using EdgeInsets_ = EdgeInsets;
    using FreeCameraOptions_ = FreeCameraOptions;
    using LatLngBounds_ = LatLngBounds;
    using NorthOrientation_ = NorthOrientation;
    using Size_ = Size;
    using ViewportMode_ = ViewportMode;
    
    public ref class TransformStateProperties : NativeWrapper<mbgl::TransformStateProperties>
    {
    public:
        TransformStateProperties();
        ~TransformStateProperties();

        TransformStateProperties^ WithX(System::Nullable<System::Double> val);
        TransformStateProperties^ WithY(System::Nullable<System::Double> val);
        TransformStateProperties^ WithScale(System::Nullable<System::Double> val);
        TransformStateProperties^ WithBearing(System::Nullable<System::Double> val);
        TransformStateProperties^ WithPitch(System::Nullable<System::Double> val);
        TransformStateProperties^ WithXSkew(System::Nullable<System::Double> val);
        TransformStateProperties^ WithYSkew(System::Nullable<System::Double> val);
        TransformStateProperties^ WithAxonometric(System::Nullable<System::Boolean> val);
        TransformStateProperties^ WithPanningInProgress(System::Nullable<System::Boolean> val);
        TransformStateProperties^ WithScalingInProgress(System::Nullable<System::Boolean> val);
        TransformStateProperties^ WithRotatingInProgress(System::Nullable<System::Boolean> val);
        TransformStateProperties^ WithEdgeInsets(EdgeInsets_^ val);
        TransformStateProperties^ WithSize(Size_^ val);
        TransformStateProperties^ WithConstrainMode(System::Nullable<ConstrainMode> val);
        TransformStateProperties^ WithNorthOrientation(System::Nullable<NorthOrientation_> val);
        TransformStateProperties^ WithViewportMode(System::Nullable<ViewportMode_> val);

        property System::Nullable<System::Double> X { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }
        property System::Nullable<System::Double> Y { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }
        property System::Nullable<System::Double> Bearing { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }
        property System::Nullable<System::Double> Scale { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }
        property System::Nullable<System::Double> Pitch { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }
        property System::Nullable<System::Double> XSkew { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }
        property System::Nullable<System::Double> YSkew { System::Nullable<System::Double> get(); System::Void set(System::Nullable<System::Double> value); }
        property System::Nullable<System::Boolean> Axonometric { System::Nullable<System::Boolean> get(); System::Void set(System::Nullable<System::Boolean> value); }
        property System::Nullable<System::Boolean> Panning { System::Nullable<System::Boolean> get(); System::Void set(System::Nullable<System::Boolean> value); }
        property System::Nullable<System::Boolean> Scaling { System::Nullable<System::Boolean> get(); System::Void set(System::Nullable<System::Boolean> value); }
        property System::Nullable<System::Boolean> Rotating { System::Nullable<System::Boolean> get(); System::Void set(System::Nullable<System::Boolean> value); }
        property EdgeInsets_^ EdgeInsets { EdgeInsets_^ get(); System::Void set(EdgeInsets_^ value); }
        property Size_^ Size { Size_^ get(); System::Void set(Size_^ value); }
        property System::Nullable<ConstrainMode> Constrain { System::Nullable<ConstrainMode> get(); System::Void set(System::Nullable<ConstrainMode> value); }
        property System::Nullable<NorthOrientation_> NorthOrientation { System::Nullable<NorthOrientation_> get(); System::Void set(System::Nullable<NorthOrientation_> value); }
        property System::Nullable<ViewportMode_> ViewPortMode { System::Nullable<ViewportMode_> get(); System::Void set(System::Nullable<ViewportMode_> value); }
    internal:
        TransformStateProperties(NativePointerHolder<mbgl::TransformStateProperties>^ nativePointerHolder);
    };

    public ref class TransformState : NativeWrapper<mbgl::TransformState>
    {
    public:
        TransformState();
        TransformState(ConstrainMode_ constrainMode);
        TransformState(ConstrainMode_ constrainMode, ViewportMode_ viewportMode);
        ~TransformState();

        System::Void SetProperties(TransformStateProperties^ properties);
        System::Void MatrixFor(Mat4^ matrix, UnwrappedTileID^ tileID);
        System::Void GetProjMatrix(Mat4^ projMatrix);
        System::Void GetProjMatrix(Mat4^ projMatrix, System::UInt16 nearZ);
        System::Void GetProjMatrix(Mat4^ projMatrix, System::UInt16 nearZ, System::Boolean aligned);
        CameraOptions^ GetCameraOptions(EdgeInsets_^ padding);
        LatLng^ GetLatLng();
        LatLng^ GetLatLng(LatLng::WrapMode wrapMode);
        System::Void SetRotatingInProgress(System::Boolean val);
        System::Void SetScalingInProgress(System::Boolean val);
        System::Void SetPanningInProgress(System::Boolean val);
        System::Void SetGestureInProgress(System::Boolean val);
        ScreenCoordinate LatLngToScreenCoordinate(LatLng^ latLng);
        ScreenCoordinate LatLngToScreenCoordinate(LatLng^ latLng, Vec4^ p);
        LatLng^ ScreenCoordinateToLatLng(ScreenCoordinate point);
        LatLng^ ScreenCoordinateToLatLng(ScreenCoordinate point, LatLng::WrapMode wrapMode);

        /// <summary>
        /// Implements mapbox-gl-js pointCoordinate() : MercatorCoordinate.
        /// </summary>
        /// <param name="point"></param>
        /// <param name="atZoom"></param>
        /// <returns></returns>
        TileCoordinate^ ScreenCoordinateToTileCoordinate(ScreenCoordinate point, System::Byte atZoom);
        System::Double ZoomScale(System::Double zoom);
        System::Double ScaleZoom(System::Double scale);
        System::Single GetCameraToTileDistance(UnwrappedTileID^ tileID);

        /// <summary>
        /// Recenter the map so that the given coordinate is located at the given point on screen.
        /// </summary>
        /// <param name="latLng"></param>
        /// <param name="anchor"></param>
        /// <returns></returns>
        System::Void MoveLatLng(LatLng^ latLng, ScreenCoordinate anchor);
        System::Void SetLatLngZoom(LatLng^ latLng, System::Double zoom);
        System::Void Constrain(System::Double% scale, System::Double% x, System::Double% y);

        property Size_^ Size { Size_^ get(); System::Void set(Size_^ value); }
        property NorthOrientation_ NorthOrientation { NorthOrientation_ get(); System::Void set(NorthOrientation_ value); }
        property System::Double NorthOrientationAngle { System::Double get(); }
        property ConstrainMode_ ConstrainMode { ConstrainMode_ get(); System::Void set(ConstrainMode_ value); }
        property ViewportMode_ ViewportMode { ViewportMode_ get(); System::Void set(ViewportMode_ value); }
        property EdgeInsets_^ EdgeInsets { EdgeInsets_^ get(); System::Void set(EdgeInsets_^ value); }
        property System::Double PixelX { System::Double get(); }
        property System::Double PixelY { System::Double get(); }
        property System::Double Zoom { System::Double get(); }
        property System::Byte IntegerZoom { System::Byte get(); }
        property System::Double ZoomFraction { System::Double get(); }
        property System::Double Scale { System::Double get(); System::Void set(System::Double value); }
        property System::Double X { System::Double get(); System::Void set(System::Double value); }
        property System::Double Y { System::Double get(); System::Void set(System::Double value); }
        property LatLngBounds_^ LatLngBounds { LatLngBounds_^ get(); System::Void set(LatLngBounds_^ value); }
        property System::Double MinZoom { System::Double get(); System::Void set(System::Double value); }
        property System::Double MaxZoom { System::Double get(); System::Void set(System::Double value); }
        property System::Double MinPitch { System::Double get(); System::Void set(System::Double value); }
        property System::Double MaxPitch { System::Double get(); System::Void set(System::Double value); }
        property System::Double Bearing { System::Double get(); System::Void set(System::Double value); }
        property System::Single FieldOfView { System::Single get(); }
        property System::Single CameraToCenterDistance { System::Single get(); }
        property System::Double Pitch { System::Double get(); System::Void set(System::Double value); }
        property System::Double XSkew { System::Double get(); System::Void set(System::Double value); }
        property System::Double YSkew { System::Double get(); System::Void set(System::Double value); }
        property System::Boolean Axonometric { System::Boolean get(); System::Void set(System::Boolean value); }
        property System::Boolean IsChanging { System::Boolean get(); }
        property System::Boolean IsRotating { System::Boolean get(); }
        property System::Boolean IsScaling { System::Boolean get(); }
        property System::Boolean IsPanning { System::Boolean get(); }
        property System::Boolean IsGestureInProgress { System::Boolean get(); }
        property System::Boolean Valid { System::Boolean get(); }
        property System::Single MaxPitchScaleFactor { System::Single get(); }
        property Mat4^ ProjectionMatrix { Mat4^ get(); }
        property Mat4^ InvProjectionMatrix { Mat4^ get(); }
        property FreeCameraOptions_^ FreeCameraOptions { FreeCameraOptions_^ get(); System::Void set(FreeCameraOptions_^ value); }
    internal:
        TransformState(NativePointerHolder<mbgl::TransformState>^ nativePointerHolder);
    };
}
