using Framework.OSGi;
using Platform.Bundles.Bridge;

namespace Products.UAC.Bridge
{
    /// <summary>
    /// Bundle规约实现。
    /// </summary>
    class BundleSpecification : IBundleSpecification
    {
        public bool IsSatisifedBy(IBundle bundle)
        {
            return true;
        }
    }
}
