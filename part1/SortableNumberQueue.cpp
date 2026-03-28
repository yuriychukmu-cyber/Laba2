#include "SortableNumberQueue.h"

#include <algorithm>
#include <vector>

void SortableNumberQueue::sortNumbersOnly()
{
    std::vector<double> numbers;
    numbers.reserve(items().size());

    for (const QueueItem &item : items()) {
        if (item.type() == QueueItem::Type::Number) {
            numbers.push_back(item.numberValue());
        }
    }

    std::sort(numbers.begin(), numbers.end());

    size_t numberIndex = 0;
    for (QueueItem &item : items()) {
        if (item.type() == QueueItem::Type::Number) {
            item = QueueItem(numbers[numberIndex]);
            ++numberIndex;
        }
    }
}
