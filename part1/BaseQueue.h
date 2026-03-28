#pragma once

#include <deque>

#include "QueueItem.h"

class BaseQueue
{
public:
    virtual ~BaseQueue() = default;

    void pushNumber(double value);
    void pushString(const QString &value);
    QueueItem pop();
    QueueItem removeAt(int oneBasedIndex);

    QString toString() const;
    bool isEmpty() const;
    int size() const;

protected:
    std::deque<QueueItem> &items();
    const std::deque<QueueItem> &items() const;

private:
    std::deque<QueueItem> m_items;
};
