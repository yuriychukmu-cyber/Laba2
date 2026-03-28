#include "MainWindow.h"

#include <QComboBox>
#include <QFrame>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <stdexcept>

#include "../part1/CustomExceptions.h"
#include "../part2/TemplateQueueExceptions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setWindowTitle("Лабораторная работа №2 — Очереди, исключения, шаблоны");
    resize(900, 700);
}

void MainWindow::setupUi()
{
    auto *central = new QWidget(this);
    auto *rootLayout = new QVBoxLayout(central);
    rootLayout->setSpacing(12);

    setupPart1Block(rootLayout);
    setupPart2Block(rootLayout);

    setCentralWidget(central);
}

void MainWindow::setupPart1Block(QVBoxLayout *rootLayout)
{
    auto *title = new QLabel("Часть 1: Очередь с числами и строками", this);
    title->setStyleSheet("font-weight: bold; font-size: 15px;");
    rootLayout->addWidget(title);

    auto *controlsLayout = new QHBoxLayout();
    m_part1Input = new QLineEdit(this);
    m_part1Input->setPlaceholderText("Введите значение");

    m_part1Type = new QComboBox(this);
    m_part1Type->addItems({"Число", "Строка"});

    auto *addButton = new QPushButton("Добавить", this);
    m_part1RemoveIndex = new QLineEdit(this);
    m_part1RemoveIndex->setPlaceholderText("Индекс (с 1)");
    m_part1RemoveIndex->setValidator(new QIntValidator(1, 1000000, m_part1RemoveIndex));

    auto *popButton = new QPushButton("Удалить по индексу", this);
    auto *showButton = new QPushButton("Показать очередь", this);
    auto *sortButton = new QPushButton("Сортировать числа", this);

    controlsLayout->addWidget(new QLabel("Значение:", this));
    controlsLayout->addWidget(m_part1Input);
    controlsLayout->addWidget(new QLabel("Тип:", this));
    controlsLayout->addWidget(m_part1Type);
    controlsLayout->addWidget(addButton);
    controlsLayout->addWidget(new QLabel("Удалить индекс:", this));
    controlsLayout->addWidget(m_part1RemoveIndex);
    controlsLayout->addWidget(popButton);
    controlsLayout->addWidget(showButton);
    controlsLayout->addWidget(sortButton);

    m_part1Output = new QTextEdit(this);
    m_part1Output->setReadOnly(true);
    m_part1Status = new QLabel("Готово к работе", this);

    rootLayout->addLayout(controlsLayout);
    rootLayout->addWidget(m_part1Output);
    rootLayout->addWidget(m_part1Status);

    auto *separator = new QFrame(this);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    rootLayout->addWidget(separator);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addPart1Item);
    connect(popButton, &QPushButton::clicked, this, &MainWindow::removePart1ItemByIndex);
    connect(showButton, &QPushButton::clicked, this, &MainWindow::showPart1Queue);
    connect(sortButton, &QPushButton::clicked, this, &MainWindow::sortPart1Numbers);

    m_part1Output->clear();
}

void MainWindow::setupPart2Block(QVBoxLayout *rootLayout)
{
    auto *title = new QLabel("Часть 2: Шаблонная очередь", this);
    title->setStyleSheet("font-weight: bold; font-size: 15px;");
    rootLayout->addWidget(title);

    auto *controlsLayout = new QHBoxLayout();
    m_part2Input = new QLineEdit(this);
    m_part2Input->setPlaceholderText("Введите значение");

    m_part2Type = new QComboBox(this);
    m_part2Type->addItems({"int", "QString"});

    auto *addButton = new QPushButton("Добавить", this);
    m_part2RemoveIndex = new QLineEdit(this);
    m_part2RemoveIndex->setPlaceholderText("Индекс (с 1)");
    m_part2RemoveIndex->setValidator(new QIntValidator(1, 1000000, m_part2RemoveIndex));

    auto *popButton = new QPushButton("Удалить по индексу", this);
    auto *showButton = new QPushButton("Показать очередь", this);

    controlsLayout->addWidget(new QLabel("Значение:", this));
    controlsLayout->addWidget(m_part2Input);
    controlsLayout->addWidget(new QLabel("Тип очереди:", this));
    controlsLayout->addWidget(m_part2Type);
    controlsLayout->addWidget(addButton);
    controlsLayout->addWidget(new QLabel("Удалить индекс:", this));
    controlsLayout->addWidget(m_part2RemoveIndex);
    controlsLayout->addWidget(popButton);
    controlsLayout->addWidget(showButton);

    m_part2Output = new QTextEdit(this);
    m_part2Output->setReadOnly(true);
    m_part2Status = new QLabel("Готово к работе", this);

    rootLayout->addLayout(controlsLayout);
    rootLayout->addWidget(m_part2Output);
    rootLayout->addWidget(m_part2Status);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addPart2Item);
    connect(popButton, &QPushButton::clicked, this, &MainWindow::removePart2ItemByIndex);
    connect(showButton, &QPushButton::clicked, this, &MainWindow::showPart2Queue);
    m_part2Output->clear();
}

