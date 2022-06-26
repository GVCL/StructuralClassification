/****************************************************************************
**
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QAction>
#include "Classification/Processing.h"

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
class Processing;
class ParmWidget;
class Strucparam;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

 Processing *m_handReduction;

// void viewFeatures(vector<TreeNode *> featurAdd);
 void GLupdate();
 void setFeatureMode(int pointMode, int displayMode);
 void GLClear();
 void openNodeFeature();

 void getlabel();

public slots:
    void setRmin(double rmin);
    void setRmax(double rmax);
    void setEps(double eps);
    void setSigmaMin(double sigmin);
    void setSigmaMax(double sigmax);
    void setDisplayMode(int displayMode);
    void setPointMode(int pointMode);
 
signals:
    void displaymodeChanged(int displymode);
    void pointmodeChanged(int pointmode);



private slots:
    void setFilePath();
    void performReduction();
    void about();
    void setFeatDispMode(int);
    void setMeatFeatDispMode(int);

    
protected:
    void keyPressEvent(QKeyEvent *event);
private:

    void initToolBarRight();
    void initVisActions();
    // void createStatusBar();
    void createDockWindows();

    QListWidget *customerList;
    QListWidget *paragraphsList;
    QAction *action_Separator;

    ParmWidget *m_handleParWindow;
    Strucparam *m_handlestrucwind;
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


    QAction *action_ptRedn;


    float rmin, rmax, eps, sigmin, sigmax;
    int displaymode, pointmode;
    std::string filePath;


    QComboBox *ftdisp2;
    
};

#endif
