namespace DirectEncodeNET
{
    using System.Runtime.InteropServices;

    [ComImport, Guid("B196B28D-BAB4-101A-B69C-00AA00341D07"), CoClass(typeof(StandardMpegEncoderVideoPropsClass))]
    public interface StandardMpegEncoderVideoProps : IPropertyPage
    {
    }
}

