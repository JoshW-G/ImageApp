#ifndef IMGEDIT_H
#define IMGEDIT_H

#include <QObject>

#include <QDebug>
#include <QThread>
#include <QtDebug>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include<opencv2/photo.hpp>
#include<opencv2/xphoto.hpp>
#include <chrono>
using namespace std;
using namespace cv;
class ImgEdit : public QObject
{
    Q_OBJECT
public:
    explicit ImgEdit(QObject *parent = nullptr);
    //update Functions MUST clear imRedo  and call pushUndo with currect Mat
    cv::Mat getMat() const;  //ONLY use this to get Mats
    void openMat(string &filename);
    void redo();//call when triggered in ui
    void undo();//call when triggered in ui

    void greyScale();
    void flipMat(int fp, bool tp);/**fp (flip) =1, 0,-1.
    tp(transponse) true or false
    flip vert = 0,false
    horrizontal = 1,false
    90 = 1,true. 90ac=0,true. 180 =-1,0

    **/
    void cartoonise();
    void oilPainting();

    void whiteBal(string mode);
    void contBright(double contrast, int brightness);
signals:

private:

    cv::Mat mImg;//image to work with
    vector<cv::Mat> imUndo;//stores previous mats
    vector<cv::Mat> imRedo;//stores mats that are undone, should be cleared when an update is called
    void setCurrMat(cv::Mat im); //all functions should use this to set current working Mat (imMat)
    bool ifGrey(Mat *im);
    void toColour(Mat &src, Mat &dst);

    const int imMax = 100;//to add limit  to amount  of images to be saved
    bool compMat(const Mat & a, const Mat & b);

    void pushUndo(Mat inMat);//call  everytime an update to mMat is  complete so it is stored,
    void popUndo();//call  when undo is called to get last image, the current image should be added to another vector (pushRedo)
    void pushRedo(Mat inMat);//call when popUndo is to add undone images to redo
    void popRedo();//call when redo is called, call pushUndo to add it to to the undo stack
};

#endif // IMGEDIT_H

