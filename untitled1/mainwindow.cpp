#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <stdio.h>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QErrorMessage>
//#include <qhbox.h>
#include "Running.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

//MainWindow::MainWindow(QWidget *parent, const char *name)
//    : QWidget(parent, name)
//{
//  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//  newPol = true;
//  MainWindow::setMouseTracking(true);
//  mainImage.create(300, 300, 32);//QImage::Format_RGB444);
//  mainImage.fill(qRgb(255, 255, 255));
//  QPixmap pixmap(100,100);
//  pixmap.fill(QColor("transparent"));
//}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //newPol = true;
//    MainWindow::setMouseTracking(true);
//    mainImage.create(300, 300, 32);//QImage::Format_RGB444);
//    mainImage.fill(qRgb(255, 255, 255));
    curWidget = new PaintFig(this);
    curWidget->setVisible(true);
//    ui.centralWidget->setLayout(ui.horizontalLayout);
//    set_gridWidget(*curWidget);
//    setCentralWidget(new frame);
//    ui->widget->set;
//    QHBox *hbox = new QHBox(0);
//    hbox->setMargin(6);
//    hbox->setSpacing(6);
//            addWidget(curWidget);
    //connect(ui->skeletImageButton, SIGNAL(clicked()), this, SLOT(SkeletButtonClicked()));
    //connect(ui->pivotsButton, SIGNAL(clicked()), this, SLOT(PivotsButtonClicked()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(OkButtonClicked()));
    connect(ui->moveButton, SIGNAL(clicked()), this, SLOT(MovingButtonClicked()));
    connect(ui->saveImageButton, SIGNAL(clicked()), this, SLOT(saveImageButtonClicked()));
    connect(ui->openImageButton, SIGNAL(clicked()), this, SLOT(openImageButtonClicked()));
    connect(ui->savePolyButton, SIGNAL(clicked()), this, SLOT(errorMessage()));//curWidget, SLOT(savePolygons()));
}

void MainWindow::errorMessage()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),
                           "Now it's unavailable", 0, this);
    msgBox.exec();
}

MainWindow::~MainWindow()
{
//    delete mainImage;
//    polygons.clear();
//    delete Widget;
    delete ui;
}

//void MainWindow::createActions()
//{
//    newAct = new QAction(tr("&Open"), tr("Ctrl+N"), this);
//    newAct->setIconSet(QPixmap::fromMimeSource("new.png"));
//    newAct->setStatusTip(tr("Open file"));
//    connect(newAct, SIGNAL(activated()), this, SLOT(openFile()));

//    showGridAct = new QAction(tr("&Show Grid"), 0, this);
//    showGridAct->setToggleAction(true);
//    showGridAct->setOn(spreadsheet->showGrid());
//    showGridAct->setStatusTip(tr("Show or hide the spreadsheet s " "grid"));
//    connect(showGridAct, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));
//}

//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//  pressed = false;
//  if (event->button() == Qt::LeftButton){
//    setVertex(event->pos(), true);
////    paintTrace(event->pos(), 3);
//    this->update();
//  }
//  else if (event->button() == Qt::RightButton){
//    setVertex(event->pos(), false);
////    paintTrace(event->pos(), 2);
//    this->update();
//  }
//}

//void MainWindow :: mouseDoubleClickEvent(QMouseEvent *)
//{
//    pressed = true;
//    newPol = true;
//}

//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    if (!newPol)
//        xPr = event->pos().x();
//        yPr = event->pos().y();
////        paintTrace(event->pos(), 3);
//        this->update();
////  if (event->state() & LeftButton)
////    setImagePixel(event->pos(), true);
////  else if (event->state() & RightButton)
////    setImagePixel(event->pos(), false);
//}

//void MainWindow::keyPressEvent (QKeyEvent * event){
//    if (event->isAutoRepeat())
//        return;
//    if (event->key() == Qt::Key_Escape)
//        QApplication::quit();
//    if (event->key() == Qt::Key_Space)//Key_Enter)
//        ;//Run();
//}


void MainWindow::OkButtonClicked(){
    QApplication::quit();
}

void MainWindow::MovingButtonClicked(){

    mainImage = curWidget->getImage();    
    // = curWidget->skeleton;
    curWidget->setVisible(false);
    //std::vector<TNode*> p = curWidget->getPivots(); //
    delete curWidget;
    curWidget = new MoveSkeletW(this, mainImage);
    //curWidget->pivots = p; //
    curWidget->setVisible(true);
}

void MainWindow::saveImageButtonClicked()
{
    QPixmap qpimage = QPixmap::grabWidget(curWidget);

    QFileDialog* fileDialog = new QFileDialog(this);

    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setNameFilter("PNG file (*.png)");
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    fileDialog->setDirectory("..\\SavedData\\");

    QStringList fileNames;

    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
    }

    if (fileNames.size() != 0) {
        QString filen = fileNames.at(0);

        if (!filen.endsWith(".png")) {
            filen += ".png";
        }
    qpimage.save(filen);
   }
}

void MainWindow::openImageButtonClicked()
{
    QFileDialog* fileDialog = new QFileDialog(this);

    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setNameFilter("Images (*.png *.jpg *.bmp)");
    QStringList fileNames;
    QString imagepath;
    //QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.h");
    if (fileDialog->exec()) {
            fileNames = fileDialog->selectedFiles();
        }

        if (fileNames.size() != 0) {

            imagepath = fileNames.at(0);
            string filepath = string(fileNames.at(0).toLocal8Bit().constData());
            string filename = "File name : ";
            int index = 0;

            for (ulong i = 0; i < filepath.size(); i++) {
                if (filepath[i] == '/') {
                    index = i + 1;
                }
            }

            for (ulong i = index; i < filepath.size(); i++) {
                filename.push_back(filepath[i]);
            }

        curWidget->setImage(new QImage(imagepath));
        }

       /*mainImage = curWidget->getImage();
        //SelectPivots* Widget = new SelectPivots(this, mainImage);
        disconnect(ui->savePolyButton, SIGNAL(clicked()), curWidget, SLOT(savePolygons()));


        TPolFigure *sk = curWidget->skeleton;
        curWidget->setVisible(false);
        delete curWidget;
        curWidget = new SelectPivots(this, mainImage, sk);
        curWidget->setVisible(true);
        connect(ui->savePolyButton, SIGNAL(clicked()), curWidget, SLOT(savePolygons()));


        curWidget = new PaintFig(this);
        curWidget->setVisible(true);*/


//    emit(newImageLoaded(imagepath));
   // curWidget->setImage(QImage(imagepath));
    //mainImage = new QImage(imagepath);
}

