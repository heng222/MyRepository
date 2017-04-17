using System;
using System.Collections.Generic;
using System.Text;
using ProWrite.Entity;
using ProWrite.Entity.Dashboard;

namespace ProWrite.Commons.Test
{
    class MemoryDataProvider:IDataProvider
    {
        private ProjectInfo _entitySet = new ProjectInfo();

        private MemoryDataProvider()
        {
            for (int i = 1; i < 6; i++)
            {
                SignInfo sign = new SignInfo();
                sign.Name = "Sign" + i;
                _entitySet.RootGroup.AddSign(sign);
            }

            for (int i = 1; i < 6; i++)
            {
                SignGroupInfo group = new SignGroupInfo();
                group.Name = "Group" + i;
                for (int j = 1; j <= i; j++)
                {
                    SignInfo sign = new SignInfo();
                    sign.Name = "Sign" + j;
                    group.AddSign(sign);
                    sign.Parent = group;

                    SignGroupInfo subGroup = new SignGroupInfo();
                    subGroup.Name = "SubGroup" + j;
                    group.AddGroup(subGroup);
                    subGroup.Parent = group;

                }
                _entitySet.RootGroup.AddGroup(group);
            }


        }

        public static readonly MemoryDataProvider Instance = new MemoryDataProvider();

        public ProjectInfo GetEntitySet()
        {
            return _entitySet;
        }

        public object Get()
        {
            return _entitySet;
        }

        public bool Update(ProjectInfo entitySet)
        {
            return true;
        }

        public bool Update()
        {
            return true;
        }

        public void Dispose()
        {
        }
        #region IDataProvider ³ÉÔ±


        public bool Update(object data)
        {
            throw new Exception("The method or operation is not implemented.");
        }

        #endregion
    }
}
