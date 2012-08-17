/* ***** BEGIN LICENSE BLOCK *****
 * 
 * Portions Copyright (c) 1995-2008 RealNetworks, Inc. All Rights Reserved.
 * 
 * The contents of this file, and the files included with this file,
 * are subject to the current version of the RealNetworks Public
 * Source License (the "RPSL") available at
 * http://www.helixcommunity.org/content/rpsl unless you have licensed
 * the file under the current version of the RealNetworks Community
 * Source License (the "RCSL") available at
 * http://www.helixcommunity.org/content/rcsl, in which case the RCSL
 * will apply. You may also obtain the license terms directly from
 * RealNetworks.  You may not use this file except in compliance with
 * the RPSL or, if you have a valid RCSL with RealNetworks applicable
 * to this file, the RCSL.  Please see the applicable RPSL or RCSL for
 * the rights, obligations and limitations governing use of the
 * contents of the file.
 * 
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License Version 2 (the
 * "GPL") in which case the provisions of the GPL are applicable
 * instead of those above. If you wish to allow use of your version of
 * this file only under the terms of the GPL, and not to allow others
 * to use your version of this file under the terms of either the RPSL
 * or RCSL, indicate your decision by deleting the provisions above
 * and replace them with the notice and other provisions required by
 * the GPL. If you do not delete the provisions above, a recipient may
 * use your version of this file under the terms of any one of the
 * RPSL, the RCSL or the GPL.
 * 
 * This file is part of the Helix DNA Technology. RealNetworks is the
 * developer of the Original Code and owns the copyrights in the
 * portions it created.
 * 
 * This file, and the files included with this file, is distributed
 * and made available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS
 * ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET
 * ENJOYMENT OR NON-INFRINGEMENT.
 * 
 * Technology Compatibility Kit Test Suite(s) Location:
 *    http://www.helixcommunity.org/content/tck
 * 
 * Contributor(s):
 * 
 * ***** END LICENSE BLOCK ***** */

/////////////////////////////////////////////////////////////////////////////////
//
//  The event defined here is used to percolate information from the bottom to the
//  top in the object hierachy.
//
//  Each event has its own type, sender and receiver classes that encapsulates
//  the dispatch of this specific event. Object wants to send/receive this event
//  needs to inherit from the sender/receiver classes of this event.
//
//  This header defines macros to faciliate creation of new event and its associated
//  classes & utility functions.
//
//  To create a new event(HXFooEvent):
//  1. define the event types(HXFooEvent) in client/include/hxeventtypes.h
//  2. define a new receiver interface(IHXFooEventReceiver) in 
//     client/include/ihxeventreceiver.h, IHXFooEventReceiver needs to be inherited 
//     from IHXEventReceiver    
//  3. define a new sender interface(IHXFooEventSender) in
//     client/include/ihxeventsender.h, IHXFooEventSender needs to be inherited 
//     from *IUnknown*. IHXEventSender is reserved as private interface, it's used when
//     a specific event sender is aggregated by another class(see CRPHelixPlaybackEngine
//     & CRPHelixPlaylistManager)
//  4. create a new header in client_rn/common/pub to define the remaing objects, it
//     looks like this:
//
//     chxfooevent.h
//
//     #include "hxeventtypes.h"
//     #include "hxeventobj.h"
//
//     // CHXFooEvent
//     DEFINE_EVENT_TYPE(HXFooEvent)
//
//     // CHXFooEventSender
//     DEFINE_EVENT_SNDR(HXFooEvent)
//
//     // CHXFooEventReceiver
//     DEFINE_EVENT_RCVR_BEGIN(HXFooEvent)
//          DEFINE_EVENT_RCVR_METHOD1(HXFooEvent, [HXFooEvent_TYPE0], [PARAMETER_TYPE0])
//          DEFINE_EVENT_RCVR_METHOD2(HXFooEvent, [HXFooEvent_TYPE1], [PARAMETER_TYPE0], [PARAMETER_TYPE1])
//          ...
//     DEFINE_EVENT_RCVR_END()
//
//  5. create a new source for the header defined above, it needs to include:
// 
//     chxfooevent.cpp
//
//     IMPLEMENT_EVENT_SNDR(HXFooEvent)
//
//     IMPLEMENT_EVENT_RCVR_BEGIN(HXFooEvent)
//          IMPLEMENT_EVENT_RCVR_METHOD1(HXFooEvent, [HXFooEvent_TYPE0], [PARAMETER_TYPE0])
//          IMPLEMENT_EVENT_RCVR_METHOD2(HXFooEvent, [HXFooEvent_TYPE1], [PARAMETER_TYPE0], [PARAMETER_TYPE1])
//          ...
//      IMPLEMENT_EVENT_RCVR_END()
//
//  The event type(HXFooEvent) passed to all the macros need to be the same as 
//  what's defined in hxeventtypes.h
//
//  To send HXFooEvent, the sender object needs to:
//  1. inherit from CHXFooEventSender
//  2. add IHXFooEventSender to sender's interface table
//  3. call CHXFooEventSender::SendEvent() to send HXFooEvent
//
//  To receive HXFooEvent, the receiver object needs to:
//  1. inherit from CHXFooEventReceiver
//  2. add IHXFooEventReceiver to receiver's interface table
//  3. unless you want to overwrite the default behavior of OnEvent in CHXFooEventReceiver, 
//     you can simply overwrite OnHXFooEvent_xxxx methods for the events you want to handle 
//  4. call HXFooEventSenderUtils::AddReceiver() to start receiving events from the sender of 
//     interest and HXFooEventSenderUtils::RemoveReceiver() to stop receiving events
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef _HXEVENTOBJ_H_
#define _HXEVENTOBJ_H_

