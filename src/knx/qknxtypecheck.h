/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
****************************************************************************/

#pragma once

QT_BEGIN_NAMESPACE

class QKnxTypeCheck
{
public:
    template <typename T> static void FailIfNotQByteArrayQVectorUint8Type()
    {
        static_assert(IsType<T, QByteArray, QVector<quint8>>::value,
            "Only QByteArray or QVector<quint8> are supported as type.");
    }

private:
    template <typename T, typename ... Ts> struct IsType
    {
        enum { value = false };
    };

    template <typename T, typename T1, typename ... Ts> struct IsType<T, T1, Ts...>
    {
        enum { value = std::is_same<T, T1>::value || IsType<T, Ts...>::value };
    };
};

QT_END_NAMESPACE
