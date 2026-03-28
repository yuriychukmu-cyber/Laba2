#pragma once

#include <deque>
#include <sstream>
#include <type_traits>

#include <QString>
#include <QStringList>

#include "TemplateQueueExceptions.h"

template<typename T>
class TemplateQueue
{
public:
    void push(const T &value)
    {
        m_items.push_back(value);
    }

    T pop()
    {
        if (m_items.empty()) {
            throw TemplateQueueEmptyException();
        }
        T first = m_items.front();
        m_items.pop_front();
        return first;
    }

    const T &front() const
    {
        if (m_items.empty()) {
            throw TemplateQueueEmptyException();
        }
        return m_items.front();
    }

    bool isEmpty() const
    {
        return m_items.empty();
    }

    int size() const
    {
        return static_cast<int>(m_items.size());
    }

    QString toString() const
    {
        if (m_items.empty()) {
            return "Очередь пуста";
        }

        QStringList lines;
        int index = 1;
        for (const T &item : m_items) {
            lines << QString("%1) %2").arg(index++).arg(valueToQString(item));
        }
        return lines.join('\n');
    }

private:
    QString valueToQString(const T &value) const
    {
        if constexpr (std::is_same_v<T, QString>) {
            return value;
        } else {
            std::ostringstream stream;
            stream << value;
            return QString::fromStdString(stream.str());
        }
    }

    std::deque<T> m_items;
};
