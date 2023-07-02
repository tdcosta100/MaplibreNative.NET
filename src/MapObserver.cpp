#include "MapObserver.h"
#include "ShaderRegistry.h"
#include <mbgl/gfx/shader_registry.hpp>
#include <mbgl/map/map_observer.hpp>

namespace DOTNET_NAMESPACE
{
    MapObserver::MapObserver()
        : NativeWrapper(new NativeMapObserver())
    {
        NativePointer->CameraWillChangeHandler = gcnew CameraWillChangeHandler(this, &MapObserver::onCameraWillChange);
        NativePointer->CameraIsChangingHandler = gcnew CameraIsChangingHandler(this, &MapObserver::onCameraIsChanging);
        NativePointer->CameraDidChangeHandler = gcnew CameraDidChangeHandler(this, &MapObserver::onCameraDidChange);
        NativePointer->WillStartLoadingMapHandler = gcnew WillStartLoadingMapHandler(this, &MapObserver::onWillStartLoadingMap);
        NativePointer->DidFinishLoadingMapHandler = gcnew DidFinishLoadingMapHandler(this, &MapObserver::onDidFinishLoadingMap);
        NativePointer->DidFailLoadingMapHandler = gcnew DidFailLoadingMapHandler(this, &MapObserver::onDidFailLoadingMap);
        NativePointer->WillStartRenderingFrameHandler = gcnew WillStartRenderingFrameHandler(this, &MapObserver::onWillStartRenderingFrame);
        NativePointer->DidFinishRenderingFrameHandler = gcnew DidFinishRenderingFrameHandler(this, &MapObserver::onDidFinishRenderingFrame);
        NativePointer->WillStartRenderingMapHandler = gcnew WillStartRenderingMapHandler(this, &MapObserver::onWillStartRenderingMap);
        NativePointer->DidFinishRenderingMapHandler = gcnew DidFinishRenderingMapHandler(this, &MapObserver::onDidFinishRenderingMap);
        NativePointer->DidFinishLoadingStyleHandler = gcnew DidFinishLoadingStyleHandler(this, &MapObserver::onDidFinishLoadingStyle);
        //NativePointer->SourceChangedHandler = gcnew SourceChangedHandler(this, &MapObserver::onSourceChanged);
        NativePointer->DidBecomeIdleHandler = gcnew DidBecomeIdleHandler(this, &MapObserver::onDidBecomeIdle);
        NativePointer->StyleImageMissingHandler = gcnew StyleImageMissingHandler(this, &MapObserver::onStyleImageMissing);
        NativePointer->CanRemoveUnusedStyleImageHandler = gcnew CanRemoveUnusedStyleImageHandler(this, &MapObserver::onCanRemoveUnusedStyleImage);
        NativePointer->RegisterShadersHandler = gcnew RegisterShadersHandler(this, &MapObserver::onRegisterShaders);
    }
    
    MapObserver::~MapObserver()
    {
    }

    System::Void MapObserver::onCameraWillChange(CameraChangeMode mode)
    {
        CameraWillChange(mode);
    }

    System::Void MapObserver::onCameraIsChanging()
    {
        CameraIsChanging();
    }

    System::Void MapObserver::onCameraDidChange(CameraChangeMode mode)
    {
        CameraDidChange(mode);
    }

    System::Void MapObserver::onWillStartLoadingMap()
    {
        WillStartLoadingMap();
    }

    System::Void MapObserver::onDidFinishLoadingMap()
    {
        DidFinishLoadingMap();
    }

    System::Void MapObserver::onDidFailLoadingMap(MapLoadError type, System::String^ description)
    {
        DidFailLoadingMap(type, description);
    }

    System::Void MapObserver::onWillStartRenderingFrame()
    {
        WillStartRenderingFrame();
    }

    System::Void MapObserver::onDidFinishRenderingFrame(RenderFrameStatus status)
    {
        DidFinishRenderingFrame(status);
    }

    System::Void MapObserver::onWillStartRenderingMap()
    {
        WillStartRenderingMap();
    }

    System::Void MapObserver::onDidFinishRenderingMap(RenderMode mode)
    {
        DidFinishRenderingMap(mode);
    }

    System::Void MapObserver::onDidFinishLoadingStyle()
    {
        DidFinishLoadingStyle();
    }

    // TODO: implement the managed version
    /*
    System::Void MapObserver::onSourceChanged(Source^ source)
    {
        SourceChanged(source);
    }
    */

    System::Void MapObserver::onDidBecomeIdle()
    {
        DidBecomeIdle();
    }

    System::Void MapObserver::onStyleImageMissing(System::String^ id)
    {
        StyleImageMissing(id);
    }

    System::Boolean MapObserver::onCanRemoveUnusedStyleImage(System::String^ id)
    {
        return true;
        //return CanRemoveUnusedStyleImage(id);
    }

    System::Void MapObserver::onRegisterShaders(ShaderRegistry^ shaderRegistry)
    {
        RegisterShaders(shaderRegistry);
    }

