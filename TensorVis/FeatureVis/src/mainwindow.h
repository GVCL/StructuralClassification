/****************************************************************************
**
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QAction>
#include "vis.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <QComboBox>

using namespace std;

class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QSlider;
class QListWidget;
class GLWidget;
class vis;
class ParmWidget;
class Strucparam;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

 vis *_objprocess ;

// void viewFeatures(vector<TreeNode *> featurAdd);
 void GLupdate();
 void setFeatureMode(int pointMode, int displayMode);
 void GLClear();

public slots:

 
signals:

private slots:
    void setFilePath();
    void about();

    
protected:
    void keyPressEvent(QKeyEvent *event);
private:

    void initToolBarRight();
    void initVisActions();
    // void createStatusBar();

    //TreeWidget *m_handleTreeVis;

    QAction *action_Open;
        
    void createActions();
    void createMenus();
 
    QSize getSize();

    //QWidget *centralWidget;
    QScrollArea *glWidgetArea;

    GLWidget *glWidget;


    QMenu *fileMenu;
    QMenu *helpMenu;

    QToolBar *toolBarTop;
    QToolBar *toolBarRight;
    
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;


    std::string filePath;

    
};

#endif
