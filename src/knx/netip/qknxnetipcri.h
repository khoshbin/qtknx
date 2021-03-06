/******************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtKnx module.
**
** $QT_BEGIN_LICENSE:GPL$
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
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
******************************************************************************/

#ifndef QKNXNETIPCRI_H
#define QKNXNETIPCRI_H

#include <QtCore/qbytearray.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qdebug.h>
#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtKnx/qknxglobal.h>
#include <QtKnx/qknxnetipstruct.h>
#include <QtKnx/qknxtraits.h>
#include <QtKnx/qknxnetipservicefamiliesdib.h>

QT_BEGIN_NAMESPACE

class Q_KNX_EXPORT QKnxNetIpCri : public QKnxNetIpConnectionTypeStruct
{
public:
    QKnxNetIpCri() = default;
    ~QKnxNetIpCri() override = default;

    explicit QKnxNetIpCri(QKnxNetIp::TunnelingLayer layer);
    explicit QKnxNetIpCri(QKnxNetIp::ConnectionType connectionType);

    template <typename T> static QKnxNetIpCri fromBytes(const T &bytes, quint16 index)
    {
        auto code = QKnxNetIpStructHeader<QKnxNetIp::ConnectionType>::fromBytes(bytes, index).code();
        if (!QKnxNetIp::isStructType(code))
            return {};
        return QKnxNetIpStructHelper::fromBytes(bytes, index, code);
    }

    QKnxNetIp::ConnectionType connectionType() const;
    void setConnectionType(QKnxNetIp::ConnectionType connectionType);

    bool isValid() const override;

    QKnxNetIp::TunnelingLayer tunnelingLayer() const;
    bool setTunnelingLayer(QKnxNetIp::TunnelingLayer layer);

private:
    QKnxNetIpCri(const QKnxNetIpConnectionTypeStruct &other);
};

QT_END_NAMESPACE

#endif
