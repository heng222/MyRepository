using System;
using System.Collections.Generic;
using System.Text;
using DirectShowLib;
using DirectShowLib.DES;
using ProWrite.Core;

namespace ProWrite.DES
{
	/// <summary>
	/// Time£º2008-9-15
	/// Author£ºMichael
	/// Function£ºThis Class set Sign Color
	/// Update£º
	/// </summary>
	public sealed class DESSign
	{
		public static IPropertySetter GetPropertySetterBySign(SignType pSignType)
		{
			switch (pSignType)
			{
				case SignType.RGB:
					return RGB();
                //case SignType.Red:
                //    return Red();
                //case SignType.Amber:
                //    return Amber();
				default:
					return RGB();
			}
		}

		private static IPropertySetter RGB()
		{
			IPropertySetter ipro = (IPropertySetter)new PropertySetter();
			DESHelper.AddParameter(ipro, "InternalName", "Standard");
			return ipro;
		}

		private static IPropertySetter Red()
		{
			IPropertySetter ipro = (IPropertySetter)new PropertySetter();
			DESHelper.AddParameter(ipro, "InternalName", "Standard");
			DESHelper.AddParameter(ipro, "Red", "1.0");
			return ipro;
		}

		private static IPropertySetter Amber()
		{
			IPropertySetter ipro = (IPropertySetter)new PropertySetter();
			DESHelper.AddParameter(ipro, "InternalName", "Standard");
			//DESHelper.AddParameter(ipro, "Desaturate", "true");
			DESHelper.AddParameter(ipro, "Red", "0.1");
			DESHelper.AddParameter(ipro, "Magenta", "0.09");
			DESHelper.AddParameter(ipro, "Yellow", "0.25");
			//DESHelper.AddParameter(ipro, "contrast", "1.0");
			return ipro;
		}
	}
}