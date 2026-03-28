#pragma once

#include <QString>

class QueueItem
{
public:
    enum class Type
    {
        Number,
        String
    };

    QueueItem(double numberValue);
    QueueItem(const QString &stringValue);

    Type type() const;
    double numberValue() const;
    const QString &stringValue() const;
    QString toString() const;

private:
    Type m_type;
    double m_numberValue;
    QString m_stringValue;
};
