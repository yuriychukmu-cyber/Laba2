#pragma once

#include <stdexcept>

class TemplateQueueEmptyException : public std::runtime_error
{
public:
    TemplateQueueEmptyException()
        : std::runtime_error("Шаблонная очередь пуста. Операция невозможна.")
    {
    }
};

class TemplateQueueIndexOutOfRangeException : public std::runtime_error
{
public:
    explicit TemplateQueueIndexOutOfRangeException(const std::string &message)
        : std::runtime_error(message)
    {
    }
};
