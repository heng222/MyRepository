namespace DirectEncodeNET
{
    using System.Runtime.InteropServices;

    [ComImport, Guid("91D3D934-6DEE-42C5-A687-6F81E1162559"), CoClass(typeof(StandardMpegEncoderClass))]
    public interface StandardMpegEncoder : IStandardMpegEncoder
    {
    }
}

