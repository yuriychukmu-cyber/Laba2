#pragma once

#include <QString>
#include <stdexcept>

class QueueException : public std::runtime_error
{
public:
    explicit QueueException(const QString &message);
};

class EmptyQueueException : public QueueException
{
public:
    EmptyQueueException();
};

class InvalidInputException : public QueueException
{
public:
    explicit InvalidInputException(const QString &details);
};
