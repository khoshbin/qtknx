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

#ifndef QKNXBYTESTOREREF_H
#define QKNXBYTESTOREREF_H

#include <QtCore/qbytearray.h>
#include <QtCore/qdatastream.h>
#include <QtCore/qdebug.h>
#include <QtCore/qstring.h>
#include <QtCore/qvector.h>
#include <QtKnx/qknxglobal.h>
#include <QtKnx/qknxtraits.h>

QT_BEGIN_NAMESPACE

class QKnxByteStore;
class Q_KNX_EXPORT QKnxByteStoreRef final
{
    friend class QKnxByteStore;

public:
    QKnxByteStoreRef() = default;
    ~QKnxByteStoreRef() = default;

    QKnxByteStoreRef(const QKnxByteStoreRef &) = default;
    QKnxByteStoreRef &operator=(const QKnxByteStoreRef &) = default;

    quint16 size() const;
    const quint8 *bytes() const;

    quint8 byte(quint16 index) const
    {
        if (index < size()) {
            const quint8 *tmp = bytes();
            return tmp[index];
        }
        return {};
    }

    template <typename T = QByteArray> auto bytes() const -> decltype(T())
    {
        return bytes<T>(0, size());
    }

    template <typename T = QByteArray> auto bytes(quint16 start, quint16 count) const -> decltype(T())
    {
        static_assert(is_type<T, QByteArray, QVector<quint8>, std::deque<quint8>,
            std::vector<quint8>>::value, "Type not supported.");

        if (size() < start + count)
            return {};

        T t(count, 0);
        std::copy_n(std::next(bytes(), start), count, std::begin(t));
        return t;
    }

    typedef const quint8 *const_iterator;
    const_iterator begin() const
    {
        const quint8 *tmp = bytes();
        return tmp;
    }

    const_iterator end() const
    {
        const quint8 *tmp = bytes();
        return std::next(tmp, size());
    }

    quint8 operator[](int i) const;

private:
    explicit QKnxByteStoreRef(QKnxByteStore *store);
    QKnxByteStoreRef(QKnxByteStore *store, quint16 index);

private:
    quint16 m_index = 0;
    QKnxByteStore *m_store = nullptr;
};

QT_END_NAMESPACE

#endif
