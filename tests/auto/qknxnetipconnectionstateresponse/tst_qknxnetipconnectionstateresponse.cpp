/******************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtKnx module.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#include <QtCore/qdebug.h>
#include <QtTest/qtest.h>
#include <QtKnx/qknxnetipconnectionstateresponse.h>

static QString s_msg;
static void myMessageHandler(QtMsgType, const QMessageLogContext &, const QString &msg)
{
    s_msg = msg;
}

class tst_QKnxNetIpConnectionStateResponse: public QObject
{
    Q_OBJECT

private slots:
    void testDefaultConstructor();
    void testConstructor();
    void testDebugStream();
    void testDataStream();
};

void tst_QKnxNetIpConnectionStateResponse::testDefaultConstructor()
{
    QKnxNetIpConnectionStateResponse connectionStateResponse;
    QCOMPARE(connectionStateResponse.isValid(), false);
    QCOMPARE(connectionStateResponse.channelId(), quint8(0));
    QCOMPARE(connectionStateResponse.status(), QKnxNetIp::Error::None);
}

void tst_QKnxNetIpConnectionStateResponse::testConstructor()
{
    quint8 channelId = 200;
    QKnxNetIpConnectionStateResponse connectionStateResponse(channelId,
        QKnxNetIp::Error::ConnectionId);
    QCOMPARE(connectionStateResponse.isValid(), true);
    QCOMPARE(connectionStateResponse.size(), quint16(8));
    QCOMPARE(connectionStateResponse.bytes<QByteArray>(),
        QByteArray::fromHex("061002080008c821"));
    QCOMPARE(connectionStateResponse.payload().size(), quint16(2));
    QCOMPARE(connectionStateResponse.payload().bytes<QByteArray>(),
        QByteArray::fromHex("c821"));
    QCOMPARE(connectionStateResponse.toString(), QString::fromLatin1("Header size { 0x06 }, "
            "Version { 0x10 }, Code { 0x208 }, Total size { 0x08 }, "
            "Bytes { 0xc8, 0x21 }"));
    QCOMPARE(connectionStateResponse.channelId(), quint8(200));
    QCOMPARE(connectionStateResponse.status(), QKnxNetIp::Error::ConnectionId);
}

void tst_QKnxNetIpConnectionStateResponse::testDebugStream()
{
    struct DebugHandler
    {
        explicit DebugHandler(QtMessageHandler newMessageHandler)
            : oldMessageHandler(qInstallMessageHandler(newMessageHandler)) {}
        ~DebugHandler() {
            qInstallMessageHandler(oldMessageHandler);
        }
        QtMessageHandler oldMessageHandler;
    } _(myMessageHandler);

    qDebug() << QKnxNetIpConnectionStateResponse();
    QCOMPARE(s_msg, QString::fromLatin1("0x1nv4l1d"));

    qDebug() << QKnxNetIpConnectionStateResponse(quint8(200), QKnxNetIp::Error::ConnectionId);
    QCOMPARE(s_msg, QString::fromLatin1("0x061002080008c821"));
}

void tst_QKnxNetIpConnectionStateResponse::testDataStream()
{
    QByteArray byteArray;
    QDataStream out(&byteArray, QIODevice::WriteOnly);
    out << QKnxNetIpConnectionStateResponse(quint8(200), QKnxNetIp::Error::ConnectionId);
    QCOMPARE(byteArray, QByteArray::fromHex("061002080008c821"));
}

QTEST_APPLESS_MAIN(tst_QKnxNetIpConnectionStateResponse)

#include "tst_qknxnetipconnectionstateresponse.moc"
