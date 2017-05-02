/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

#ifndef QKNXNETIPKNXADDRESSESDIB_H
#define QKNXNETIPKNXADDRESSESDIB_H

#include <QtCore/qbytearray.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qdebug.h>
#include <QtCore/qstring.h>
#include <QtCore/qvector.h>

#include <QtKnx/qknxaddress.h>
#include <QtKnx/qknxglobal.h>
#include <QtKnx/qknxnetipstruct.h>
#include <QtKnx/qknxtraits.h>

QT_BEGIN_NAMESPACE

class Q_KNX_EXPORT QKnxNetIpKnxAddressesDIB final : public QKnxNetIpDescriptionTypeStruct
{
public:
    QKnxNetIpKnxAddressesDIB() = default;
    ~QKnxNetIpKnxAddressesDIB() override = default;

    explicit QKnxNetIpKnxAddressesDIB(const QKnxAddress &address);
    explicit QKnxNetIpKnxAddressesDIB(const QVector<QKnxAddress> &addresses);

    template <typename T> static QKnxNetIpKnxAddressesDIB fromBytes(const T &bytes, quint16 index)
    {
        return QKnxNetIpStructHelper::fromBytes(bytes, index,
            QKnxNetIp::DescriptionType::KnxAddresses);
    }

    QKnxNetIp::DescriptionType descriptionType() const;
    template <typename T> auto individualAddresses() const -> decltype(T())
    {
        static_assert(is_type<T, QVector<QKnxAddress>, std::deque<QKnxAddress>,
            std::vector<QKnxAddress>>::value, "Type not supported.");

        const QKnxNetIpPayload &load = payload();
        T addresses;
        for (quint16 i = 0; i < load.size(); i += 2)
            addresses.push_back({ QKnxAddress::Type::Individual, load.bytes<QByteArray>(i, 2) });
        return addresses;

    }

    bool isValid() const override;

private:
    QKnxNetIpKnxAddressesDIB(const QKnxNetIpDescriptionTypeStruct &other);
};
Q_DECLARE_TYPEINFO(QKnxNetIpKnxAddressesDIB, Q_MOVABLE_TYPE);

QT_END_NAMESPACE

#endif
