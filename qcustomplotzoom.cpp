/*
    A derived class from QCustomPlot for a easy to use plot zoom function.


    LICENSE: GNU GPLv3
*/



#include <QRubberBand>
#include "qcustomplotzoom.h"


QCustomPlotZoom::QCustomPlotZoom(QWidget* parent)
    : QCustomPlot(parent)
    , zoomMode(false)
    , errorBars(nullptr)
    , rubberBand(new QRubberBand(QRubberBand::Rectangle, this))
{}

QCustomPlotZoom::~QCustomPlotZoom()
{
    delete rubberBand;
}

void QCustomPlotZoom::setZoomMode(bool mode)
{
    zoomMode = mode;
}

void QCustomPlotZoom::setErrorBars(size_t graphNr)
{
    if(errorBars != nullptr)
    {
        delete errorBars;
    }

    errorBars = new QCPErrorBars(this->xAxis, this->yAxis);
    errorBars->removeFromLegend();
    //errorBars->setAntialiased(false);
    //errorBars->setPen(QPen(QColor(180,180,180)));
    if(graphCount() > graphNr)
        errorBars->setDataPlottable(this->graph(graphNr));
}

void QCustomPlotZoom::setErrorBarsData(const QVector<double> &error_data)
{
    if(errorBars != nullptr)
    {
        errorBars->setData(error_data);
    }
}

void QCustomPlotZoom::mousePressEvent(QMouseEvent * event)
{
    switch(event->button())
    {
    case Qt::LeftButton:

        if(zoomMode)
        {
            origin = event->pos();
            rubberBand->setGeometry(QRect(origin, QSize()));
            rubberBand->show();
        }

        break;

    case Qt::RightButton:

        break;

    case Qt::MiddleButton:
        rescaleAxes();
        replot();
        break;

    default:
        break;
    }


    QCustomPlot::mousePressEvent(event);
}

void QCustomPlotZoom::mouseMoveEvent(QMouseEvent * event)
{
    if(rubberBand->isVisible())
    {
        rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    }
    QCustomPlot::mouseMoveEvent(event);
}

void QCustomPlotZoom::mouseReleaseEvent(QMouseEvent * event)
{
    if(rubberBand->isVisible())
    {
        const QRect & zoomRect = rubberBand->geometry();
        int xp1, yp1, xp2, yp2;
        zoomRect.getCoords(&xp1, &yp1, &xp2, &yp2);

        // zoom in only if the rect is bigger than 5px x 5px
        int tol = 5;
        if(abs(xp2-xp1) > tol && abs(yp2-yp1) > tol)
        {
            if(event->button() == Qt::LeftButton)
            {
                for(int j = 0; j < axisRectCount(); j++)
                {
                    for(int i = 0; i < axisRect(j)->axisCount(QCPAxis::atBottom); i++)
                    {
                        auto myAxis = axisRect(j)->axis(QCPAxis::atBottom, i);
                        auto x1 = myAxis->pixelToCoord(xp1);
                        auto x2 = myAxis->pixelToCoord(xp2);
                        myAxis->setRange(x1, x2);
                    }

                    for(int i = 0; i < axisRect(j)->axisCount(QCPAxis::atLeft); i++)
                    {
                        auto myAxis = axisRect(j)->axis(QCPAxis::atLeft, i);
                        auto y1 = myAxis->pixelToCoord(yp1);
                        auto y2 = myAxis->pixelToCoord(yp2);
                        myAxis->setRange(y1, y2);
                    }
                }
            }
            else if(event->button() == Qt::RightButton)
            {

            }
        }

        rubberBand->hide();
        replot();
    }
    
    QCustomPlot::mouseReleaseEvent(event);
}


void QCustomPlotZoom::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case Qt::Key_L:

        if(yAxis->scaleType() == QCPAxis::ScaleType::stLinear)
            yAxis->setScaleType(QCPAxis::ScaleType::stLogarithmic);
        else
            yAxis->setScaleType(QCPAxis::ScaleType::stLinear);

        rescaleAxes();
        replot();

        break;
    default:
        break;
    }

    QCustomPlot::keyPressEvent(event);
}

void QCustomPlotZoom::keyReleaseEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Control)
    {

    }

    QCustomPlot::keyReleaseEvent(event);
}

