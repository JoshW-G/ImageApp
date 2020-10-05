#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
//#include <QDialog>
#include <opencv2/core.hpp>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class ImgEdit;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_Image_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();



    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionBW_triggered();

    void on_actionFlip_Vertical_triggered();

    void on_actionFlip_Horizontal_triggered();

    void on_actionRotate_90_triggered();

    void on_actionRotate_90_A_triggered();

    void on_actionRotate_180_triggered();

    void on_actionCartoonise_triggered();

    void on_actionWhite_Balance_triggered();

    void on_actionGrey_Balance_triggered();

    void on_actionOil_Painting_triggered();

    void on_actionContrast_Brightness_triggered();

    void on_actionInvert_Colours_triggered();

    void on_actionHue_Saturation_triggered();

private:
    Ui::MainWindow *ui;
    ImgEdit *imEdit;

    QImage cvMatToQImage( const cv::Mat &inMat ){
        {
            switch ( inMat.type() )
            {
            // 8-bit, 4 channel
            case CV_8UC4:
            {
                QImage image( inMat.data,
                              inMat.cols, inMat.rows,
                              static_cast<int>(inMat.step),
                              QImage::Format_ARGB32 );
                return image;
            }
                // 8-bit, 3 channel
            case CV_8UC3:
            {
                QImage image( inMat.data,
                              inMat.cols, inMat.rows,
                              static_cast<int>(inMat.step),
                              QImage::Format_RGB888 );
                return image.rgbSwapped();
            }
                // 8-bit, 1 channel
            case CV_8UC1:
            {
        #if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
                QImage image( inMat.data,
                              inMat.cols, inMat.rows,
                              static_cast<int>(inMat.step),
                              QImage::Format_Grayscale8 );
        #else
                static QVector<QRgb>  sColorTable;
                // only create our color table the first time
                if ( sColorTable.isEmpty() )
                {
                    sColorTable.resize( 256 );
                    for ( int i = 0; i < 256; ++i )
                    {
                        sColorTable[i] = qRgb( i, i, i );
                    }
                }
                QImage image( inMat.data,
                              inMat.cols, inMat.rows,
                              static_cast<int>(inMat.step),
                              QImage::Format_Indexed8 );
                image.setColorTable( sColorTable );
        #endif
                return image;
            }
            default:
                qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
                break;
            }
            return QImage();
        }
    }
    QPixmap cvMatToQPixmap( const cv::Mat &inMat )
    {
        return QPixmap::fromImage( cvMatToQImage( inMat ) );
    }
};
#endif // MAINWINDOW_H
