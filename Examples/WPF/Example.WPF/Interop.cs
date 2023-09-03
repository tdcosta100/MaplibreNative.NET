using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Example.WPF
{
    using GLuint = System.UInt32;
    using GLenum = System.UInt32;
    using GLbitfield = System.UInt32;
    using GLint = System.Int32;
    using GLsizei = System.Int32;
    using GLfloat = System.Single;

    public enum PixelFormatDescriptorFlags : uint
    {
        PFD_DRAW_TO_WINDOW = 0x00000004,
        PFD_DRAW_TO_BITMAP = 0x00000008,
        PFD_SUPPORT_GDI = 0x00000010,
        PFD_SUPPORT_OPENGL = 0x00000020,
        PFD_GENERIC_ACCELERATED = 0x00001000,
        PFD_GENERIC_FORMAT = 0x00000040,
        PFD_NEED_PALETTE = 0x00000080,
        PFD_NEED_SYSTEM_PALETTE = 0x00000100,
        PFD_DOUBLEBUFFER = 0x00000001,
        PFD_STEREO = 0x00000002,
        PFD_SWAP_LAYER_BUFFERS = 0x00000800
    }

    public enum PixelType : byte
    {
        PFD_TYPE_RGBA = 0,
        PFD_TYPE_COLORINDEX = 1
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct PixelFormatDescriptor
    {
        public ushort Size;
        public ushort Version;
        public PixelFormatDescriptorFlags Flags;
        public PixelType PixelType;
        public byte ColorBits;
        public byte RedBits;
        public byte RedShift;
        public byte GreenBits;
        public byte GreenShift;
        public byte BlueBits;
        public byte BlueShift;
        public byte AlphaBits;
        public byte AlphaShift;
        public byte AccumBits;
        public byte AccumRedBits;
        public byte AccumGreenBits;
        public byte AccumBlueBits;
        public byte AccumAlphaBits;
        public byte DepthBits;
        public byte StencilBits;
        public byte AuxBuffers;
        public byte LayerType;
        private byte Reserved;
        public uint LayerMask;
        public uint VisibleMask;
        public uint DamageMask;

        //Use this function to make a new one with Size and Version already filled in.
        public static PixelFormatDescriptor Build()
        {
            var pfd = new PixelFormatDescriptor
            {
                Size = (ushort)Marshal.SizeOf(typeof(PixelFormatDescriptor)),
                Version = 1
            };

            return pfd;
        }
    }

    public class Gdi32
    {
        [DllImport("gdi32.dll", SetLastError = true)]
        public static extern int ChoosePixelFormat(nint hdc, [In] ref PixelFormatDescriptor pfd);

        [DllImport("gdi32.dll", SetLastError = true)]
        public static extern bool SetPixelFormat(nint hdc, int format, [In] ref PixelFormatDescriptor pfd);
    }

    public class User32
    {
        [DllImport("user32.dll", SetLastError = true)]
        public static extern nint GetDC([In] nint hWnd);
    }

    public class OpenGL32
    {
        public const GLenum GL_DEPTH_BUFFER_BIT = 0x100;
        public const GLenum GL_STENCIL_BUFFER_BIT = 0x400;
        public const GLenum GL_COLOR_BUFFER_BIT = 0x4000;

        public const GLenum GL_UNSIGNED_BYTE = 0x1401;
        public const GLenum GL_DEPTH_COMPONENT = 0x1902;
        public const GLenum GL_RGBA = 0x1908;

        public const GLenum GL_RGBA4 = 0x8056;
        public const GLenum GL_RGBA8 = 0x8058;

        public const GLenum GL_READ_FRAMEBUFFER = 0x8CA8;
        public const GLenum GL_DRAW_FRAMEBUFFER = 0x8CA9;
        public const GLenum GL_FRAMEBUFFER_COMPLETE = 0x8CD5;
        public const GLenum GL_COLOR_ATTACHMENT0 = 0x8CE0;
        public const GLenum GL_DEPTH_ATTACHMENT = 0x8D00;
        public const GLenum GL_FRAMEBUFFER = 0x8D40;
        public const GLenum GL_RENDERBUFFER = 0x8D41;

        [DllImport("opengl32.dll", SetLastError = true)]
        public static extern nint wglCreateContext(nint hDC);

        [DllImport("opengl32.dll", SetLastError = true)]
        public static extern bool wglDeleteContext(nint hGLRC);

        [DllImport("opengl32.dll", SetLastError = true)]
        public static extern bool wglMakeCurrent(nint hDC, nint hGLRC);

        [DllImport("opengl32.dll", CharSet = CharSet.Ansi, SetLastError = true)]
        public static extern nint wglGetProcAddress(string procName);

        public delegate void glGenFramebuffersDelegate(GLsizei n, GLuint[] ids);
        public delegate void glGenRenderbuffersDelegate(GLsizei n, GLuint[] renderbuffers);
        public delegate void glBindFramebufferDelegate(GLenum target, GLuint framebuffer);
        public delegate void glBindRenderbufferDelegate(GLenum target, GLuint renderbuffer);
        public delegate void glRenderbufferStorageDelegate(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
        public delegate void glFramebufferRenderbufferDelegate(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
        public delegate GLenum glCheckFramebufferStatusDelegate(GLenum target);
        public delegate void glReadBufferDelegate(GLenum mode);
        public delegate void glReadPixelsDelegate(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, nint data);

        public static glGenFramebuffersDelegate? glGenFramebuffers;
        public static glGenRenderbuffersDelegate? glGenRenderbuffers;
        public static glBindFramebufferDelegate? glBindFramebuffer;
        public static glBindRenderbufferDelegate? glBindRenderbuffer;
        public static glRenderbufferStorageDelegate? glRenderbufferStorage;
        public static glFramebufferRenderbufferDelegate? glFramebufferRenderbuffer;
        public static glCheckFramebufferStatusDelegate? glCheckFramebufferStatus;
        public static glReadBufferDelegate? glReadBuffer;
        public static glReadPixelsDelegate? glReadPixels;

        public static nint HModule = nint.Zero;

        public static T GetProcAddress<T>(string name)
        {
            if (HModule == nint.Zero)
            {
                HModule = Kernel32.LoadLibrary("opengl32.dll");
            }

            var result = wglGetProcAddress(name);

            if (result == nint.Zero)
            {
                result = Kernel32.GetProcAddress(HModule, name);
            }

            return Marshal.GetDelegateForFunctionPointer<T>(result);
        }

        public static void Init()
        {
            glGenFramebuffers = GetProcAddress<glGenFramebuffersDelegate>("glGenFramebuffers");
            glGenRenderbuffers = GetProcAddress<glGenRenderbuffersDelegate>("glGenRenderbuffers");
            glBindFramebuffer = GetProcAddress<glBindFramebufferDelegate>("glBindFramebuffer");
            glBindRenderbuffer = GetProcAddress<glBindRenderbufferDelegate>("glBindRenderbuffer");
            glRenderbufferStorage = GetProcAddress<glRenderbufferStorageDelegate>("glRenderbufferStorage");
            glFramebufferRenderbuffer = GetProcAddress<glFramebufferRenderbufferDelegate>("glFramebufferRenderbuffer");
            glCheckFramebufferStatus = GetProcAddress<glCheckFramebufferStatusDelegate>("glCheckFramebufferStatus");
            glReadBuffer = GetProcAddress<glReadBufferDelegate>("glReadBuffer");
            glReadPixels = GetProcAddress<glReadPixelsDelegate>("glReadPixels");
        }
    }

    public class Kernel32
    {
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, EntryPoint = "LoadLibraryW", SetLastError = true)]
        public static extern nint LoadLibrary([In] string lpLibFileName);

        [DllImport("kernel32.dll", CharSet = CharSet.Ansi, SetLastError = true)]
        public static extern nint GetProcAddress(nint hModule, string procName);
    }
}
