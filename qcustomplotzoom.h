/*
    A derived class from QCustomPlot for a easy to use plot zoom function.


    LICENSE: GNU GPLv3
*/

#pragma once

#include <QPoint>
#include "qcustomplot/qcustomplot.h"

class QRubberBand;
class QMouseEvent;
class QWidget;

class QCustomPlotZoom : public QCustomPlot
{
	Q_OBJECT

public:
    QCustomPlotZoom(QWidget* parent = 0);
    virtual ~QCustomPlotZoom();

	void setZoomMode(bool on);

    void setErrorBars(size_t graphNr);
    void setErrorBarsData(const QVector<double> &error_data);


private slots:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    QCPErrorBars *errorBars;
    bool zoomMode;
    QRubberBand* rubberBand;
    QPoint origin;
};