#include "ihxeventsender.h"
#include "ihxeventreceiver.h"

#include "hxcomptr.h"
#include <list>
#include <boost/function.hpp>
#include <algorithm>

_INTERFACE IHXEventReceiver;
typedef std::list<IHXEventReceiver*> IHXEventReceiverPtrList;

class CHXBaseEvent
{
public:
    CHXBaseEvent() {};
    virtual ~CHXBaseEvent() {};
    virtual void operator() (IHXEventReceiver* pEventReceiver) const = 0;
};

class CHXEventSender
{
public:
    CHXEventSender() {};
    virtual ~CHXEventSender() {};

protected:
    void    SendEvent(IHXEventReceiverPtrList receivers, const CHXBaseEvent& event);
};

#define DEFINE_EVENT_TYPE(NEW_EVENT)                                                \
class C##NEW_EVENT : public CHXBaseEvent                                            \
{                                                                                   \
public:                                                                             \
    C##NEW_EVENT(NEW_EVENT event, void* pParam1, void* pParam2) :                   \
                 m_event(event),                                                    \
                 m_pParam1(pParam1),                                                \
                 m_pParam2(pParam2)                                                 \
    {};                                                                             \
                                                                                    \
    virtual void operator() (IHXEventReceiver* pEventReceiver) const                \
    {                                                                               \
        SPI##NEW_EVENT##Receiver sp##NEW_EVENT##Receiver(pEventReceiver);           \
                                                                                    \
        if (sp##NEW_EVENT##Receiver)                                                \
        {                                                                           \
            sp##NEW_EVENT##Receiver->OnEvent(m_event, m_pParam1, m_pParam2);        \
        }                                                                           \
    };                                                                              \
                                                                                    \
private:                                                                            \
    NEW_EVENT   m_event;                                                            \
    void*       m_pParam1;                                                          \
    void*       m_pParam2;                                                          \
};                                                                      
   
#define DEFINE_EVENT_SNDR(NEW_EVENT)                                                \
class C##NEW_EVENT##Sender : public CHXEventSender                                  \
                           , public I##NEW_EVENT##Sender                            \
{                                                                                   \
public:                                                                             \
    C##NEW_EVENT##Sender() {};                                                      \
    virtual ~C##NEW_EVENT##Sender() {};                                             \
                                                                                    \
    STDMETHOD(AddReceiver)      (THIS_ I##NEW_EVENT##Receiver* pReceiver);          \
    STDMETHOD(RemoveReceiver)   (THIS_ I##NEW_EVENT##Receiver* pReceiver);          \
                                                                                    \
protected:                                                                          \
    void SendEvent(NEW_EVENT event, void* pParam1 = NULL, void* pParam2 = NULL);    \
                                                                                    \
private:                                                                            \
    IHXEventReceiverPtrList                m_##NEW_EVENT##Receivers;                \
};                                                                                  \
                                                                                    \
namespace NEW_EVENT##SenderUtils                                                    \
{                                                                                   \
    HX_RESULT   AddReceiver(IUnknown* pUnknown, IHXEventReceiver* pReceiver);       \
    HX_RESULT   RemoveReceiver(IUnknown* pUnknown, IHXEventReceiver* pReceiver);    \
};

#define IMPLEMENT_EVENT_SNDR(NEW_EVENT)                                             \
STDMETHODIMP C##NEW_EVENT##Sender::AddReceiver(I##NEW_EVENT##Receiver* pReceiver)   \
{                                                                                   \
    if (!pReceiver)                                                                 \
    {                                                                               \
        return HXR_INVALID_PARAMETER;                                               \
    }                                                                               \
                                                                                    \
    IHXEventReceiverPtrList::iterator iter = std::find(                             \
                                             m_##NEW_EVENT##Receivers.begin(),      \
                                             m_##NEW_EVENT##Receivers.end(),        \
                                             pReceiver);                            \
                                                                                    \
    /* The lifetime of the event receiver should always be longer than the      */  \
    /* lifetime of the event sender.  Therefore we do not call AddRef on the    */  \
    /* event receiver.  This allows us to avoid circular referecnes and having  */  \
    /* to add Init/Terminate calls everywhere to break the references.          */  \
    if (iter == m_##NEW_EVENT##Receivers.end())                                     \
    {                                                                               \
        m_##NEW_EVENT##Receivers.push_back(pReceiver);                              \
    }                                                                               \
                                                                                    \
    return HXR_OK;                                                                  \
}                                                                                   \
                                                                                    \
STDMETHODIMP C##NEW_EVENT##Sender::RemoveReceiver(I##NEW_EVENT##Receiver* pReceiver)\
{                                                                                   \
    if (!pReceiver)                                                                 \
    {                                                                               \
        return HXR_INVALID_PARAMETER;                                               \
    }                                                                               \
                                                                                    \
    IHXEventReceiverPtrList::iterator iter = std::find(                             \
                                             m_##NEW_EVENT##Receivers.begin(),      \
                                             m_##NEW_EVENT##Receivers.end(),        \
                                             pReceiver);                            \
                                                                                    \
    /* The lifetime of the event receiver should always be longer than the      */  \
    /* lifetime of the event sender.  Therefore we do not call Release on       */  \
    /* the event receiver. This allows us to avoid circular referecnes and      */  \
    /* having to add Init/Terminate calls everywhere to break the references.   */  \
    if (iter != m_##NEW_EVENT##Receivers.end())                                     \
    {                                                                               \
        m_##NEW_EVENT##Receivers.erase(iter);                                       \
    }                                                                               \
                                                                                    \
    return HXR_OK;                                                                  \
}                                                                                   \
                                                                                    \
void C##NEW_EVENT##Sender::SendEvent(NEW_EVENT event, void* pParam1,                \
                                     void* pParam2)                                 \
{                                                                                   \
    C##NEW_EVENT    newEvent(event, pParam1, pParam2);                              \
    CHXEventSender::SendEvent(m_##NEW_EVENT##Receivers, newEvent);                  \
}                                                                                   \
                                                                                    \
namespace NEW_EVENT##SenderUtils                                                    \
{                                                                                   \
HX_RESULT AddReceiver(IUnknown* pUnknown, IHXEventReceiver* pEventReceiver)         \
{                                                                                   \
    if (!pUnknown || !pEventReceiver)                                               \
    {                                                                               \
        return HXR_INVALID_PARAMETER;                                               \
    }                                                                               \
                                                                                    \
    SPI##NEW_EVENT##Sender  spEventSender = pUnknown;                               \
    if (spEventSender)                                                              \
    {                                                                               \
        return spEventSender->AddReceiver((I##NEW_EVENT##Receiver*)pEventReceiver); \
    }                                                                               \
                                                                                    \
    return HXR_NOINTERFACE;                                                         \
}                                                                                   \
                                                                                    \
HX_RESULT RemoveReceiver(IUnknown* pUnknown, IHXEventReceiver* pEventReceiver)      \
{                                                                                   \
    if (!pUnknown || !pEventReceiver)                                               \
    {                                                                               \
        return HXR_INVALID_PARAMETER;                                               \
    }                                                                               \
                                                                                    \
    SPI##NEW_EVENT##Sender  spEventSender = pUnknown;                               \
    if (spEventSender)                                                              \
    {                                                                               \
        return spEventSender->RemoveReceiver((I##NEW_EVENT##Receiver*)pEventReceiver);  \
    }                                                                               \
                                                                                    \
    return HXR_NOINTERFACE;                                                         \
}                                                                                   \
};

#define DEFINE_EVENT_RCVR_BEGIN(NEW_EVENT)                                          \
class C##NEW_EVENT##Receiver : public I##NEW_EVENT##Receiver                        \
{                                                                                   \
protected:                                                                          \
    C##NEW_EVENT##Receiver() {};                                                    \
    virtual ~C##NEW_EVENT##Receiver() {};                                           \
                                                                                    \
public:                                                                             \
    STDMETHOD(OnEvent)(THIS_ NEW_EVENT event, void* pParam1, void* pParam2);   

#define DEFINE_EVENT_RCVR_METHOD1(TYPE, NAME, PARAM_1)                              \
    virtual void On##TYPE##_##NAME(PARAM_1 p1) {};

#define DEFINE_EVENT_RCVR_METHOD2(TYPE, NAME, PARAM_1, PARAM_2)                     \
    virtual void On##TYPE##_##NAME(PARAM_1 p1, PARAM_2 p2) {};                    

#define DEFINE_EVENT_RCVR_END()                                                     \
};

#define IMPLEMENT_EVENT_RCVR_BEGIN(NEW_EVENT)                                       \
STDMETHODIMP C##NEW_EVENT##Receiver::OnEvent(NEW_EVENT event, void* p1, void* p2)   \
{                                                                                   \
        switch (event)                                                              \
        {                                                                           \

#define IMPLEMENT_EVENT_RCVR_METHOD1(TYPE, NAME, PARAM_1)                           \
        case TYPE##_##NAME:                                                         \
            On##TYPE##_##NAME(PARAM_1 p1);                                          \
            break;

#define IMPLEMENT_EVENT_RCVR_METHOD2(TYPE, NAME, PARAM_1, PARAM_2)                  \
        case TYPE##_##NAME:                                                         \
            On##TYPE##_##NAME(PARAM_1 p1, PARAM_2 p2);                              \
            break;

#define IMPLEMENT_EVENT_RCVR_END()                                                  \
        default:                                                                    \
            break;                                                                  \
    }                                                                               \
    return HXR_OK;                                                                  \
}

#endif // _HXEVENTOBJ_H_
