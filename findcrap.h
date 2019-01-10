#ifndef FINDCRAP_H
#define FINDCRAP_H

#include <QWidget>
#include <QtMultimedia/QCameraInfo>
#include "cqtopencvviewergl.h"
#include "ledindicator.h"

#define MAXCAMERAS 5

namespace Ui {
class Findcrap;
}

class Findcrap : public QWidget
{
    Q_OBJECT

public:
    explicit Findcrap(QWidget *parent = 0);
    ~Findcrap();

private slots:
    void on_ProfileButton_clicked();
    void on_startButton_clicked();

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::Findcrap *ui;
    void GetTextFile();
    QString profilename;
    cv::VideoCapture mCapture;
    cv::Mat     mOrigImage;
    double lasttime;
    QList<QCameraInfo> cameras;
    LedIndicator *myLedIndicator;

    std::vector<int> FindCameras(void);
};

#endif // FINDCRAP_H
