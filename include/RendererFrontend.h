#pragma once

namespace DOTNET_NAMESPACE
{
    ref class RendererObserver;
    ref class UpdateParameters;

    /// <summary>
    /// The RenderFrontend is the bridge between the Map and
    /// platform used to update and observer the Renderer
    ///
    /// It hides any threading specifics and always replies on
    /// the original thread.
    /// </summary>
    public interface class IRendererFrontend
    {
        /// <summary>
        /// Must synchronously clean up the Renderer if set
        /// </summary>
        /// <returns></returns>
        System::Void Reset();

        /// <summary>
        /// Implementer must bind the renderer observer to the renderer in a
        /// appropriate manner so that the callbacks occur on the main thread
        /// </summary>
        /// <param name="observer"></param>
        /// <returns></returns>
        System::Void SetObserver(RendererObserver^ observer);

        /// <summary>
        /// Coalescing updates is up to the implementer
        /// </summary>
        /// <param name="parameters"></param>
        /// <returns></returns>
        System::Void Update(UpdateParameters^ parameters);

        System::IntPtr GetNativePointer();
    };
}
