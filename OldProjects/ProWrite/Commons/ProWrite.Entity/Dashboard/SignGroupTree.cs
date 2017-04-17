using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.Serialization;
using ProWrite.Entity.Dashboard;

namespace ProWrite.Entity.Dashboard
{
	[Serializable]
	public class SignGroupTree : SignGroupInfo
	{
		public override void Clear()
		{
			base.Clear();
			_allSigns.Clear();
			_allGroups.Clear();
		}

		public override bool IsChanged
		{
			get
			{
				if (_allSigns.Count > 0)
				{
					foreach (SignInfo item in _allSigns)
					{
						if (item.IsChanged)
							return true;
					}
				}

				if (_allGroups.Count > 0)
				{
					foreach (SignGroupInfo item in _allGroups)
						if (item.IsChanged)
							return true;
				}

				return false;
			}
		}

		public override void AcceptChanges()
		{
			if (_allSigns.Count > 0)
			{
				foreach (SignInfo item in _allSigns)
					item.AcceptChanges();
			}

			if (_allGroups.Count > 0)
			{
				foreach (SignGroupInfo item in _allGroups)
					item.AcceptChanges();
			}
		}

		public override bool IsRoot
		{
			get
			{
				return true;
			}
		}

		public override string Name
		{
			get
			{
				return "";
			}
			set
			{
			}
		}

		public override string ToString()
		{
			return "";
		}

		public void PopulateRelation()
		{
			PopulateRelation(Groups, this);
			if (Signs.Length > 0)
			{
				_allSigns.AddRange(Signs);
				foreach (DashboardItem item in Signs)
					item.Parent = this;
			}
		}

		private static void PopulateRelation(SignGroupInfo[] items, SignGroupInfo parent)
		{
			if (items.Length > 0)
			{
				_allGroups.AddRange(items);
				foreach (SignGroupInfo group in items)
				{
					group.Parent = parent;

					PopulateRelation(group.Groups, group);

					if (group.Signs.Length > 0)
					{
						_allSigns.AddRange(group.Signs);
						foreach (SignInfo sign in group.Signs)
							sign.Parent = group;
					}
				}
			}
		}

		//[OnDeserialized]
		//private void Deserialized(StreamingContext ctx)
		//{
		//    AddDefaultItem();
		//}

		//internal void AddDefaultItem()
		//{
		//    if (AllSigns.Length < 1)
		//    {
		//        SignInfo defaultSign = new SignInfo();
		//        defaultSign.Name = "defautl Sign";
		//        defaultSign.Type = SignType.RGB;
		//        defaultSign.Active = true;
		//        this.AddSign(defaultSign);
		//    }
		//}

	}
}