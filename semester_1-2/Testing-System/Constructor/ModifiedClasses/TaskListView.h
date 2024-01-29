#ifndef TASKLISTVIEW_H
#define TASKLISTVIEW_H

#include <QListWidget>
#include <QKeyEvent>
#include "ModifiedClasses/StatusBar.h"

class TaskListView
    : public QListWidget
{
    Q_OBJECT
private:
    int copiedRow;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override {

        if (event->modifiers() == Qt::ControlModifier &&
                event->key() == Qt::Key_C) {
            copiedRow = currentRow();

            emit taskCopied(copiedRow);
        }
        else if (event->modifiers() == Qt::ControlModifier &&
                 event->key() == Qt::Key_V) {
            int currentRow_ = currentRow();
            if (copiedRow != -1 && currentRow_ != -1) {
                emit taskPasted(copiedRow, currentRow_);

                if (currentRow_ < copiedRow)
                    copiedRow++;
            }
        }
    }

signals:
    void taskPasted(int numberOfPasted, int currentRow);
    void taskCopied(int numberOfCopied);
public:
    TaskListView(QWidget* parent = nullptr)
        : QListWidget(parent)
        , copiedRow(-1)
    {

    }

    void rowDeleted(int row) {
        if (copiedRow == row)
            copiedRow = -1;
    }

    void rowMoved(int from, int to) {
        if (copiedRow == from)
            copiedRow = to;
    }

};



#endif // TASKLISTVIEW_H
