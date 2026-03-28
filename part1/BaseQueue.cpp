#include "BaseQueue.h"


#include <QStringList>

#include "CustomExceptions.h"

void BaseQueue::pushNumber(double value)
{
    m_items.emplace_back(value);
}

void BaseQueue::pushString(const QString &value)
{
    m_items.emplace_back(value);
}

QueueItem BaseQueue::pop()
{
    if (m_items.empty()) {
        throw EmptyQueueException();
    }

    QueueItem first = m_items.front();
    m_items.pop_front();
    return first;
}


QString BaseQueue::toString() const
{
    if (m_items.empty()) {
        return "Очередь пуста";
    }

    QStringList lines;
    for (int i = 0; i < static_cast<int>(m_items.size()); ++i) {
        const QueueItem &item = m_items[static_cast<size_t>(i)];

    }
    return lines.join('\n');
}

bool BaseQueue::isEmpty() const
{
    return m_items.empty();
}

int BaseQueue::size() const
{
    return static_cast<int>(m_items.size());
}

std::deque<QueueItem> &BaseQueue::items()
{
    return m_items;
}

const std::deque<QueueItem> &BaseQueue::items() const
{
    return m_items;
}
