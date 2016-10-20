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
    if(zoomMode)
    {
        if(event->button() == Qt::LeftButton)
        {
            origin = event->pos();
            rubberBand->setGeometry(QRect(origin, QSize()));
            rubberBand->show();
        }

        if(event->button() == Qt::RightButton)
        {

        }

        if(event->button() == Qt::MiddleButton)
        {
            rescaleAxes();
            replot();
        }
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
        auto x1 = xAxis->pixelToCoord(xp1);
        auto x2 = xAxis->pixelToCoord(xp2);
        auto y1 = yAxis->pixelToCoord(yp1);
        auto y2 = yAxis->pixelToCoord(yp2);

        xAxis->setRange(x1, x2);
        yAxis->setRange(y1, y2);

        rubberBand->hide();
        replot();
    }
    
    QCustomPlot::mouseReleaseEvent(event);
}


void QCustomPlotZoom::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Control)
    {

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

