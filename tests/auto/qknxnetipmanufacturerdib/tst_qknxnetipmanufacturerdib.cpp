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
#include <QtKnx/qknxnetipmanufacturerdib.h>
#include <QtTest/qtest.h>

static QString s_msg;
static void myMessageHandler(QtMsgType, const QMessageLogContext &, const QString &msg)
{
    s_msg = msg;
}

class tst_QKnxNetIpManufacturerDib : public QObject
{
    Q_OBJECT

private slots:
    void testDefaultConstructor();
    void testConstructorWithOneArguments();
    void testConstructorWithByteArrayDataArguments();
    void testConstructorWithVectorDataArguments();
    void testDebugStream();
    void testDataStream();
};

void tst_QKnxNetIpManufacturerDib::testDefaultConstructor()
{
    QKnxNetIpManufacturerDib manufacturerDib;
    QCOMPARE(manufacturerDib.isValid(), false);
    QCOMPARE(manufacturerDib.size(), quint16(0));
    QCOMPARE(manufacturerDib.bytes<QByteArray>(), QByteArray(""));
    QCOMPARE(manufacturerDib.payload().size(), quint16(0));
    QCOMPARE(manufacturerDib.payload().bytes<QByteArray>(), QByteArray(""));
    QCOMPARE(manufacturerDib.toString(), QString::fromLatin1("Total size { 0x00 }, Code { 0x00 }, "
        "Bytes {  }"));
    QCOMPARE(quint8(manufacturerDib.descriptionType()), quint8(0));
    QCOMPARE(manufacturerDib.manufacturerId(), quint16(0));
}

void tst_QKnxNetIpManufacturerDib::testConstructorWithOneArguments()
{
    QKnxNetIpManufacturerDib manufacturerDib(65535);
    QCOMPARE(manufacturerDib.isValid(), true);
    QCOMPARE(manufacturerDib.size(), quint16(4));
    QCOMPARE(manufacturerDib.bytes<QByteArray>(), QByteArray::fromHex("04FEFFFF"));
    QCOMPARE(manufacturerDib.payload().size(), quint16(2));
    QCOMPARE(manufacturerDib.payload().bytes<QByteArray>(), QByteArray::fromHex("FFFF"));
    QCOMPARE(manufacturerDib.toString(), QString::fromLatin1("Total size { 0x04 }, Code { 0xfe }, "
        "Bytes { 0xff, 0xff }"));
    QCOMPARE(manufacturerDib.descriptionType(), QKnxNetIp::DescriptionType::ManufactorData);
    QCOMPARE(manufacturerDib.manufacturerId(), quint16(65535));
}

void tst_QKnxNetIpManufacturerDib::testConstructorWithByteArrayDataArguments()
{
    const QByteArray data = QByteArray::fromHex("0102030405");
    QKnxNetIpManufacturerDib manufacturerDib(65535, data);
    QCOMPARE(manufacturerDib.isValid(), true);
    QCOMPARE(manufacturerDib.size(), quint16(9));
    QCOMPARE(manufacturerDib.bytes<QByteArray>(), QByteArray::fromHex("09FEFFFF0102030405"));
    QCOMPARE(manufacturerDib.payload().size(), quint16(7));
    QCOMPARE(manufacturerDib.payload().bytes<QByteArray>(), QByteArray::fromHex("FFFF0102030405"));
    QCOMPARE(manufacturerDib.toString(), QString::fromLatin1("Total size { 0x09 }, Code { 0xfe }, "
        "Bytes { 0xff, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05 }"));
    QCOMPARE(manufacturerDib.descriptionType(), QKnxNetIp::DescriptionType::ManufactorData);
    QCOMPARE(manufacturerDib.manufacturerId(), quint16(65535));
    QCOMPARE(manufacturerDib.manufacturerData<QByteArray>().size(), data.size());
    QCOMPARE(manufacturerDib.manufacturerData<QVector<quint8>>().size(), data.size());
    QCOMPARE(manufacturerDib.manufacturerData<QByteArray>(), data);
}

