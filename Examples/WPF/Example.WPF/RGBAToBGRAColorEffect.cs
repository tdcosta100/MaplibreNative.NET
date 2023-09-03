using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows;
using System.Windows.Media.Effects;

namespace Example.WPF
{
    public class RGBAToBGRAColorEffect : ShaderEffect
    {
        private const string _Base64Code = "AAL///7/IgBDVEFCHAAAAE8AAAAAAv//AQAAABwAAAAAAQAASAAAADAAAAADAAAAAQACADgAAAAAAAAAaW5wdXQAq6sEAAwAAQABAAEAAAAAAAAAcHNfMl8wAE1pY3Jvc29mdCAoUikgSExTTCBTaGFkZXIgQ29tcGlsZXIgMTAuMC4xMDAxMS4xNjM4NACrHwAAAgAAAIAAAAOwHwAAAgAAAJAACA+gQgAAAwAAD4AAAOSwAAjkoAEAAAIBAAmAAADSgAEAAAIBAASAAAAAgAEAAAIBAAKAAABVgAEAAAIACA+AAQDkgP//AAA=";
        private static readonly PixelShader _Shader;

        static RGBAToBGRAColorEffect()
        {
            _Shader = new PixelShader();
            _Shader.SetStreamSource(new MemoryStream(Convert.FromBase64String(_Base64Code)));
        }

        public static readonly DependencyProperty InputProperty = RegisterPixelShaderSamplerProperty("Input", typeof(RGBAToBGRAColorEffect), 0);

        public Brush Input
        {
            get { return (Brush)GetValue(InputProperty); }
            set { SetValue(InputProperty, value); }
        }

        public RGBAToBGRAColorEffect()
        {
            PixelShader = _Shader;
            UpdateShaderValue(InputProperty);
        }
    }
}
