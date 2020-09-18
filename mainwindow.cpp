#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imgedit.h"
#include "brightdialog.h"
#include <QDebug>

const QString g_imageFilter = "All Image Files (*.bmp *.jpg *.jpeg *.png *.tiff *.tif) ;; Bitmap (*.bmp) ;; JPEG (*.jpg *.jpeg) ;; Potable Image (*.png) ;; TIFF (*.tiff *.tif) ";
const QString g_imageSave = "Bitmap (*.bmp) ;; JPEG (*.jpg *.jpeg) ;; Potable Image (*.png) ;; TIFF (*.tiff *.tif) ";
QString g_path;
ImgEdit ie;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect( ui->projectsTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(on_close_tab(int)));
    //connect(ui->actionUndo,SIGNAL())


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Exit", "Are you sure? Any changes made may not have been saved", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QApplication::quit();
    }
}

void MainWindow::on_actionOpen_Image_triggered()
{
    if(g_path.isEmpty()){
        g_path = QDir::homePath();
    }
    else{//Ask user if they would like to save before opening new file
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Open Image", "Any changes made may not be saved. Would you like to save?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
            MainWindow::on_actionSave_As_triggered();//maybe chance to save
        }
    }
    //file directory
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image",g_path, g_imageFilter);
    if(!fileName.isEmpty()){
        QPixmap img(fileName);//display images
        string file =  fileName.toStdString();
        ie.openMat(file);
        //ie.oilPainting();
        img =cvMatToQPixmap(ie.getMat());
        //int w = ui->label_img->width();
        //int h = ui->label_img->height();
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));
        g_path = fileName; 
    }
    else{g_path = QString();}//if no file is selected the path is set back to empty

}



void MainWindow::on_actionSave_As_triggered()
{
    if(!g_path.isEmpty()){


            QString fileName = QFileDialog::getSaveFileName(this, "Save Image",g_path, g_imageSave);
            if (!fileName.isEmpty())
            {
                const QPixmap* img = ui->label_img->pixmap();
                QImage image( img -> toImage());
                image.save(fileName);
            }
    }
    else{
        QMessageBox::warning(this,"Warning", "You dont have a file to save");
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (!g_path.isEmpty()){

        QMessageBox::StandardButton reply = QMessageBox::question(this,"Save", "Are you sure? You may be overwritting a file.", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
           const QPixmap* img = ui->label_img->pixmap();
           QImage image( img -> toImage() );
           image.save(g_path);
        }
    }

    else{
        QMessageBox::warning(this,"Warning", "You dont have a file to save");
    }

}

void MainWindow::on_actionUndo_triggered()
{
    if(!g_path.isEmpty()){
        ie.undo();
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));
    }
}

void MainWindow::on_actionRedo_triggered()
{
    if(!g_path.isEmpty()){
        ie.redo();
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));
    }
}

void MainWindow::on_actionBW_triggered()
{
    if(!g_path.isEmpty()){
        ie.greyScale();
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));
    }
}

/**fp (flip) =1, 0,-1.
    tp(transponse) true or false
    flip vert = 0,false
    horrizontal = 1,false
    90 = 1,true. 90ac=0,true. 180 =-1,0

    **/
void MainWindow::on_actionFlip_Vertical_triggered()
{
    if(!g_path.isEmpty()){
        ie.flipMat(0,false);
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_actionFlip_Horizontal_triggered()
{
    if(!g_path.isEmpty()){
        ie.flipMat(1,false);
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_actionRotate_90_triggered()
{
    if(!g_path.isEmpty()){
        ie.flipMat(1,true);
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_actionRotate_90_A_triggered()//anticlockwise
{
    if(!g_path.isEmpty()){
        ie.flipMat(0,true);
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_actionRotate_180_triggered()
{
    if(!g_path.isEmpty()){
        ie.flipMat(-1,false);
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_actionCartoonise_triggered()
{
    if(!g_path.isEmpty()){
        ie.cartoonise();
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_actionWhite_Balance_triggered()
{
    if(!g_path.isEmpty()){
        ie.whiteBal("white");
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_actionGrey_Balance_triggered()
{
    if(!g_path.isEmpty()){
        ie.whiteBal("grey");
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_actionOil_Painting_triggered()
{
    if(!g_path.isEmpty()){
        ie.oilPainting();
        QPixmap img = cvMatToQPixmap(ie.getMat());
        int x= img.width();
        int y =img.height();
        //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
        ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));

    }
}

void MainWindow::on_actionContrast_Brightness_triggered()
{
    if(!g_path.isEmpty()){
        brightDialog diag;
        diag.setModal(true);
        if(diag.exec() == QDialog::Accepted){
            int bright  = diag.getBright();
            double cont = diag.getCont();
            qDebug() << cont << "   "<<bright ;
            //double a = (double)result[0]/100.0 * 2.0 + 1.0;
            //int b  = result[1];
            //qDebug() << a << " " <<  b;
            ie.contBright(cont , bright);
            QPixmap img = cvMatToQPixmap(ie.getMat());
            int x= img.width();
            int y =img.height();
            //ui->label_img->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));
            ui->label_img->setPixmap(img.scaled(x,y,Qt::KeepAspectRatio));
        }

    }
}