void tst_QKnxNetIpManufacturerDib::testConstructorWithVectorDataArguments()
{
    const QVector<quint8> data = { 1, 2, 3, 4, 5 };
    QKnxNetIpManufacturerDib manufacturerDib(65535, data);
    QCOMPARE(manufacturerDib.isValid(), true);
    QCOMPARE(manufacturerDib.size(), quint16(9));
    QCOMPARE(manufacturerDib.bytes<QByteArray>(), QByteArray::fromHex("09FEFFFF0102030405"));
    QCOMPARE(manufacturerDib.payload().size(), quint16(7));
    QCOMPARE(manufacturerDib.payload().bytes<QByteArray>(), QByteArray::fromHex("FFFF0102030405"));
    QCOMPARE(manufacturerDib.toString(), QString::fromLatin1("Total size { 0x09 }, Code { 0xfe }, "
        "Bytes { 0xff, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05 }"));
    QCOMPARE(manufacturerDib.descriptionType(), QKnxNetIp::DescriptionType::ManufactorData);
    QCOMPARE(manufacturerDib.manufacturerId(), quint16(65535));
    QCOMPARE(manufacturerDib.manufacturerData<QByteArray>().size(), data.size());
    QCOMPARE(manufacturerDib.manufacturerData< QVector<quint8> >().size(), data.size());
    QCOMPARE(manufacturerDib.manufacturerData< QVector<quint8> >(), data);
}

void tst_QKnxNetIpManufacturerDib::testDebugStream()
{
    struct DebugHandler
    {
        explicit DebugHandler(QtMessageHandler newMessageHandler)
            : oldMessageHandler(qInstallMessageHandler(newMessageHandler))
        {}
        ~DebugHandler()
        {
            qInstallMessageHandler(oldMessageHandler);
        }
        QtMessageHandler oldMessageHandler;
    } _(myMessageHandler);

    qDebug() << QKnxNetIpManufacturerDib();
    QCOMPARE(s_msg, QString::fromLatin1("0x1nv4l1d"));

    qDebug() << QKnxNetIpManufacturerDib(65535);
    QCOMPARE(s_msg, QString::fromLatin1("0x04feffff"));

    qDebug() << QKnxNetIpManufacturerDib(65535, QByteArray::fromHex("0102030405"));
    QCOMPARE(s_msg, QString::fromLatin1("0x09feffff0102030405"));

    qDebug() << QKnxNetIpManufacturerDib(65535, { { 1, 2, 3, 4, 5 } });
    QCOMPARE(s_msg, QString::fromLatin1("0x09feffff0102030405"));
}

void tst_QKnxNetIpManufacturerDib::testDataStream()
{
    {
        QByteArray byteArray;
        QDataStream out(&byteArray, QIODevice::WriteOnly);
        out << QKnxNetIpManufacturerDib(65535);
        QCOMPARE(byteArray, QByteArray::fromHex("04FEFFFF"));
    }

    {
        QByteArray byteArray;
        QDataStream out(&byteArray, QIODevice::WriteOnly);
        out << QKnxNetIpManufacturerDib(65535, QByteArray::fromHex("0102030405"));
        QCOMPARE(byteArray, QByteArray::fromHex("09FEFFFF0102030405"));
    }

    {
        QByteArray byteArray;
        QDataStream out(&byteArray, QIODevice::WriteOnly);
        out << QKnxNetIpManufacturerDib(65535, { { 1, 2, 3, 4, 5 } });
        QCOMPARE(byteArray, QByteArray::fromHex("09FEFFFF0102030405"));
    }
}

QTEST_APPLESS_MAIN(tst_QKnxNetIpManufacturerDib)

#include "tst_qknxnetipmanufacturerdib.moc"
