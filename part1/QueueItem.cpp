#include "QueueItem.h"

QueueItem::QueueItem(double numberValue)
    : m_type(Type::Number), m_numberValue(numberValue)
{
}

QueueItem::QueueItem(const QString &stringValue)
    : m_type(Type::String), m_numberValue(0.0), m_stringValue(stringValue)
{
}

QueueItem::Type QueueItem::type() const
{
    return m_type;
}

double QueueItem::numberValue() const
{
    return m_numberValue;
}

const QString &QueueItem::stringValue() const
{
    return m_stringValue;
}

QString QueueItem::toString() const
{
    if (m_type == Type::Number) {
        return QString::number(m_numberValue, 'g', 12);
    }
    return m_stringValue;
}
