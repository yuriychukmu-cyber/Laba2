#include "CustomExceptions.h"

QueueException::QueueException(const QString &message)
    : std::runtime_error(message.toStdString())
{
}

EmptyQueueException::EmptyQueueException()
    : QueueException("Очередь пуста. Невозможно удалить элемент.")
{
}

InvalidInputException::InvalidInputException(const QString &details)
    : QueueException(QString("Некорректный ввод: %1").arg(details))
{
}

IndexOutOfRangeException::IndexOutOfRangeException(const QString &details)
    : QueueException(QString("Неверный индекс: %1").arg(details))
{
}
