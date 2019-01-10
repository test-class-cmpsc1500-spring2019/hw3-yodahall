#include "findcrap.h"
#include "ui_findcrap.h"
#include <QInputDialog>
#include <QDir>



Findcrap::Findcrap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Findcrap)
{
    ui->setupUi(this);
    myLedIndicator = new LedIndicator();
    ui->LEDgridLayout->addWidget(myLedIndicator,0,0);
    // get the cameras
    cameras = QCameraInfo::availableCameras();
    //foreach(const QCameraInfo &cameraInfo, cameras)
    for (int i=0;i<cameras.size();i++)
    {
        const QCameraInfo cameraInfo = cameras[i];
        qDebug() << cameraInfo.deviceName();
        ui->cameraComboBox->addItem(cameraInfo.deviceName());
    }
}

Findcrap::~Findcrap()
{
    delete ui;
}

void Findcrap::on_ProfileButton_clicked()
{
    // pop up edit box for name
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("User name:"), QLineEdit::Normal,
                                            QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
           ui->statusbox->append(text);

    // send image to nexaface cache
}

void Findcrap::timerEvent(QTimerEvent *event)
{
    cv::Mat image;
    mCapture >> image;
    mOrigImage = image;

    // Do what you want with the image :-)

    // Show the image
    ui->openCVviewer->showImage(image);
    
    double rightnow = cv::getTickCount();
    double elapsedTime = (rightnow - lasttime) / cv::getTickFrequency();
    lasttime = rightnow;    // reset the timer
    
    double fps = 1.0 / elapsedTime;
    std::string fpsText = cv::format("fps=%01.1f", fps);
    cv::putText(image, fpsText, cv::Point(10, 10), cv::FONT_HERSHEY_PLAIN, 0.8, CV_RGB(0, 255, 0), 1.0);

    ui->openCVviewer->showImage(image);
}


void Findcrap::on_startButton_clicked()
{
    if (!mCapture.isOpened())
    {
        int deviceID = ui->cameraComboBox->currentIndex();
        if (!mCapture.open(deviceID))
            return;
    }

    startTimer(0);
}

std::vector<int> Findcrap::FindCameras(void)
{
    std::vector<int> result;
#if 1

#else

    
    cv::VideoCapture temp_camera;
    int maxTested = 10;
    for (int i = 0; i < MAXCAMERAS; i++) {
        cv::VideoCapture temp_camera(i);
        bool res = (!temp_camera.isOpened());
        temp_camera.release();
        result.push_back(i);
/*
        if (res)
        {
            return i;
        }
        */
    }

#endif
    return result;
}
