#pragma once
#include "NativeWrapper.h"
#include <functional>
#include <string>
#include <mbgl/renderer/renderer_observer.hpp>
#include <algorithm>
#include <msclr/gcroot.h>

namespace DOTNET_NAMESPACE
{
    class NativeRendererObserver;
    ref class ShaderRegistry;

    public ref class RendererObserver : NativeWrapper<NativeRendererObserver>
    {
    public:
        enum class RenderMode : System::UInt32
        {
            Partial,
            Full
        };

        /// <summary>
        /// Style is missing an image
        /// </summary>
        delegate void StyleImageMissingCallback();

        delegate System::Void InvalidateHandler();
        delegate System::Void ResourceErrorHandler(System::Exception^ ex);
        delegate System::Void WillStartRenderingMapHandler();
        delegate System::Void WillStartRenderingFrameHandler();
        delegate System::Void DidFinishRenderingFrameHandler(RenderMode mode, bool repaintNeeded, bool placementChanged);
        delegate System::Void DidFinishRenderingMapHandler();
        delegate System::Void StyleImageMissingHandler(System::String^ image, StyleImageMissingCallback^ callback);
        delegate System::Void RemoveUnusedStyleImagesHandler(System::Collections::Generic::IEnumerable<System::String^>^ unusedImageIDs);
        delegate System::Void RegisterShadersHandler(ShaderRegistry^ shaderRegistry);

        /// <summary>
        /// Signals that a repaint is required
        /// </summary>
        event InvalidateHandler^ Invalidate;

        /// <summary>
        /// Resource failed to download / parse
        /// </summary>
        event ResourceErrorHandler^ ResourceError;

        /// <summary>
        /// First frame
        /// </summary>
        event WillStartRenderingMapHandler^ WillStartRenderingMap;

        /// <summary>
        /// Start of frame, initial is the first frame for this map
        /// </summary>
        event WillStartRenderingFrameHandler^ WillStartRenderingFrame;

        /// <summary>
        /// End of frame, booleans flags that a repaint is required and that placement changed.
        /// </summary>
        event DidFinishRenderingFrameHandler^ DidFinishRenderingFrame;

        /// <summary>
        /// Final frame
        /// </summary>
        event DidFinishRenderingMapHandler^ DidFinishRenderingMap;
        event StyleImageMissingHandler^ StyleImageMissing;
        event RemoveUnusedStyleImagesHandler^ RemoveUnusedStyleImages;

        /// <summary>
        /// Entry point for custom shader registration
        /// </summary>
        event RegisterShadersHandler^ RegisterShaders;

        RendererObserver();
        ~RendererObserver();

    protected:
        virtual System::Void onInvalidate();
        virtual System::Void onResourceError(System::Exception^ ex);
        virtual System::Void onWillStartRenderingMap();
        virtual System::Void onWillStartRenderingFrame();
        virtual System::Void onDidFinishRenderingFrame(RenderMode mode, bool repaintNeeded, bool placementChanged);
        virtual System::Void onDidFinishRenderingMap();
        virtual System::Void onStyleImageMissing(System::String^ image, StyleImageMissingCallback^ callback);
        virtual System::Void onRemoveUnusedStyleImages(System::Collections::Generic::IEnumerable<System::String^>^ unusedImageIDs);
        virtual System::Void onRegisterShaders(ShaderRegistry^ shaderRegistry);
    };

    ref class StyleImageMissingCallbackHelper
    {
    public:
        StyleImageMissingCallbackHelper(NativeRendererObserver* observer);
        ~StyleImageMissingCallbackHelper();
        !StyleImageMissingCallbackHelper();

        void StyleImageMissingCallbackHandler();
    private:
        NativeRendererObserver* _Observer;
    };

    class NativeRendererObserver : public mbgl::RendererObserver
    {
    public:
        NativeRendererObserver();
        ~NativeRendererObserver();

        void onInvalidate() override;
        void onResourceError(std::exception_ptr eptr) override;
        void onWillStartRenderingMap() override;
        void onWillStartRenderingFrame() override;
        void onDidFinishRenderingFrame(RenderMode renderMode, bool needsRepaint, bool placemenChanged) override;
        void onDidFinishRenderingMap() override;
        void onStyleImageMissing(const std::string& id, const StyleImageMissingCallback& done) override;
        void onRemoveUnusedStyleImages(const std::vector<std::string>& unusedImageIDs) override;
        void onRegisterShaders(mbgl::gfx::ShaderRegistry& shaderRegistry) override;

        void StyleImageMissingCallbackHandler(StyleImageMissingCallbackHelper^ callbackHelper);

        msclr::gcroot<DOTNET_NAMESPACE::RendererObserver::InvalidateHandler^> InvalidateHandler;
        msclr::gcroot<DOTNET_NAMESPACE::RendererObserver::ResourceErrorHandler^> ResourceErrorHandler;
        msclr::gcroot<DOTNET_NAMESPACE::RendererObserver::WillStartRenderingMapHandler^> WillStartRenderingMapHandler;
        msclr::gcroot<DOTNET_NAMESPACE::RendererObserver::WillStartRenderingFrameHandler^> WillStartRenderingFrameHandler;
        msclr::gcroot<DOTNET_NAMESPACE::RendererObserver::DidFinishRenderingFrameHandler^> DidFinishRenderingFrameHandler;
        msclr::gcroot<DOTNET_NAMESPACE::RendererObserver::DidFinishRenderingMapHandler^> DidFinishRenderingMapHandler;
        msclr::gcroot<DOTNET_NAMESPACE::RendererObserver::StyleImageMissingHandler^> StyleImageMissingHandler;
        msclr::gcroot<DOTNET_NAMESPACE::RendererObserver::RemoveUnusedStyleImagesHandler^> RemoveUnusedStyleImagesHandler;
        msclr::gcroot<DOTNET_NAMESPACE::RendererObserver::RegisterShadersHandler^> RegisterShadersHandler;
    private:
        msclr::gcroot<System::Collections::Concurrent::ConcurrentDictionary<StyleImageMissingCallbackHelper^, System::IntPtr>^> _PendingCallbacks = gcnew System::Collections::Concurrent::ConcurrentDictionary<StyleImageMissingCallbackHelper^, System::IntPtr>();
    };
}
