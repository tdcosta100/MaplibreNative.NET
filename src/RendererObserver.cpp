#include "Convert.h"
#include "RendererObserver.h"
#include "ShaderRegistry.h"
#include <mbgl/gfx/shader_registry.hpp>

namespace DOTNET_NAMESPACE
{
    RendererObserver::RendererObserver() : NativeWrapper(new NativeRendererObserver())
    {
        NativePointer->InvalidateHandler = gcnew InvalidateHandler(this, &RendererObserver::onInvalidate);
        NativePointer->ResourceErrorHandler = gcnew ResourceErrorHandler(this, &RendererObserver::onResourceError);
        NativePointer->WillStartRenderingMapHandler = gcnew WillStartRenderingMapHandler(this, &RendererObserver::onWillStartRenderingMap);
        NativePointer->WillStartRenderingFrameHandler = gcnew WillStartRenderingFrameHandler(this, &RendererObserver::onWillStartRenderingFrame);
        NativePointer->DidFinishRenderingFrameHandler = gcnew DidFinishRenderingFrameHandler(this, &RendererObserver::onDidFinishRenderingFrame);
        NativePointer->DidFinishRenderingMapHandler = gcnew DidFinishRenderingMapHandler(this, &RendererObserver::onDidFinishRenderingMap);
        NativePointer->StyleImageMissingHandler = gcnew StyleImageMissingHandler(this, &RendererObserver::onStyleImageMissing);
        NativePointer->RemoveUnusedStyleImagesHandler = gcnew RemoveUnusedStyleImagesHandler(this, &RendererObserver::onRemoveUnusedStyleImages);
    }

    RendererObserver::~RendererObserver()
    {
    }

    System::Void RendererObserver::onInvalidate()
    {
        Invalidate();
    }

    System::Void RendererObserver::onResourceError(System::Exception^ ex)
    {
        ResourceError(ex);
    }

    System::Void RendererObserver::onWillStartRenderingMap()
    {
        WillStartRenderingMap();
    }

    System::Void RendererObserver::onWillStartRenderingFrame()
    {
        WillStartRenderingFrame();
    }

    System::Void RendererObserver::onDidFinishRenderingFrame(RenderMode mode, bool repaintNeeded, bool placementChanged)
    {
        DidFinishRenderingFrame(mode, repaintNeeded, placementChanged);
    }

    System::Void RendererObserver::onDidFinishRenderingMap()
    {
        DidFinishRenderingMap();
    }

    System::Void RendererObserver::onStyleImageMissing(System::String^ image, StyleImageMissingCallback^ callback)
    {
        StyleImageMissing(image, callback);
    }

    System::Void RendererObserver::onRemoveUnusedStyleImages(System::Collections::Generic::IEnumerable<System::String^>^ unusedImageIDs)
    {
        RemoveUnusedStyleImages(unusedImageIDs);
    }

    System::Void RendererObserver::onRegisterShaders(ShaderRegistry^ shaderRegistry)
    {
        RegisterShaders(shaderRegistry);
    }

    StyleImageMissingCallbackHelper::StyleImageMissingCallbackHelper(NativeRendererObserver* observer) : _Observer(observer)
    {
    }

    StyleImageMissingCallbackHelper::~StyleImageMissingCallbackHelper()
    {
        this->!StyleImageMissingCallbackHelper();
    }

    StyleImageMissingCallbackHelper::!StyleImageMissingCallbackHelper()
    {
    }

    void StyleImageMissingCallbackHelper::StyleImageMissingCallbackHandler()
    {
        _Observer->StyleImageMissingCallbackHandler(this);
    }

    NativeRendererObserver::NativeRendererObserver()
    {
    }

    NativeRendererObserver::~NativeRendererObserver()
    {
    }

    void NativeRendererObserver::onInvalidate()
    {
        if (static_cast<DOTNET_NAMESPACE::RendererObserver::InvalidateHandler^>(InvalidateHandler))
        {
            InvalidateHandler->Invoke();
        }
    }

