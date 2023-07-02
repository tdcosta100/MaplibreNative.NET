#pragma once
#include "Convert.h"
#include "NativeWrapper.h"
#include <mbgl/map/map_observer.hpp>
#include <algorithm>
#include <msclr/gcroot.h>

namespace mbgl
{
    namespace gfx
    {
        class ShaderRegistry;
    }
}

namespace DOTNET_NAMESPACE
{
    public enum class MapLoadError {
        StyleParseError,
        StyleLoadError,
        NotFoundError,
        UnknownError,
    };

    ref class ShaderRegistry;
    class NativeMapObserver;

    public ref class MapObserver : NativeWrapper<NativeMapObserver>
    {
    public:
        enum class CameraChangeMode : System::UInt32
        {
            Immediate,
            Animated
        };

        enum class RenderMode : System::UInt32
        {
            Partial,
            Full
        };

        value struct RenderFrameStatus
        {
            RenderMode mode;
            System::Boolean needsRepaint;
            System::Boolean placementChanged;
        };

        delegate System::Void CameraWillChangeHandler(CameraChangeMode mode);
        delegate System::Void CameraIsChangingHandler();
        delegate System::Void CameraDidChangeHandler(CameraChangeMode mode);
        delegate System::Void WillStartLoadingMapHandler();
        delegate System::Void DidFinishLoadingMapHandler();
        delegate System::Void DidFailLoadingMapHandler(MapLoadError type, System::String^ description);
        delegate System::Void WillStartRenderingFrameHandler();
        delegate System::Void DidFinishRenderingFrameHandler(RenderFrameStatus status);
        delegate System::Void WillStartRenderingMapHandler();
        delegate System::Void DidFinishRenderingMapHandler(RenderMode mode);
        delegate System::Void DidFinishLoadingStyleHandler();
        // TODO: implement the managed version
        //delegate System::Void SourceChangedHandler(Source^ source);
        delegate System::Void DidBecomeIdleHandler();
        delegate System::Void StyleImageMissingHandler(System::String^ id);
        
        /// <summary>
        /// This event handler should return true if unused image can be removed,
        /// false otherwise. By default, unused image will be removed.
        /// </summary>
        delegate System::Boolean CanRemoveUnusedStyleImageHandler(System::String^ id);
        delegate System::Void RegisterShadersHandler(ShaderRegistry^ shaderRegistry);

        event CameraWillChangeHandler^ CameraWillChange;
        event CameraIsChangingHandler^ CameraIsChanging;
        event CameraDidChangeHandler^ CameraDidChange;
        event WillStartLoadingMapHandler^ WillStartLoadingMap;
        event DidFinishLoadingMapHandler^ DidFinishLoadingMap;
        event DidFailLoadingMapHandler^ DidFailLoadingMap;
        event WillStartRenderingFrameHandler^ WillStartRenderingFrame;
        event DidFinishRenderingFrameHandler^ DidFinishRenderingFrame;
        event WillStartRenderingMapHandler^ WillStartRenderingMap;
        event DidFinishRenderingMapHandler^ DidFinishRenderingMap;
        event DidFinishLoadingStyleHandler^ DidFinishLoadingStyle;
        // TODO: implement the managed version
        //event SourceChangedHandler^ SourceChanged;
        event DidBecomeIdleHandler^ DidBecomeIdle;
        event StyleImageMissingHandler^ StyleImageMissing;
        event CanRemoveUnusedStyleImageHandler^ CanRemoveUnusedStyleImage;

        /// <summary>
        /// Observe this event to easily mutate or observe shaders as soon
        /// as the registry becomes available.
        /// </summary>
        event RegisterShadersHandler^ RegisterShaders;

        MapObserver();
        ~MapObserver();

    protected:
        virtual System::Void onCameraWillChange(CameraChangeMode mode);
        virtual System::Void onCameraIsChanging();
        virtual System::Void onCameraDidChange(CameraChangeMode mode);
        virtual System::Void onWillStartLoadingMap();
        virtual System::Void onDidFinishLoadingMap();
        virtual System::Void onDidFailLoadingMap(MapLoadError type, System::String^ description);
        virtual System::Void onWillStartRenderingFrame();
        virtual System::Void onDidFinishRenderingFrame(RenderFrameStatus status);
        virtual System::Void onWillStartRenderingMap();
        virtual System::Void onDidFinishRenderingMap(RenderMode mode);
        virtual System::Void onDidFinishLoadingStyle();
        //virtual System::Void onSourceChanged(Source^ source);
        virtual System::Void onDidBecomeIdle();
        virtual System::Void onStyleImageMissing(System::String^ id);

        /// <summary>
        /// This method should return true if unused image can be removed,
        /// false otherwise. By default, unused image will be removed.
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        virtual System::Boolean onCanRemoveUnusedStyleImage(System::String^ id);
        virtual System::Void onRegisterShaders(ShaderRegistry^ shaderRegistry);
    };

    class NativeMapObserver : public mbgl::MapObserver
    {
    public:
        NativeMapObserver();
        ~NativeMapObserver();

        void onCameraWillChange(mbgl::MapObserver::CameraChangeMode mode) override;
        void onCameraIsChanging() override;
        void onCameraDidChange(mbgl::MapObserver::CameraChangeMode mode) override;
        void onWillStartLoadingMap() override;
        void onDidFinishLoadingMap() override;
        void onDidFailLoadingMap(mbgl::MapLoadError type, const std::string& description) override;
        void onWillStartRenderingFrame() override;
        void onDidFinishRenderingFrame(mbgl::MapObserver::RenderFrameStatus status) override;
        void onWillStartRenderingMap() override;
        void onDidFinishRenderingMap(mbgl::MapObserver::RenderMode mode) override;
        void onDidFinishLoadingStyle() override;
        void onSourceChanged(mbgl::style::Source& source) override;
        void onDidBecomeIdle() override;
        void onStyleImageMissing(const std::string& id) override;
        bool onCanRemoveUnusedStyleImage(const std::string& id) override;
        void onRegisterShaders(mbgl::gfx::ShaderRegistry& shaderRegistry) override;

        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::CameraWillChangeHandler^> CameraWillChangeHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::CameraIsChangingHandler^> CameraIsChangingHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::CameraDidChangeHandler^> CameraDidChangeHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::WillStartLoadingMapHandler^> WillStartLoadingMapHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::DidFinishLoadingMapHandler^> DidFinishLoadingMapHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::DidFailLoadingMapHandler^> DidFailLoadingMapHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::WillStartRenderingFrameHandler^> WillStartRenderingFrameHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::DidFinishRenderingFrameHandler^> DidFinishRenderingFrameHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::WillStartRenderingMapHandler^> WillStartRenderingMapHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::DidFinishRenderingMapHandler^> DidFinishRenderingMapHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::DidFinishLoadingStyleHandler^> DidFinishLoadingStyleHandler;
        //msclr::gcroot<DOTNET_NAMESPACE::MapObserver::SourceChangedHandler^> SourceChangedHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::DidBecomeIdleHandler^> DidBecomeIdleHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::StyleImageMissingHandler^> StyleImageMissingHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::CanRemoveUnusedStyleImageHandler^> CanRemoveUnusedStyleImageHandler;
        msclr::gcroot<DOTNET_NAMESPACE::MapObserver::RegisterShadersHandler^> RegisterShadersHandler;
    };
}
