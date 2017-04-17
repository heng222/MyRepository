

#ifndef _INBASEOBSERVER_H_43E06336_0A6E_493c_A376_457E19E1EE0C
#define _INBASEOBSERVER_H_43E06336_0A6E_493c_A376_457E19E1EE0C
//////////////////////////////////////////////////////////////////////////
#include "AppLog.h"

/// <summary>
/// NBASE library observer
/// </summary>
interface INBaseObserver
{

    /// <summary>
    /// Before launching NBASE
    /// </summary>
    virtual void OnLaunching() = 0;

    /// <summary>
    /// This action occurs between modules initialized
    /// and modules starting when NBASE launch.
    /// </summary>
    virtual void OnStarting() = 0;

    /// <summary>
    /// On launch NBASE completely.
    /// </summary>
    virtual void OnLaunched() = 0;

    /// <summary>
    /// On receiving an application log.
    /// </summary>
    /// <param name="log">application log</param>
    virtual void OnRevcAppLog(CAppLog* log) = 0;

    /// <summary>
    /// On Dispathing message. This event happens when call NBASE.SendMessage or NBASE.PostMessage.
    /// </summary>
    /// <param name="msg">IMC message.</param>
    /// <returns>true means the message has been handled, no need to dispath any more, otherwise NBASE will
    /// dispath the message to an appropriate module.</returns>
    virtual bool PreDispatchMessage(CImcMessage* msg) = 0;

    /// <summary>
    /// Occurs before terminate NBASE library.
    /// </summary>
    virtual void OnTerminate() = 0;
};

//////////////////////////////////////////////////////////////////////////

#endif
