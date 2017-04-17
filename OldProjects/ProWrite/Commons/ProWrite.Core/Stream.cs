using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml.Serialization;
using System.ComponentModel;

namespace ProWrite.Core
{
    public class StreamWrapper : Stream
    {
        private Stream _stream;

        protected StreamWrapper(Stream stream)
        {
            if (stream == null)
                throw new ArgumentNullException("stream");
            _stream = stream;
        }

        protected Stream ContainedStream { get { return _stream; } }

        public override bool CanRead { get { return _stream.CanRead; } }

        public override bool CanSeek { get { return _stream.CanSeek; } }

        public override bool CanWrite { get { return _stream.CanWrite; } }

        public override void Flush() { _stream.Flush(); }

        public override long Length { get { return _stream.Length; } }

        public override long Position
        {
            get { return _stream.Position; }
            set { _stream.Position = value; }
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            return _stream.Read(buffer, offset, count);
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            return _stream.Seek(offset, origin);
        }

        public override void SetLength(long value)
        {
            _stream.SetLength(value);
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            _stream.Write(buffer, offset, count);
        }

    }

    public class ProgressStream : StreamWrapper
    {
        private int _lastProgress = 0;

        public ProgressStream(Stream stream)
            : base(stream)
        {
            if (!stream.CanRead || !stream.CanSeek || stream.Length <= 0)
                throw new ArgumentException("stream");
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            int amountRead = base.Read(buffer, offset, count);
            OnProgressChanged();
            return amountRead;
        }

        [NonSerialized]
        [XmlIgnore]
        private ProgressChangedEventHandler _progressChanged;
        public event ProgressChangedEventHandler ProgressChanged
        {
            add { _progressChanged += value; }
            remove { _progressChanged -= value; }
        }

        protected virtual void OnProgressChanged()
        {
            if (_progressChanged != null)
            {
                int newProgress = (int)(Position * 100.0 / Length);
                if (newProgress > _lastProgress)
                {
                    _lastProgress = newProgress;
                    _progressChanged(this,
                        new ProgressChangedEventArgs(_lastProgress, null));
                }
            }
        }
    }
}
