#include "BaseQueue.h"

#include <cstddef>
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

QueueItem BaseQueue::removeAt(int oneBasedIndex)
{
    if (m_items.empty()) {
        throw EmptyQueueException();
    }
    if (oneBasedIndex < 1 || oneBasedIndex > static_cast<int>(m_items.size())) {
        throw IndexOutOfRangeException(
            QString("индекс должен быть от 1 до %1").arg(m_items.size()));
    }

    const size_t zeroBasedIndex = static_cast<size_t>(oneBasedIndex - 1);
    QueueItem removed = m_items[zeroBasedIndex];
    m_items.erase(m_items.begin() + static_cast<std::ptrdiff_t>(zeroBasedIndex));
    return removed;
}

QString BaseQueue::toString() const
{
    if (m_items.empty()) {
        return "Очередь пуста";
    }

    QStringList lines;
    for (int i = 0; i < static_cast<int>(m_items.size()); ++i) {
        const QueueItem &item = m_items[static_cast<size_t>(i)];
        lines << QString("%1) %2").arg(i + 1).arg(item.toString());
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
