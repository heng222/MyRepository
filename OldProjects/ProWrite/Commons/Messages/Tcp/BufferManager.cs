using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;


namespace System.Net.Tcp
{
    public class BufferManager:DisposableObject
    {
        int totalbytes;
        byte[] buffer;
        Stack<int> freeIndexPool;
        int currentIndex;
        int bufferSize;

        public BufferManager(int buffers, int bufferSize)
        {
            this.totalbytes = buffers * bufferSize;
            this.bufferSize = bufferSize;

            currentIndex = 0;
            freeIndexPool = new Stack<int>();
            buffer = new byte[totalbytes];
        }

        public void SetBuffer(SocketAsyncEventArgs args)
        {
            if (freeIndexPool.Count > 0)
                args.SetBuffer(buffer, freeIndexPool.Pop(), bufferSize);
            else
            {
                args.SetBuffer(buffer, currentIndex, bufferSize);
                currentIndex += bufferSize;
            }
        }

        public void FreeBuffer(SocketAsyncEventArgs args)
        {
            freeIndexPool.Push(args.Offset);
            args.SetBuffer(null, 0, 0);
        }

        protected override void Dispose(bool disposing)
        {
            if (freeIndexPool != null)
            {
                freeIndexPool.Clear();
                freeIndexPool = null;
            }

            if (buffer != null)
            {
                Array.Clear(buffer, 0, buffer.Length);
                buffer = null;
            }

            base.Dispose(disposing);

        }
    }
}
