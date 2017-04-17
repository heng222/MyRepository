namespace DirectEncodeNET
{
    using System.Runtime.InteropServices;

    [ComImport, CoClass(typeof(StandardMpegEncoderProfileClass)), Guid("182EB270-5FA5-46E8-83BA-40F7205C545B")]
    public interface StandardMpegEncoderProfile : IStandardMpegEncoderProfile
    {
    }
}