    NativeMapObserver::NativeMapObserver()
    {
    }

    NativeMapObserver::~NativeMapObserver()
    {
    }

    void NativeMapObserver::onCameraWillChange(mbgl::MapObserver::CameraChangeMode mode)
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::CameraWillChangeHandler^>(CameraWillChangeHandler))
        {
            CameraWillChangeHandler->Invoke((DOTNET_NAMESPACE::MapObserver::CameraChangeMode)mode);
        }
    }

    void NativeMapObserver::onCameraIsChanging()
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::CameraIsChangingHandler^>(CameraIsChangingHandler))
        {
            CameraIsChangingHandler->Invoke();
        }
    }

    void NativeMapObserver::onCameraDidChange(mbgl::MapObserver::CameraChangeMode mode)
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::CameraDidChangeHandler^>(CameraDidChangeHandler))
        {
            CameraDidChangeHandler->Invoke((DOTNET_NAMESPACE::MapObserver::CameraChangeMode)mode);
        }
    }

    void NativeMapObserver::onWillStartLoadingMap()
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::WillStartLoadingMapHandler^>(WillStartLoadingMapHandler))
        {
            WillStartLoadingMapHandler->Invoke();
        }
    }

    void NativeMapObserver::onDidFinishLoadingMap()
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::DidFinishLoadingMapHandler^>(DidFinishLoadingMapHandler))
        {
            DidFinishLoadingMapHandler->Invoke();
        }
    }

    void NativeMapObserver::onDidFailLoadingMap(mbgl::MapLoadError type, const std::string& description)
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::DidFailLoadingMapHandler^>(DidFailLoadingMapHandler))
        {
            DidFailLoadingMapHandler->Invoke((DOTNET_NAMESPACE::MapLoadError)type, Convert::ToSystemString(description));
        }
    }

    void NativeMapObserver::onWillStartRenderingFrame()
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::WillStartRenderingFrameHandler^>(WillStartRenderingFrameHandler))
        {
            WillStartRenderingFrameHandler->Invoke();
        }
    }

    void NativeMapObserver::onDidFinishRenderingFrame(mbgl::MapObserver::RenderFrameStatus status)
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::DidFinishRenderingFrameHandler^>(DidFinishRenderingFrameHandler))
        {
            DOTNET_NAMESPACE::MapObserver::RenderFrameStatus managedStatus
            {
                (DOTNET_NAMESPACE::MapObserver::RenderMode)status.mode,
                status.needsRepaint,
                status.placementChanged
            };

            DidFinishRenderingFrameHandler->Invoke(managedStatus);
        }
    }

    void NativeMapObserver::onWillStartRenderingMap()
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::WillStartRenderingMapHandler^>(WillStartRenderingMapHandler))
        {
            WillStartRenderingMapHandler->Invoke();
        }
    }

    void NativeMapObserver::onDidFinishRenderingMap(mbgl::MapObserver::RenderMode mode)
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::DidFinishRenderingMapHandler^>(DidFinishRenderingMapHandler))
        {
            DidFinishRenderingMapHandler->Invoke((DOTNET_NAMESPACE::MapObserver::RenderMode)mode);
        }
    }

    void NativeMapObserver::onDidFinishLoadingStyle()
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::DidFinishLoadingStyleHandler^>(DidFinishLoadingStyleHandler))
        {
            DidFinishLoadingStyleHandler->Invoke();
        }
    }

    void NativeMapObserver::onSourceChanged(mbgl::style::Source& source)
    {
        /*
        if (static_cast<DOTNET_NAMESPACE::MapObserver::SourceChangedHandler^>(SourceChangedHandler))
        {
            SourceChangedHandler->Invoke(gcnew Source(Source::CreateNativePointerHolder(source)));
        }
        */
    }

    void NativeMapObserver::onDidBecomeIdle()
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::DidBecomeIdleHandler^>(DidBecomeIdleHandler))
        {
            DidBecomeIdleHandler->Invoke();
        }
    }

    void NativeMapObserver::onStyleImageMissing(const std::string& id)
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::StyleImageMissingHandler^>(StyleImageMissingHandler))
        {
            StyleImageMissingHandler->Invoke(Convert::ToSystemString(id));
        }
    }

    bool NativeMapObserver::onCanRemoveUnusedStyleImage(const std::string& id)
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::CanRemoveUnusedStyleImageHandler^>(CanRemoveUnusedStyleImageHandler))
        {
            return CanRemoveUnusedStyleImageHandler->Invoke(Convert::ToSystemString(id));
        }

        return mbgl::MapObserver::onCanRemoveUnusedStyleImage(id);
    }

    void NativeMapObserver::onRegisterShaders(mbgl::gfx::ShaderRegistry& shaderRegistry)
    {
        if (static_cast<DOTNET_NAMESPACE::MapObserver::RegisterShadersHandler^>(RegisterShadersHandler))
        {
            RegisterShadersHandler->Invoke(gcnew ShaderRegistry(ShaderRegistry::CreateNativePointerHolder(&shaderRegistry, false)));
        }
    }
}
