#ifndef TREE_WINDOW_H
#define TREE_WINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QtGui/QAction>
#include <QtGui>

#include "mainwindow.h"

class QSlider;




class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    TreeWidget(MainWindow *mainWnd);
   
protected:
    void keyPressEvent(QKeyEvent *event);

private:
	MainWindow *mainWnd;
	
    QSlider *createSlider();

    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
};

#endif
