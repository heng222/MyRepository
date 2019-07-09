using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Products.Infrastructure.Entities
{
    /// <summary>
    /// 实体基类
    /// </summary>
    [Serializable]
    public abstract class Entity
    {
        /// <summary>
        /// 默认构造函数。
        /// </summary>
        protected Entity()
        {
        }
    }
}
