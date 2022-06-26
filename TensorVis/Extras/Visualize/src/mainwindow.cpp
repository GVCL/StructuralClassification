/****************************************************************************
**
**
****************************************************************************/

#include <QtGui>
#include <QtOpenGL>

#include "glwidget.h"
#include "mainwindow.h"
#include "ParameterWidget.h"
#include "TreeWidget.h"
#include "Strucparam.h"

/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
MainWindow::MainWindow() 
{

    _objprocess = new vis();
    glWidget = new GLWidget(0, this);

    this->resize(800, 800);
    setCentralWidget(glWidget);
    setWindowTitle(tr("Vis tool"));

    //initVisActions();
    createActions();
    createMenus();

    //Parameter initializatio
    filePath = "NULL";

}
/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
void MainWindow::setFilePath()
{
     QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
            QString(), tr("Okc Files (*.txt);;CSV Files (*.las);;All Files (*)"));
    // if users clicked the button "Cancel", fn will be null
    if (fn.isNull()) {
        return;
    }

    try
    {
         filePath =fn.toStdString();
        _objprocess->fileread(filePath);
        _objprocess->drawColorMap(0);
        glWidget->updateGL();
    } 
    catch (bad_alloc& ba) 
    {
        QMessageBox::critical(this,
                "Failure to request memory",
                "XmdvTool failed to request enough memory to visualize "
                "the current dataset and has to exit.  Please report "
                "this problem to xmdv@cs.wpi.edu with the description "
                "of your dataset and system configuration.  Thank you! "
                "--Xmdv Group");
        exit(1);
    }

}



/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Grabber"),
            tr("The <b>Grabber</b> example demonstrates two approaches for "
               "rendering OpenGL into a Qt pixmap."));
}
/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
void MainWindow::createActions()
{
     action_Open = new QAction(this);
   // action_Open->setObjectName(QString::fromUtf8("action_Open"));
    action_Open->setText(tr("Open"));
   // action_Open->setIcon(ICON_OPEN);
    action_Open->setShortcut(tr("Ctrl+F"));
    action_Open->setStatusTip(tr("Open file"));
    connect(action_Open, SIGNAL(triggered()), this, SLOT(setFilePath()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}
/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(action_Open);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}




/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
void MainWindow::initToolBarRight()
{

}


/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
       glWidget->keyPressEvent(e);
       // QWidget::keyPressEvent(e);
}
/*****************************************************************************************
Function Name		:	FeatureGraph::SelectSeedNode
Purpose	of Function	:	classify the 3D points into various classes- curve node, disc node
                                critical curve node and critical disc node
Calls			:
Input Params		:	T *curve, T *disc, T *spherical
Output Params		:	S *curveNode, S *discNode, S *critCurveNode, S *critDiscNode
Return			:
Remarks			:
*****************************************************************************************/
 void MainWindow::GLClear()
 {
    glWidget->winClear();
 }
