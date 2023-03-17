#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include "widgets/MediaDropWidget.hpp"

namespace Ui {
class TimeLine;
}

class TimeLine : public MediaDropWidget
{
    Q_OBJECT

public:
    explicit TimeLine(QWidget *parent = nullptr);
    ~TimeLine();

private:
    Ui::TimeLine *ui;
};

#endif // TIMELINE_H