    void NativeRendererObserver::onResourceError(std::exception_ptr eptr)
    {
        if (static_cast<DOTNET_NAMESPACE::RendererObserver::ResourceErrorHandler^>(ResourceErrorHandler))
        {
            try
            {
                std::rethrow_exception(eptr);
            }
            catch (const std::exception& ex)
            {
                ResourceErrorHandler->Invoke(gcnew System::Exception(gcnew System::String(ex.what())));
            }
        }
    }

    void NativeRendererObserver::onWillStartRenderingMap()
    {
        if (static_cast<DOTNET_NAMESPACE::RendererObserver::WillStartRenderingMapHandler^>(WillStartRenderingMapHandler))
        {
            WillStartRenderingMapHandler->Invoke();
        }
    }

    void NativeRendererObserver::onWillStartRenderingFrame()
    {
        if (static_cast<DOTNET_NAMESPACE::RendererObserver::WillStartRenderingFrameHandler^>(WillStartRenderingFrameHandler))
        {
            WillStartRenderingFrameHandler->Invoke();
        }
    }

    void NativeRendererObserver::onDidFinishRenderingFrame(RenderMode renderMode, bool needsRepaint, bool placemenChanged)
    {
        if (static_cast<DOTNET_NAMESPACE::RendererObserver::DidFinishRenderingFrameHandler^>(DidFinishRenderingFrameHandler))
        {
            DidFinishRenderingFrameHandler->Invoke((DOTNET_NAMESPACE::RendererObserver::RenderMode)renderMode, needsRepaint, placemenChanged);
        }
    }

    void NativeRendererObserver::onDidFinishRenderingMap()
    {
        if (static_cast<DOTNET_NAMESPACE::RendererObserver::DidFinishRenderingMapHandler^>(DidFinishRenderingMapHandler))
        {
            DidFinishRenderingMapHandler->Invoke();
        }
    }

    void NativeRendererObserver::onStyleImageMissing(const std::string& id, const StyleImageMissingCallback& done)
    {
        if (static_cast<DOTNET_NAMESPACE::RendererObserver::StyleImageMissingHandler^>(StyleImageMissingHandler))
        {
            StyleImageMissingCallbackHelper^ callbackHelper = gcnew StyleImageMissingCallbackHelper(this);

            _PendingCallbacks->TryAdd(callbackHelper, System::IntPtr(new StyleImageMissingCallback(done)));
            
            StyleImageMissingHandler->Invoke(
                Convert::ToSystemString(id),
                gcnew DOTNET_NAMESPACE::RendererObserver::StyleImageMissingCallback(
                    callbackHelper,
                    &StyleImageMissingCallbackHelper::StyleImageMissingCallbackHandler
                )
            );
        }
    }

    void NativeRendererObserver::onRemoveUnusedStyleImages(const std::vector<std::string>& unusedImageIDs)
    {
        if (static_cast<DOTNET_NAMESPACE::RendererObserver::RemoveUnusedStyleImagesHandler^>(RemoveUnusedStyleImagesHandler))
        {
            RemoveUnusedStyleImagesHandler->Invoke(
                Convert::ToSystemIEnumerable<std::string, System::String^>(
                    unusedImageIDs,
                    &Convert::ToSystemString
                )
            );
        }
    }

    void NativeRendererObserver::onRegisterShaders(mbgl::gfx::ShaderRegistry& shaderRegistry)
    {
        if (static_cast<DOTNET_NAMESPACE::RendererObserver::RegisterShadersHandler^>(RegisterShadersHandler))
        {
            RegisterShadersHandler->Invoke(
                gcnew ShaderRegistry(ShaderRegistry::CreateNativePointerHolder(&shaderRegistry, false))
            );
        }
    }

    void NativeRendererObserver::StyleImageMissingCallbackHandler(StyleImageMissingCallbackHelper^ callbackHelper)
    {
        System::IntPtr callbackPtr;

        _PendingCallbacks->TryRemove(callbackHelper, callbackPtr);
        (*reinterpret_cast<StyleImageMissingCallback*>(callbackPtr.ToPointer()))();
    }
}
