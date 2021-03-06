#include "imgedit.h"
#include<opencv2/xphoto.hpp>
ImgEdit::ImgEdit(QObject *parent) : QObject(parent)
{

}

cv::Mat ImgEdit::getMat() const{
    return mImg;
}
void ImgEdit::openMat(string &filename){
    mImg = cv::imread(filename, cv::IMREAD_UNCHANGED);
    imUndo.clear();//emptys images stored
    imRedo.clear();
}

void ImgEdit::greyScale(){
    imRedo.clear();
    pushUndo(getMat());
    Mat im = getMat();
    Mat imGrey;
    if(!(im.channels()==1)){
    cv::cvtColor(im, imGrey, CV_BGR2GRAY);
    setCurrMat(imGrey);
    }
}

void ImgEdit::flipMat(int fp, bool tp)
{
    imRedo.clear();
    pushUndo(getMat());
    Mat im = getMat();
    Mat imOut;
    if(tp){
        transpose(im,imOut);
    }
    flip(im,imOut,fp);
    setCurrMat(imOut);
}

void ImgEdit::cartoonise()
{
    imRedo.clear();
    pushUndo(getMat());
    Mat im = getMat();

    //Convert to gray scale
    Mat imGrey;
    if(!ifGrey(&im)){
        //toColour(im,imGrey);
        cvtColor(im, imGrey, COLOR_BGR2GRAY);
    }else{im.copyTo(imGrey);}


    //apply gaussian blur
    GaussianBlur(imGrey, imGrey, Size(3, 3), 0);

    //find edges
    Mat imEdge;
    Laplacian(imGrey, imEdge, -1, 5);
    convertScaleAbs(imEdge, imEdge);

    //invert the image
    imEdge = 255 - imEdge;

    //apply thresholding
    threshold(imEdge, imEdge, 150, 255, THRESH_BINARY);

    //blur images heavily using edgePreservingFilter
    Mat imEdgePreserving;
    edgePreservingFilter(im, imEdgePreserving, 2, 50, 0.4);

    // Create a output Matrix
    Mat output;
    output = Scalar::all(0);

    // Combine the cartoon and edges
    cv::bitwise_and(imEdgePreserving, imEdgePreserving, output, imEdge);
    if(ifGrey(&im)){
        Mat imOut;
        cv::cvtColor(output, imOut, CV_BGR2GRAY);//SOMETHING DOEST WORK RIGHT
        setCurrMat(imOut);
    }else{
    setCurrMat(output);}
}

void ImgEdit::oilPainting()
{
    imRedo.clear();
    pushUndo(getMat());
    Mat im = getMat();
    Mat imOut;
    if(ifGrey(&im)){
        toColour(im,imOut);
        xphoto::oilPainting(imOut, imOut, 10, 1, COLOR_BGR2Lab);
        setCurrMat(imOut);
        greyScale();
    }
    else{
        xphoto::oilPainting(im, imOut, 10, 1, COLOR_BGR2Lab);
        setCurrMat(imOut);
    }
}

void ImgEdit::invert()
{
    imRedo.clear();
    pushUndo(getMat());
    Mat im = getMat();
    Mat imOut;
    cv::bitwise_not(im, imOut);
    setCurrMat(imOut);
}


void ImgEdit::whiteBal(string mode)
{
    imRedo.clear();
    pushUndo(getMat());
    Mat im = getMat();
    Mat imOut;
    Ptr<xphoto::WhiteBalancer> wb;
    if (mode == "white")
        wb = xphoto::createSimpleWB();
    else if (mode == "grey")
        wb = xphoto::createGrayworldWB();
    if(ifGrey(&im)){
        toColour(im,imOut);
        wb->balanceWhite(imOut, imOut);
        setCurrMat(imOut);
        greyScale();
    }else{
    wb->balanceWhite(im, imOut);
    setCurrMat(imOut);}
}

void ImgEdit::contBright(double a, int b)//addgrey error check
{

    imRedo.clear();
    pushUndo(getMat());
    Mat im = getMat();
    Mat imConv;
    auto start = chrono::high_resolution_clock::now();
    im.convertTo(imConv,-1,a,b);
    auto  stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    qDebug() << "covertTo:" <<duration.count() <<"ms";
    setCurrMat(imConv);
}

