
using System;
using System.Drawing;
using System.Runtime.InteropServices;
using NUnit.Framework;

namespace CSharpLearning
{

    // Design pattern for the base class.
    // By implementing IDisposable, you are announcing that instances
    // of this type allocate scarce resources.
    public class BaseResource : IDisposable
    {
        // Track whether Dispose has been called.
        private bool _disposed;
        // Unmanaged resource
        private IntPtr _unmanagedResource;
        // IDisposable managed resources
        private Bitmap _bitmap; 

        // Constructor for the BaseResource object.
        public BaseResource()
        {
            _unmanagedResource = Marshal.AllocCoTaskMem(100);
            _bitmap = new Bitmap(50, 50);
            _disposed = false;
        }

        // Use C# destructor syntax for finalization code.
        // This destructor will run only if the Dispose method 
        // does not get called.
        // It gives your base class the opportunity to finalize.
        // Do not provide destructors in types derived from this class.
        ~BaseResource()
        {
            // Do not re-create Dispose clean-up code here.
            // Calling Dispose(false) is optimal in terms of
            // readability and maintainability.
            Dispose(false);
        }

        // Implement IDisposable.
        // Do not make this method virtual.
        // A derived class should not be able to override this method.
        void IDisposable.Dispose()
        {
            Dispose(true);

            // Take yourself off the Finalization queue 
            // to prevent finalization code for this object
            // from executing a second time.
            GC.SuppressFinalize(this);
        }

        // Dispose(bool disposing) executes in two distinct scenarios.
        // If disposing equals true, the method has been called directly
        // or indirectly by a user's code. Managed and unmanaged resources
        // can be disposed.
        // If disposing equals false, the method has been called by the 
        // runtime from inside the finalizer and you should not reference 
        // other objects. Only unmanaged resources can be disposed.
        protected virtual void Dispose(bool disposing)
        {
            // Check to see if Dispose has already been called.
            if (!_disposed)
            {
                // If disposing equals true, dispose all managed 
                // and unmanaged resources.
                if (disposing)
                {
                    // Dispose managed resources.
                    _bitmap.Dispose();
                }

                // Release unmanaged resources. If disposing is false, 
                // only the following code is executed.
                Marshal.FreeCoTaskMem(_unmanagedResource);

                _disposed = true;

                // Note that this is not thread safe.
                // Another thread could start disposing the object
                // after the managed resources are disposed,
                // but before the disposed flag is set to true.
                // If thread safety is necessary, it must be
                // implemented by the client.

            }
        }

        // Allow your Dispose method to be called multiple times,
        // but throw an exception if the object has been disposed.
        // Whenever you do something with this class, 
        // check to see if it has been disposed.
        public void DoSomething()
        {
            if (_disposed)
            {
                throw new ObjectDisposedException("Error");
            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Close()
        {
            ((IDisposable)this).Dispose();
        }
    }

    /// <summary>
    /// 
    /// </summary>
    public class DerivedResource : BaseResource
    {
        private IntPtr _anotherMemory;
        private Bitmap _anotherImage;
        private bool _disposed;

        public DerivedResource()
        {
            _anotherMemory = Marshal.AllocCoTaskMem(20);
            _anotherImage = new Bitmap(24, 24);
        }

        protected override void Dispose(bool isDisposing)
        {
            if (!_disposed)
            {
                if (isDisposing)
                {
                    _anotherImage.Dispose();
                }

                Marshal.FreeCoTaskMem(_anotherMemory);

                base.Dispose(isDisposing);

                _disposed = true;
            }
        }
    }

    [TestFixture]
    internal class IDisposableTest
    {
        [Test]
        public void Test1()
        {
            BaseResource aStream = new DerivedResource();

            aStream.Close(); // Allowed
            // aStream.Dispose(); // Cannot compile

            ((IDisposable)aStream).Dispose(); // Allowed

            //
            // This one works as well, because newStream calls the explicit implemented
            // IDisposable.Dispose method
            //
            using (BaseResource newStream = new DerivedResource())
            {
                //
                // Do something
                //
            }

        }


        [Test]
        public void Test2()
        {
            for (int i = 0; i < 1000; i++ )
            {
                Console.WriteLine(i);
                System.Threading.Thread.Sleep(1000);
            }
        }

        public void Test3()
        {
            BaseResource aStream = new DerivedResource();
            aStream.DoSomething();
        }

    }
}
