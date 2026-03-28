#pragma once

#include <QMainWindow>

#include "../part1/SortableNumberQueue.h"
#include "../part2/TemplateQueue.h"

class QComboBox;
class QLineEdit;
class QTextEdit;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupUi();
    void setupPart1Block(class QVBoxLayout *rootLayout);
    void setupPart2Block(class QVBoxLayout *rootLayout);

    void addPart1Item();

    void showPart1Queue();
    void sortPart1Numbers();

    void addPart2Item();

    SortableNumberQueue m_part1Queue;
    TemplateQueue<int> m_intQueue;
    TemplateQueue<QString> m_stringQueue;

    QLineEdit *m_part1Input = nullptr;

    QComboBox *m_part1Type = nullptr;
    QTextEdit *m_part1Output = nullptr;
    QLabel *m_part1Status = nullptr;

    QLineEdit *m_part2Input = nullptr;

    QComboBox *m_part2Type = nullptr;
    QTextEdit *m_part2Output = nullptr;
    QLabel *m_part2Status = nullptr;
};
