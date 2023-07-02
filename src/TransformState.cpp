#include "CameraOptions.h"
#include "FreeCameraOptions.h"
#include "EdgeInsets.h"
#include "LatLng.h"
#include "Size.h"
#include "TileCoordinate.h"
#include "TransformState.h"
#include "UnwrappedTileID.h"
#include "Vector.h"
#include <mbgl/map/transform_state.hpp>
#include <mbgl/util/tile_coordinate.hpp>

namespace DOTNET_NAMESPACE
{
    TransformStateProperties::TransformStateProperties() : NativeWrapper(new mbgl::TransformStateProperties())
    {
    }

    TransformStateProperties::TransformStateProperties(NativePointerHolder<mbgl::TransformStateProperties>^ nativePointerHolder) : NativeWrapper(nativePointerHolder)
    {
    }

    TransformStateProperties::~TransformStateProperties()
    {
    }

    TransformStateProperties^ TransformStateProperties::WithX(System::Nullable<System::Double> val)
    {
        if (val.HasValue)
        {
            NativePointer->withX(val.Value);
        }
        else
        {
            NativePointer->withX(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithY(System::Nullable<System::Double> val)
    {
        if (val.HasValue)
        {
            NativePointer->withY(val.Value);
        }
        else
        {
            NativePointer->withY(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithScale(System::Nullable<System::Double> val)
    {
        if (val.HasValue)
        {
            NativePointer->withScale(val.Value);
        }
        else
        {
            NativePointer->withScale(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithBearing(System::Nullable<System::Double> val)
    {
        if (val.HasValue)
        {
            NativePointer->withBearing(val.Value);
        }
        else
        {
            NativePointer->withBearing(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithPitch(System::Nullable<System::Double> val)
    {
        if (val.HasValue)
        {
            NativePointer->withPitch(val.Value);
        }
        else
        {
            NativePointer->withPitch(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithXSkew(System::Nullable<System::Double> val)
    {
        if (val.HasValue)
        {
            NativePointer->withXSkew(val.Value);
        }
        else
        {
            NativePointer->withXSkew(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithYSkew(System::Nullable<System::Double> val)
    {
        if (val.HasValue)
        {
            NativePointer->withYSkew(val.Value);
        }
        else
        {
            NativePointer->withYSkew(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithAxonometric(System::Nullable<System::Boolean> val)
    {
        if (val.HasValue)
        {
            NativePointer->withAxonometric(val.Value);
        }
        else
        {
            NativePointer->withAxonometric(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithPanningInProgress(System::Nullable<System::Boolean> val)
    {
        if (val.HasValue)
        {
            NativePointer->withPanningInProgress(val.Value);
        }
        else
        {
            NativePointer->withPanningInProgress(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithScalingInProgress(System::Nullable<System::Boolean> val)
    {
        if (val.HasValue)
        {
            NativePointer->withScalingInProgress(val.Value);
        }
        else
        {
            NativePointer->withScalingInProgress(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithRotatingInProgress(System::Nullable<System::Boolean> val)
    {
        if (val.HasValue)
        {
            NativePointer->withY(val.Value);
        }
        else
        {
            NativePointer->withY(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithEdgeInsets(EdgeInsets_^ val)
    {
        if (val)
        {
            NativePointer->withEdgeInsets(*val->NativePointer);
        }
        else
        {
            NativePointer->withEdgeInsets(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithSize(Size_^ val)
    {
        if (val)
        {
            NativePointer->withSize(*val->NativePointer);
        }
        else
        {
            NativePointer->withSize(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithConstrainMode(System::Nullable<ConstrainMode> val)
    {
        if (val.HasValue)
        {
            NativePointer->withConstrainMode((mbgl::ConstrainMode)val.Value);
        }
        else
        {
            NativePointer->withConstrainMode(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithNorthOrientation(System::Nullable<NorthOrientation_> val)
    {
        if (val.HasValue)
        {
            NativePointer->withNorthOrientation((mbgl::NorthOrientation)val.Value);
        }
        else
        {
            NativePointer->withNorthOrientation(std::nullopt);
        }

        return this;
    }

    TransformStateProperties^ TransformStateProperties::WithViewportMode(System::Nullable<ViewportMode_> val)
    {
        if (val.HasValue)
        {
            NativePointer->withViewportMode((mbgl::ViewportMode)val.Value);
        }
        else
        {
            NativePointer->withViewportMode(std::nullopt);
        }

        return this;
    }

    System::Nullable<System::Double> TransformStateProperties::X::get()
    {
        if (NativePointer->x.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->x.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void TransformStateProperties::X::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->x = value.Value;
        }
        else
        {
            NativePointer->x = std::nullopt;
        }
    }

    System::Nullable<System::Double> TransformStateProperties::Y::get()
    {
        if (NativePointer->y.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->y.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void TransformStateProperties::Y::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->y = value.Value;
        }
        else
        {
            NativePointer->y = std::nullopt;
        }
    }

    System::Nullable<System::Double> TransformStateProperties::Bearing::get()
    {
        if (NativePointer->bearing.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->bearing.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void TransformStateProperties::Bearing::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->bearing = value.Value;
        }
        else
        {
            NativePointer->bearing = std::nullopt;
        }
    }

    System::Nullable<System::Double> TransformStateProperties::Scale::get()
    {
        if (NativePointer->scale.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->scale.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void TransformStateProperties::Scale::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->scale = value.Value;
        }
        else
        {
            NativePointer->scale = std::nullopt;
        }
    }

    System::Nullable<System::Double> TransformStateProperties::Pitch::get()
    {
        if (NativePointer->pitch.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->pitch.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void TransformStateProperties::Pitch::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->pitch = value.Value;
        }
        else
        {
            NativePointer->pitch = std::nullopt;
        }
    }

    System::Nullable<System::Double> TransformStateProperties::XSkew::get()
    {
        if (NativePointer->xSkew.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->xSkew.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void TransformStateProperties::XSkew::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->xSkew = value.Value;
        }
        else
        {
            NativePointer->xSkew = std::nullopt;
        }
    }

    System::Nullable<System::Double> TransformStateProperties::YSkew::get()
    {
        if (NativePointer->ySkew.has_value())
        {
            return System::Nullable<System::Double>(NativePointer->ySkew.value());
        }

        return System::Nullable<System::Double>();
    }

    System::Void TransformStateProperties::YSkew::set(System::Nullable<System::Double> value)
    {
        if (value.HasValue)
        {
            NativePointer->ySkew = value.Value;
        }
        else
        {
            NativePointer->ySkew = std::nullopt;
        }
    }

    System::Nullable<System::Boolean> TransformStateProperties::Axonometric::get()
    {
        if (NativePointer->axonometric.has_value())
        {
            return System::Nullable<System::Boolean>(NativePointer->axonometric.value());
        }

        return System::Nullable<System::Boolean>();
    }

    System::Void TransformStateProperties::Axonometric::set(System::Nullable<System::Boolean> value)
    {
        if (value.HasValue)
        {
            NativePointer->axonometric = value.Value;
        }
        else
        {
            NativePointer->axonometric = std::nullopt;
        }
    }

    System::Nullable<System::Boolean> TransformStateProperties::Panning::get()
    {
        if (NativePointer->panning.has_value())
        {
            return System::Nullable<System::Boolean>(NativePointer->panning.value());
        }

        return System::Nullable<System::Boolean>();
    }

    System::Void TransformStateProperties::Panning::set(System::Nullable<System::Boolean> value)
    {
        if (value.HasValue)
        {
            NativePointer->panning = value.Value;
        }
        else
        {
            NativePointer->panning = std::nullopt;
        }
    }

    System::Nullable<System::Boolean> TransformStateProperties::Scaling::get()
    {
        if (NativePointer->scaling.has_value())
        {
            return System::Nullable<System::Boolean>(NativePointer->scaling.value());
        }

        return System::Nullable<System::Boolean>();
    }

    System::Void TransformStateProperties::Scaling::set(System::Nullable<System::Boolean> value)
    {
        if (value.HasValue)
        {
            NativePointer->scaling = value.Value;
        }
        else
        {
            NativePointer->scaling = std::nullopt;
        }
    }

    System::Nullable<System::Boolean> TransformStateProperties::Rotating::get()
    {
        if (NativePointer->rotating.has_value())
        {
            return System::Nullable<System::Boolean>(NativePointer->rotating.value());
        }

        return System::Nullable<System::Boolean>();
    }

    System::Void TransformStateProperties::Rotating::set(System::Nullable<System::Boolean> value)
    {
        if (value.HasValue)
        {
            NativePointer->rotating = value.Value;
        }
        else
        {
            NativePointer->rotating = std::nullopt;
        }
    }

    EdgeInsets_^ TransformStateProperties::EdgeInsets::get()
    {
        if (NativePointer->edgeInsets.has_value())
        {
            return gcnew EdgeInsets_(EdgeInsets_::CreateNativePointerHolder(NativePointer->edgeInsets.value()));
        }

        return nullptr;
    }

    System::Void TransformStateProperties::EdgeInsets::set(EdgeInsets_^ value)
    {
        if (value)
        {
            NativePointer->edgeInsets = *value->NativePointer;
        }
        else
        {
            NativePointer->edgeInsets = std::nullopt;
        }
    }

    Size_^ TransformStateProperties::Size::get()
    {
        if (NativePointer->size.has_value())
        {
            return gcnew Size_(Size_::CreateNativePointerHolder(NativePointer->size.value()));
        }

        return nullptr;
    }

    System::Void TransformStateProperties::Size::set(Size_^ value)
    {
        if (value)
        {
            NativePointer->size = *value->NativePointer;
        }
        else
        {
            NativePointer->size = std::nullopt;
        }
    }

    System::Nullable<ConstrainMode> TransformStateProperties::Constrain::get()
    {
        if (NativePointer->constrain.has_value())
        {
            return System::Nullable<ConstrainMode>((ConstrainMode)NativePointer->constrain.value());
        }

        return System::Nullable<ConstrainMode>();
    }

    System::Void TransformStateProperties::Constrain::set(System::Nullable<ConstrainMode> value)
    {
        if (value.HasValue)
        {
            NativePointer->constrain = (mbgl::ConstrainMode)value.Value;
        }
        else
        {
            NativePointer->constrain = std::nullopt;
        }
    }

    System::Nullable<NorthOrientation_> TransformStateProperties::NorthOrientation::get()
    {
        if (NativePointer->northOrientation.has_value())
        {
            return System::Nullable<NorthOrientation_>((NorthOrientation_)NativePointer->northOrientation.value());
        }

        return System::Nullable<NorthOrientation_>();
    }

    System::Void TransformStateProperties::NorthOrientation::set(System::Nullable<NorthOrientation_> value)
    {
        if (value.HasValue)
        {
            NativePointer->northOrientation = (mbgl::NorthOrientation)value.Value;
        }
        else
        {
            NativePointer->northOrientation = std::nullopt;
        }
    }

    System::Nullable<ViewportMode_> TransformStateProperties::ViewPortMode::get()
    {
        if (NativePointer->viewPortMode.has_value())
        {
            return System::Nullable<ViewportMode_>((ViewportMode_)NativePointer->viewPortMode.value());
        }

        return System::Nullable<ViewportMode_>();
    }

    System::Void TransformStateProperties::ViewPortMode::set(System::Nullable<ViewportMode_> value)
    {
        if (value.HasValue)
        {
            NativePointer->viewPortMode = (mbgl::ViewportMode)value.Value;
        }
        else
        {
            NativePointer->viewPortMode = std::nullopt;
        }
    }

    TransformState::TransformState()
        : NativeWrapper(new mbgl::TransformState())
    {
    }

    TransformState::TransformState(ConstrainMode_ constrainMode)
        : NativeWrapper(new mbgl::TransformState((mbgl::ConstrainMode)constrainMode))
    {
    }

    TransformState::TransformState(ConstrainMode_ constrainMode, ViewportMode_ viewportMode)
        : NativeWrapper(new mbgl::TransformState((mbgl::ConstrainMode)constrainMode, (mbgl::ViewportMode)viewportMode))
    {
    }

    TransformState::TransformState(NativePointerHolder<mbgl::TransformState>^ nativePointerHolder)
        : NativeWrapper(nativePointerHolder)
    {
    }

    TransformState::~TransformState()
    {

    }

    System::Void TransformState::SetProperties(TransformStateProperties^ properties)
    {
        NativePointer->setProperties(*properties->NativePointer);
    }

    System::Void TransformState::MatrixFor(Mat4^ matrix, UnwrappedTileID^ tileID)
    {
        NativePointer->matrixFor(*matrix->NativePointer, *tileID->NativePointer);
    }

    System::Void TransformState::GetProjMatrix(Mat4^ projMatrix)
    {
        NativePointer->getProjMatrix(*projMatrix->NativePointer);
    }

    System::Void TransformState::GetProjMatrix(Mat4^ projMatrix, System::UInt16 nearZ)
    {
        NativePointer->getProjMatrix(*projMatrix->NativePointer, nearZ);
    }

    System::Void TransformState::GetProjMatrix(Mat4^ projMatrix, System::UInt16 nearZ, System::Boolean aligned)
    {
        NativePointer->getProjMatrix(*projMatrix->NativePointer, nearZ, aligned);
    }

    CameraOptions^ TransformState::GetCameraOptions(EdgeInsets_^ padding)
    {
        return gcnew CameraOptions(CameraOptions::CreateNativePointerHolder(NativePointer->getCameraOptions(*padding->NativePointer)));
    }

    LatLng^ TransformState::GetLatLng()
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->getLatLng()));
    }

    LatLng^ TransformState::GetLatLng(LatLng::WrapMode wrapMode)
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->getLatLng((mbgl::LatLng::WrapMode)wrapMode)));
    }

    System::Void TransformState::SetRotatingInProgress(System::Boolean val)
    {
        NativePointer->setRotatingInProgress(val);
    }

    System::Void TransformState::SetScalingInProgress(System::Boolean val)
    {
        NativePointer->setScalingInProgress(val);
    }

    System::Void TransformState::SetPanningInProgress(System::Boolean val)
    {
        NativePointer->setPanningInProgress(val);
    }

    System::Void TransformState::SetGestureInProgress(System::Boolean val)
    {
        NativePointer->setGestureInProgress(val);
    }

    ScreenCoordinate TransformState::LatLngToScreenCoordinate(LatLng^ latLng)
    {
        return ScreenCoordinate(NativePointer->latLngToScreenCoordinate(*latLng->NativePointer));
    }

    ScreenCoordinate TransformState::LatLngToScreenCoordinate(LatLng^ latLng, Vec4^ p)
    {
        return ScreenCoordinate(NativePointer->latLngToScreenCoordinate(*latLng->NativePointer, *p->NativePointer));
    }

    LatLng^ TransformState::ScreenCoordinateToLatLng(ScreenCoordinate point)
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->screenCoordinateToLatLng(mbgl::ScreenCoordinate(point.X, point.Y))));
    }

    LatLng^ TransformState::ScreenCoordinateToLatLng(ScreenCoordinate point, LatLng::WrapMode wrapMode)
    {
        return gcnew LatLng(LatLng::CreateNativePointerHolder(NativePointer->screenCoordinateToLatLng(mbgl::ScreenCoordinate(point.X, point.Y), (mbgl::LatLng::WrapMode)wrapMode)));
    }

    TileCoordinate^ TransformState::ScreenCoordinateToTileCoordinate(ScreenCoordinate point, System::Byte atZoom)
    {
        return gcnew TileCoordinate(TileCoordinate::CreateNativePointerHolder(NativePointer->screenCoordinateToTileCoordinate(mbgl::ScreenCoordinate(point.X, point.Y), atZoom)));
    }

    System::Double TransformState::ZoomScale(System::Double zoom)
    {
        return NativePointer->zoomScale(zoom);
    }

    System::Double TransformState::ScaleZoom(System::Double scale)
    {
        return NativePointer->scaleZoom(scale);
    }

    System::Single TransformState::GetCameraToTileDistance(UnwrappedTileID^ tileID)
    {
        return NativePointer->getCameraToTileDistance(*tileID->NativePointer);
    }

    System::Void TransformState::MoveLatLng(LatLng^ latLng, ScreenCoordinate anchor)
    {
        NativePointer->moveLatLng(*latLng->NativePointer, mbgl::ScreenCoordinate(anchor.X, anchor.Y));
    }

    System::Void TransformState::SetLatLngZoom(LatLng^ latLng, System::Double zoom)
    {
        NativePointer->setLatLngZoom(*latLng->NativePointer, zoom);
    }

    System::Void TransformState::Constrain(System::Double% scale, System::Double% x, System::Double% y)
    {
        cli::pin_ptr<System::Double> ptrScale = &scale;
        cli::pin_ptr<System::Double> ptrX = &x;
        cli::pin_ptr<System::Double> ptrY = &y;

        NativePointer->constrain(*ptrScale, *ptrX, *ptrY);
    }

    Size_^ TransformState::Size::get()
    {
        return gcnew Size_(Size_::CreateNativePointerHolder(NativePointer->getSize()));
    }

    System::Void TransformState::Size::set(Size_^ value)
    {
        NativePointer->setSize(*value->NativePointer);
    }

    NorthOrientation_ TransformState::NorthOrientation::get()
    {
        return (NorthOrientation_)NativePointer->getNorthOrientation();
    }

    System::Void TransformState::NorthOrientation::set(NorthOrientation_ value)
    {
        NativePointer->setNorthOrientation((mbgl::NorthOrientation)value);
    }

    System::Double TransformState::NorthOrientationAngle::get()
    {
        return NativePointer->getNorthOrientationAngle();
    }

    ConstrainMode_ TransformState::ConstrainMode::get()
    {
        return (ConstrainMode_)NativePointer->getConstrainMode();
    }

    System::Void TransformState::ConstrainMode::set(ConstrainMode_ value)
    {
        NativePointer->setConstrainMode((mbgl::ConstrainMode)value);
    }

    ViewportMode_ TransformState::ViewportMode::get()
    {
        return (ViewportMode_)NativePointer->getViewportMode();
    }

    System::Void TransformState::ViewportMode::set(ViewportMode_ value)
    {
        NativePointer->setViewportMode((mbgl::ViewportMode)value);
    }

    EdgeInsets_^ TransformState::EdgeInsets::get()
    {
        return gcnew EdgeInsets_(EdgeInsets_::CreateNativePointerHolder(NativePointer->getEdgeInsets()));
    }

    System::Void TransformState::EdgeInsets::set(EdgeInsets_^ value)
    {
        NativePointer->setEdgeInsets(*value->NativePointer);
    }

    System::Double TransformState::PixelX::get()
    {
        return NativePointer->pixel_x();
    }

    System::Double TransformState::PixelY::get()
    {
        return NativePointer->pixel_y();
    }

    System::Double TransformState::Zoom::get()
    {
        return NativePointer->getZoom();
    }

    System::Byte TransformState::IntegerZoom::get()
    {
        return NativePointer->getIntegerZoom();
    }

    System::Double TransformState::ZoomFraction::get()
    {
        return NativePointer->getZoomFraction();
    }

    System::Double TransformState::Scale::get()
    {
        return NativePointer->getScale();
    }

    System::Void TransformState::Scale::set(System::Double value)
    {
        NativePointer->setScale(value);
    }

    System::Double TransformState::X::get()
    {
        return NativePointer->getX();
    }

    System::Void TransformState::X::set(System::Double value)
    {
        NativePointer->setX(value);
    }

    System::Double TransformState::Y::get()
    {
        return NativePointer->getY();
    }

    System::Void TransformState::Y::set(System::Double value)
    {
        NativePointer->setY(value);
    }

    LatLngBounds_^ TransformState::LatLngBounds::get()
    {
        return gcnew LatLngBounds_(LatLngBounds_::CreateNativePointerHolder(NativePointer->getLatLngBounds()));
    }

    System::Void TransformState::LatLngBounds::set(LatLngBounds_^ value)
    {
        NativePointer->setLatLngBounds(*value->NativePointer);
    }

    System::Double TransformState::MinZoom::get()
    {
        return NativePointer->getMinZoom();
    }

    System::Void TransformState::MinZoom::set(System::Double value)
    {
        NativePointer->setMinZoom(value);
    }

    System::Double TransformState::MaxZoom::get()
    {
        return NativePointer->getMaxZoom();
    }

    System::Void TransformState::MaxZoom::set(System::Double value)
    {
        NativePointer->setMaxZoom(value);
    }

    System::Double TransformState::MinPitch::get()
    {
        return NativePointer->getMinPitch();
    }

    System::Void TransformState::MinPitch::set(System::Double value)
    {
        NativePointer->setMinPitch(value);
    }

    System::Double TransformState::MaxPitch::get()
    {
        return NativePointer->getMaxPitch();
    }

    System::Void TransformState::MaxPitch::set(System::Double value)
    {
        NativePointer->setMaxPitch(value);
    }

    System::Double TransformState::Bearing::get()
    {
        return NativePointer->getBearing();
    }

    System::Void TransformState::Bearing::set(System::Double value)
    {
        NativePointer->setBearing(value);
    }

    System::Single TransformState::FieldOfView::get()
    {
        return NativePointer->getFieldOfView();
    }

    System::Single TransformState::CameraToCenterDistance::get()
    {
        return NativePointer->getCameraToCenterDistance();
    }

    System::Double TransformState::Pitch::get()
    {
        return NativePointer->getPitch();
    }

    System::Void TransformState::Pitch::set(System::Double value)
    {
        NativePointer->setPitch(value);
    }

    System::Double TransformState::XSkew::get()
    {
        return NativePointer->getXSkew();
    }

    System::Void TransformState::XSkew::set(System::Double value)
    {
        NativePointer->setXSkew(value);
    }

    System::Double TransformState::YSkew::get()
    {
        return NativePointer->getYSkew();
    }

    System::Void TransformState::YSkew::set(System::Double value)
    {
        NativePointer->setYSkew(value);
    }

    System::Boolean TransformState::Axonometric::get()
    {
        return NativePointer->getAxonometric();
    }

    System::Void TransformState::Axonometric::set(System::Boolean value)
    {
        NativePointer->setAxonometric(value);
    }

    System::Boolean TransformState::IsChanging::get()
    {
        return NativePointer->isChanging();
    }

    System::Boolean TransformState::IsRotating::get()
    {
        return NativePointer->isRotating();
    }

    System::Boolean TransformState::IsScaling::get()
    {
        return NativePointer->isScaling();
    }

    System::Boolean TransformState::IsPanning::get()
    {
        return NativePointer->isPanning();
    }

    System::Boolean TransformState::IsGestureInProgress::get()
    {
        return NativePointer->isGestureInProgress();
    }

    System::Boolean TransformState::Valid::get()
    {
        return NativePointer->valid();
    }

    System::Single TransformState::MaxPitchScaleFactor::get()
    {
        return NativePointer->maxPitchScaleFactor();
    }

    Mat4^ TransformState::ProjectionMatrix::get()
    {
        return gcnew Mat4(Mat4::CreateNativePointerHolder(NativePointer->getProjectionMatrix()));
    }

    Mat4^ TransformState::InvProjectionMatrix::get()
    {
        return gcnew Mat4(Mat4::CreateNativePointerHolder(NativePointer->getInvProjectionMatrix()));
    }

    FreeCameraOptions_^ TransformState::FreeCameraOptions::get()
    {
        return gcnew FreeCameraOptions_(FreeCameraOptions_::CreateNativePointerHolder(NativePointer->getFreeCameraOptions()));
    }

    System::Void TransformState::FreeCameraOptions::set(FreeCameraOptions_^ value)
    {
        NativePointer->setFreeCameraOptions(*value->NativePointer);
    }
}
