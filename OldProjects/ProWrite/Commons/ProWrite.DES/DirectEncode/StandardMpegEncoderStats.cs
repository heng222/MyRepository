namespace DirectEncodeNET
{
    using System.Runtime.InteropServices;

    [ComImport, Guid("C9510218-F457-4D51-8389-7386E6EDD0EF"), CoClass(typeof(StandardMpegEncoderStatsClass))]
    public interface StandardMpegEncoderStats : IStandardMpegEncoderStats
    {
    }
}

