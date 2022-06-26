#ifndef STRUCTURE_WINDOW_H
#define STRUCTURE_WINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QtGui/QAction>
#include <QtGui>

#include "mainwindow.h"

class QSlider;
class DoubleSlider;



class Strucparam : public QWidget
{
    Q_OBJECT

public:
    Strucparam(MainWindow *mainWnd);
   // ~ParmWidget();
   
protected:
   // void keyPressEvent(QKeyEvent *event);

public slots:    
    void epsChanged(double value);

    void sigminChanged(double value);
   
    void sigmaxChanged(double value);
   
   
private:
	MainWindow *mainWnd;
    DoubleSlider *createEpsillonSlider();
    DoubleSlider *createSigmaSlider();


    DoubleSlider *epsSlider;
    DoubleSlider *sigminSlider;
    DoubleSlider *sigmaxSlider;

    QLabel* epsLabel;
    QLabel* sigminLabel;
    QLabel* sigmaxLabel;
};

#endif
