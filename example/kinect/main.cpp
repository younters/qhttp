#include "qhttpserver.hpp"
#include "qhttpserverresponse.hpp"
#include "qhttpserverrequest.hpp"

#include "qhttpclient.hpp"
#include "qhttpclientrequest.hpp"
#include "qhttpclientresponse.hpp"

#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QUrlQuery>

#include <QLocalServer>
#include <QTimer>
#include <QTime>
#include <QThread>
//usr/local/Cellar/libusb/1.0.20/include/libusb-1.0 /

//#include "../../libusb-1.0/libusb.h"

//#include <libfreenect/libfreenect.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "../include/unixcatcher.hpp"
///////////////////////////////////////////////////////////////////////////////

using namespace cv;
using namespace std;

VideoCapture cap(0);
void runServer(QCoreApplication& app, const QString& portOrPath) {
    using namespace qhttp::server;

    QHttpServer server(&app);
    // listening tcp port or Unix path



      //prepare_video();

    server.listen(portOrPath, [](QHttpRequest* req, QHttpResponse* res) {



        //if(!cap.isOpened())  // check if we succeeded
          //  return;

        Mat edges;

        //whileloop
        Mat frame;
            cap >> frame; // get a new frame from camera
        //cap.read(&frame);
        //frame = imread("./Alpaca1.jpg", CV_LOAD_IMAGE_COLOR);

            cvtColor(frame, edges, CV_BGR2GRAY);



                // QByteArray BoundaryString = ("--boundary\r\n" \
                                             "Content-Type: image/jpeg\r\n" \
                                             "Content-Length: ");

                //BoundaryString.append(QString::number(CurrentImg.length()));

                //BoundaryString.append("\r\n\r\n");
                QByteArray ContentType = ("HTTP/1.0 200 OK\r\n" \
                                          "Server: localhost example server\r\n" \
                                          "Cache-Control: no-cache\r\n" \
                                          "Cache-Control: private\r\n" \
                                          "Content-Type: multipart/x-mixed-replace;boundary=--boundary\r\n\r\n");

                res->write(ContentType);

                while(1){

                    std::vector<uchar> buff;
                    imencode(".jpg",frame,buff);
                        std::string content(buff.begin(), buff.end());
                        QByteArray CurrentImg(QByteArray::fromStdString(content));



                            QByteArray BoundaryString = ("--boundary\r\n" \
                                                         "Content-Type: image/jpeg\r\n" \
                                                         "Content-Length: ");

                            BoundaryString.append(QString::number(CurrentImg.length()));
                            BoundaryString.append("\r\n\r\n");
                    //res->write(BoundaryString);
                            res->addHeader("Content-Length", QByteArray::number(CurrentImg.length()));
                            res->addHeader("Content-Type", "image/jpeg");
                    res->end(CurrentImg);
                    //res->flush();
                    QThread::msleep((1000/5));
                   /* QTime dieTime = QTime::currentTime().addSecs(1);
                    while (QTime::currentTime() < dieTime)
                        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);*/

                }
        /*res->setStatusCode(qhttp::ESTATUS_OK);      // status 200
        res->addHeader("connection", "");      // it's the default header, this line can be omitted.

        res->end(CurrentImg);*/
        //res->end("Hello World!\n");                 // response body data

        // when "connection: close", the req and res will be deleted automatically.

        // optionally let the clients to shut down the server
        if ( req->headers().keyHasValue("command", "quit") ) {
            printf("a client sends a quit command.\nserver quits.\n");
            QCoreApplication::quit();
            return;
        }
    });

    if ( !server.isListening() ) {
        fprintf(stderr, "failed. can not listen at port %s!\n", qPrintable(portOrPath));
        return;
    }

    app.exec();                 // application's main event loop
}

///////////////////////////////////////////////////////////////////////////////
/*int init_kinect() {
    if (freenect_init(&f_ctx, NULL) < 0) {
        printf("Freenect Framework Initialization Failed!\n");
        return 1;
    }

    freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));
    int nr_devices = freenect_num_devices (f_ctx);

    if (nr_devices < 1) {
        printf("No Kinect Sensors were detected! %i\n", nr_devices);
        freenect_shutdown(f_ctx);
        return 1;
    }

    if (freenect_open_device(f_ctx, &f_dev, 0) < 0) {
        printf("Could not open Kinect Device\n");
        freenect_shutdown(f_ctx);
        return 1;
    }

    freenect_set_tilt_degs(f_dev, 0);
    freenect_set_depth_callback(f_dev, depth_callback);
    freenect_set_video_callback(f_dev, rgb_callback);

    freenect_set_depth_mode(f_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_MM));
    // freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB));
    freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_IR_8BIT));

    freenect_start_depth(f_dev);
    freenect_start_video(f_dev);
    return 0;
}*/
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv) {

    QCoreApplication app(argc, argv);
#if defined(Q_OS_UNIX)
    catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
#endif

    app.setApplicationName("kinect");
    app.setApplicationVersion("1.0.0");
    cap.open(0);
    runServer(app, "3164");
    /*
    QCommandLineParser parser;
    parser.setApplicationDescription("a HelloWorld example for http client and server.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("mode",
                                 "working mode: server, client or weather. default: server");

    parser.addOption(QCommandLineOption(QStringList() << "p" << "port",
                                        "tcp port number or path of UNIX socket in server/client modes, default: 8080",
                                        "port/path", "8080"));
    parser.process(app);


    QStringList posArgs = parser.positionalArguments();
    if ( posArgs.size() == 1    &&    posArgs.at(0) == QLatin1Literal("server") ) {
        runServer(app, parser.value("port"));

    } else {
        parser.showHelp(0);
    }*/

    return 0;
}
