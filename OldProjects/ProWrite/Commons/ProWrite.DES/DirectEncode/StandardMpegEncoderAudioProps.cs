namespace DirectEncodeNET
{
    using System.Runtime.InteropServices;

    [ComImport, CoClass(typeof(StandardMpegEncoderAudioPropsClass)), Guid("B196B28D-BAB4-101A-B69C-00AA00341D07")]
    public interface StandardMpegEncoderAudioProps : IPropertyPage
    {
    }
}