void ImgEdit::HLS(int hue,int light, int sat )
{
    imRedo.clear();
    pushUndo(getMat());
    Mat in = getMat();
    Mat im;
    in.copyTo(im);
    bool grey = ifGrey(&im);
    if(grey){
        cvtColor(im,im,CV_GRAY2BGR);
    }
    cvtColor(im,im,CV_BGR2HLS);

//https://stackoverflow.com/questions/8535650/how-to-change-saturation-values-with-opencv

        for(int y=0; y<im.cols; y++)
        {
            for(int x=0; x<im.rows; x++)
            {
                int cur1 = im.at<Vec3b>(Point(y,x))[0];
                int cur2 = im.at<Vec3b>(Point(y,x))[1];
                int cur3 = im.at<Vec3b>(Point(y,x))[2];
                cur1 += hue;
                cur2 += light;
                cur3 += sat;

                if(cur1 < 0) cur1= 0; else if(cur1 > 180) cur1 = 180;
                if(cur2 < 0) cur2= 0; else if(cur2 > 100) cur2 = 100;
                if(cur3 < 0) cur3= 0; else if(cur3 > 100) cur3 = 100;

                im.at<Vec3b>(Point(y,x))[0] = cur1;
                im.at<Vec3b>(Point(y,x))[1] = cur2;
                im.at<Vec3b>(Point(y,x))[2] = cur3;
                //qDebug()<< "hue:  " << im.at<Vec3b>(Point(y,x))[0] << "sat: " << im.at<Vec3b>(Point(y,x))[0] << "light:" <<im.at<Vec3b>(Point(y,x))[0] ;
            }
        }
        qDebug() <<  "new";
        Mat imOut;
        im.copyTo(imOut);
        cvtColor(im,imOut,CV_HLS2BGR);
        /*for(int y=0; y<im.cols; y++)
        {
            for(int x=0; x<im.rows; x++)
            {
                qDebug()<< "hue:  " << imOut.at<Vec3b>(Point(x,y))[0] << "sat: " << imOut.at<Vec3b>(Point(x,y))[0] << "light:" <<imOut.at<Vec3b>(Point(x,y))[0] ;
        }}*/
        if(grey){
            cvtColor(imOut,imOut,CV_RGB2GRAY);
        }//need tocheck  values  by converting back to  hls  and checkingeach val
        setCurrMat(imOut);
}

void ImgEdit::redo(){
    popRedo();
}

void ImgEdit::undo(){
    popUndo();
}
//pub




//priv
void ImgEdit::setCurrMat(Mat im)
{
    mImg = im;
}

bool ImgEdit::ifGrey(Mat *im)
{
    if(im->channels()==1){return true;}
    return false;
}

void ImgEdit::toColour(Mat &src, Mat &dst)
{
    cvtColor(src, dst, cv::COLOR_GRAY2BGR);

}

//better algorithm is needed works WRONG with white/color balance and mirroring (Images are too similar so are considered  the same) ///UNUSED
bool ImgEdit::compMat(const Mat &a, const Mat &b)
{
    if ( (a.rows != b.rows) || (a.cols != b.cols) )
            return false;
    Scalar s = sum( a - b );
    return (s[0]==0) && (s[1]==0) && (s[2]==0);

}
//need to check if images are the same before adding them to version chain
void ImgEdit::pushUndo(Mat inMat)
{
    if((int)imUndo.size()<imMax){
      imUndo.push_back(inMat);
    }
    else if (imMax == (int)imUndo.size()){
        vector<Mat> temp;
        for(int i=1; i<=(int)imUndo.size(); i++ ){
            temp[i-1] = imUndo[i];
        }
        imUndo.swap(temp);
        temp.clear();
        imUndo.push_back(inMat);
        //imRedo.clear();
    }

}

void ImgEdit::popUndo()
{
    if(!imUndo.empty()){
            pushRedo(getMat());
            Mat outMat = imUndo.back();
            imUndo.pop_back();
            setCurrMat(outMat);
    }
}

void ImgEdit::pushRedo(Mat inMat)
{
    if((int)imRedo.size()<imMax){
      imRedo.push_back(inMat);
    }
    else if (imMax == (int)imRedo.size()){
        vector<Mat> temp;
        for(int i=1; i<=(int)imRedo.size(); i++ ){
            temp[i-1] = imRedo[i];
        }
        imRedo.swap(temp);
        temp.clear();
        imRedo.push_back(inMat);
    }
}

void ImgEdit::popRedo()
{
    if(!imRedo.empty()){
        pushUndo(getMat());
        Mat outMat = imRedo.back();
        imRedo.pop_back();
        setCurrMat(outMat);

    }
}




