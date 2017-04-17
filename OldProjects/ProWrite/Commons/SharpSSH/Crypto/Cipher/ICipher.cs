using System;
namespace Tamir.SharpSsh.jsch
{
    interface ICipher
    {
        int getBlockSize();
        int getIVSize();
        void init(int mode, byte[] key, byte[] iv);
        void update(byte[] foo, int s1, int len, byte[] bar, int s2);
    }
}
