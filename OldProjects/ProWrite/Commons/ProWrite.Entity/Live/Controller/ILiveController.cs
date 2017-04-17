using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ProWrite.Entity.Live.Controller
{
    public interface ILiveController:IEnumerable<LiveItem>
    {
        LiveItem GetByName(string name);
        LiveItem GetById(string id);
        /// <summary>
        /// and library item
        /// </summary>
        /// <param name="item"></param>
        bool Add(LiveItem item);
        /// <summary>
        /// remove library item
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        bool Remove(LiveItem item);
        /// <summary>
        /// update library item
        /// </summary>
        /// <param name="item"></param>
        bool Update(LiveItem item);
        /// <summary>
        /// is contains library item
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        bool Contains(LiveItem item);

        bool Contains(string name);

        bool Rename(string newName, string oldName);
    }

    /// <summary>
    /// Generic library controller interface
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public interface ILiveController<T> : ILiveController where T : LiveItem
    {
        new T GetByName(string name);
        new T GetById(string id);
        /// <summary>
        /// and library item
        /// </summary>
        /// <param name="item"></param>
        bool Add(T item);
        /// <summary>
        /// remove library item
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        bool Remove(T item);
        /// <summary>
        /// update library item
        /// </summary>
        /// <param name="item"></param>
        bool Update(T item);
        /// <summary>
        /// is contains library item
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        bool Contains(T item);
    }

    /// <summary>
    /// Library event args class
    /// </summary>
    public class LiveEventArgs : EventArgs
    {
        public readonly LiveItem Item;
        public LiveEventArgs(LiveItem item)
        {
            Item = item;
        }
    }
}