void MainWindow::addPart1Item()
{
    try {
        const QString rawText = m_part1Input->text().trimmed();
        if (rawText.isEmpty()) {
            throw InvalidInputException("поле ввода не должно быть пустым");
        }

        if (m_part1Type->currentText() == "Число") {
            bool ok = false;
            const double value = rawText.toDouble(&ok);
            if (!ok) {
                throw InvalidInputException("невозможно преобразовать значение в число");
            }
            m_part1Queue.pushNumber(value);
            setPart1Status("Число добавлено. Текущее отображение не изменено, нажмите «Показать очередь».", false);
        } else {
            m_part1Queue.pushString(rawText);
            setPart1Status("Строка добавлена. Текущее отображение не изменено, нажмите «Показать очередь».", false);
        }

        m_part1Input->clear();
    } catch (const QueueException &ex) {
        setPart1Status(ex.what(), true);
    }
}

void MainWindow::removePart1ItemByIndex()
{
    try {
        const int oneBasedIndex = readOneBasedIndex(m_part1RemoveIndex);
        const QueueItem removed = m_part1Queue.removeAt(oneBasedIndex);
        setPart1Status(
            QString("Удалён элемент с индексом %1: %2. Отображение не обновлено, нажмите «Показать очередь».")
                .arg(oneBasedIndex)
                .arg(removed.toString()),
            false);
    } catch (const QueueException &ex) {
        setPart1Status(ex.what(), true);
    }
}

void MainWindow::showPart1Queue()
{
    showPart1CurrentState();
    setPart1Status("Содержимое очереди обновлено", false);
}

void MainWindow::sortPart1Numbers()
{
    m_part1Queue.sortNumbersOnly();
    setPart1Status("Числа отсортированы. Отображение не обновлено, нажмите «Показать очередь».", false);
}

void MainWindow::addPart2Item()
{
    try {
        const QString rawText = m_part2Input->text().trimmed();
        if (rawText.isEmpty()) {
            throw InvalidInputException("поле ввода не должно быть пустым");
        }

        if (m_part2Type->currentText() == "int") {
            bool ok = false;
            const int value = rawText.toInt(&ok);
            if (!ok) {
                throw InvalidInputException("для очереди int нужно целое число");
            }
            m_intQueue.push(value);
            m_part2Status->setText("Элемент добавлен в TemplateQueue<int>. Отображение не обновлено, нажмите «Показать очередь».");
        } else {
            m_stringQueue.push(rawText);
            m_part2Status->setText("Элемент добавлен в TemplateQueue<QString>. Отображение не обновлено, нажмите «Показать очередь».");
        }

        m_part2Status->setStyleSheet("color: #1b5e20;");
        m_part2Input->clear();
    } catch (const InvalidInputException &ex) {
        m_part2Status->setText(ex.what());
        m_part2Status->setStyleSheet("color: #b71c1c;");
    }
}

void MainWindow::removePart2ItemByIndex()
{
    try {
        const int oneBasedIndex = readOneBasedIndex(m_part2RemoveIndex);
        if (m_part2Type->currentText() == "int") {
            const int removed = m_intQueue.removeAt(oneBasedIndex);
            m_part2Status->setText(
                QString("Удалён из TemplateQueue<int> индекс %1: %2. Отображение не обновлено, нажмите «Показать очередь».")
                    .arg(oneBasedIndex)
                    .arg(removed));
        } else {
            const QString removed = m_stringQueue.removeAt(oneBasedIndex);
            m_part2Status->setText(
                QString("Удалён из TemplateQueue<QString> индекс %1: %2. Отображение не обновлено, нажмите «Показать очередь».")
                    .arg(oneBasedIndex)
                    .arg(removed));
        }
        m_part2Status->setStyleSheet("color: #1b5e20;");
    } catch (const std::runtime_error &ex) {
        m_part2Status->setText(ex.what());
        m_part2Status->setStyleSheet("color: #b71c1c;");
    }
}

void MainWindow::showPart2Queue()
{
    showPart2CurrentState();
    m_part2Status->setText("Содержимое шаблонной очереди обновлено");
    m_part2Status->setStyleSheet("color: #1b5e20;");
}

void MainWindow::setPart1Status(const QString &message, bool isError)
{
    m_part1Status->setText(message);
    m_part1Status->setStyleSheet(isError ? "color: #b71c1c;" : "color: #1b5e20;");
}

void MainWindow::showPart1CurrentState()
{
    m_part1Output->setPlainText(m_part1Queue.toString());
}

void MainWindow::showPart2CurrentState()
{
    if (m_part2Type->currentText() == "int") {
        m_part2Output->setPlainText(m_intQueue.toString());
    } else {
        m_part2Output->setPlainText(m_stringQueue.toString());
    }
}

int MainWindow::readOneBasedIndex(QLineEdit *indexEdit) const
{
    const QString rawText = indexEdit->text().trimmed();
    if (rawText.isEmpty()) {
        throw InvalidInputException("укажите индекс для удаления");
    }

    bool ok = false;
    const int index = rawText.toInt(&ok);
    if (!ok || index < 1) {
        throw InvalidInputException("индекс должен быть целым числом от 1");
    }
    return index;
}
