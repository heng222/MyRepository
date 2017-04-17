using System;
using System.Collections.Generic;
using System.Text;

namespace System.Communication.Messaging
{
    /// <summary>
    /// Embedded or distributed message bus manager interface
    /// </summary>
    public interface IMessageRouter
    {
        /// <summary>
        /// Get or set message sending and receiving mode
        /// </summary>
        AsyncMessageMode AsyncMessageMode
        {
            get;
            set;
        }
        /// <summary>
        /// Whether or not to include the type's Subject
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        bool ContainSubject(Type type);
        /// <summary>
        /// Get the specified type's Subject
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        Subject this[Type type] { get;}
        /// <summary>
        /// Get or register Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <returns></returns>
        Subject<TMessage> Subject<TMessage>();
        /// <summary>
        /// Get or register Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <returns></returns>
        Subject<TMessage> Subject<TMessage>(object sender);
        /// <summary>
        /// Remove specified type's Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        void Remove<TMessage>();
        /// <summary>
        /// Remove specified type's Subject
        /// </summary>
        /// <param name="type"></param>
        void Remove(Type type);
        /// <summary>
        /// Get or register Subject,and register a Observer in the Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <param name="handler"></param>
        void Register<TMessage>(ObserverHandler<TMessage> handler);
        /// <summary>
        /// Get or register Subject,and register a Observer in the Subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <param name="handler"></param>
        void Register<TMessage>(object sender, ObserverHandler<TMessage> handler);
        /// <summary>
        /// Write off an Observer in subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <param name="handler"></param>
        void Unregister<TMessage>(ObserverHandler<TMessage> handler);
        /// <summary>
        /// Write off an Observer in subject
        /// </summary>
        /// <typeparam name="TMessage"></typeparam>
        /// <param name="handler"></param>
        void Unregister<TMessage>(object sender, ObserverHandler<TMessage> handler);
        /// <summary>
        /// Get the amount of the Subject
        /// </summary>
        int Count
        {
            get;
        }
        /// <summary>
        /// Get subject type collection
        /// </summary>
        Type[] Types
        {
            get;
        }
        /// <summary>
        /// Register Hook
        /// </summary>
        /// <param name="listner"></param>
        void RegisterHook(params IHook[] hooks);
        /// <summary>
        /// Write off Hook
        /// </summary>
        /// <param name="listner"></param>
        void UnRegisterHook(params IHook[] hooks);
        /// <summary>
        /// Message issuance
        /// </summary>
        /// <param name="sender">Message sender</param>
        /// <param name="msg">Message</param>
        void Send(object sender, object msg);
        /// <summary>
        /// Message issuance
        /// </summary>
        /// <param name="sender">Message sender</param>
        /// <param name="msg">message</param>
        /// <param name="isAsync">whether or not to send asynchronously</param>
        void Send(object sender, object msg, bool isAsync);
        /// <summary>
        /// Call the client's callback function directly, often used in  Message Hook intercept processing
        /// </summary>
        /// <param name="mea"></param>
        void SendMessage(MessagePacket mea);
    }

    public interface IMessageRouter<TMessage> : IMessageRouter
    {
        /// <summary>
        /// Message issuance
        /// </summary>
        /// <param name="sender">Message sender</param>
        /// <param name="msg">Message</param>
        void Send(object sender, TMessage msg);
        /// <summary>
        /// Message issuance
        /// </summary>
        /// <param name="sender">Message sender</param>
        /// <param name="msg">Message</param>
        /// <param name="isAsync">whether or not to send asynchronously</param>
        void Send(object sender, TMessage msg, bool isAsync);
    }

    /// <summary>
    /// Support PostMessage router
    /// </summary>
    /// <typeparam name="TMessage"></typeparam>
    public interface IPriortyMessageRouter<TMessage> : IMessageRouter<TMessage> where TMessage : IComparable<TMessage>
    {
        /// <summary>
        /// Get or set message Queue processing interval
        /// </summary>
        int MillisecondsTimeout { get; set;}
        /// <summary>
        /// Post the Message to priority message queue把消息投入到优先消息队列中
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="msg"></param>
        void Post(object sender, TMessage msg);
    }
}
