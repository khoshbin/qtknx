/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

#include "qknxnetipdisconnectresponse.h"

QT_BEGIN_NAMESPACE

QKnxNetIpDisconnectResponse::QKnxNetIpDisconnectResponse(quint8 channelId, QKnxNetIp::Error status)
    : QKnxNetIpFrame(QKnxNetIp::ServiceType::DisconnectResponse)
{
    QKnxNetIpPayload payload(channelId);
    payload.setByte(1, quint8(status));
    setPayload(payload);
}

quint8 QKnxNetIpDisconnectResponse::channelId() const
{
    return payloadRef().byte(0);
}

QKnxNetIp::Error QKnxNetIpDisconnectResponse::status() const
{
    return QKnxNetIp::Error(payloadRef().byte(1));
}

bool QKnxNetIpDisconnectResponse::isValid() const
{
    return QKnxNetIpFrame::isValid() && size() == 8
        && code() == QKnxNetIp::ServiceType::DisconnectResponse;
}

QT_END_NAMESPACE
