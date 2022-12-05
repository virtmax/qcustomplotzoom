# qcustomplotzoom
A derived class from QCustomPlot (http://qcustomplot.com/) for an easy to use plot zoom function.


### Functionality: 

###### Zoom
- Activate with ->setZoomMode(true);
- Hold right mouse key to select a zoom region. 
- Click middle mouse key to rescale the plot.

###### Keys

- L: Switch between logarithmic and linear scaling

###### Error bars
- Enable error bars for a graph with ->setErrorBars(graphNr);
- Set error bars data with ->setErrorBarsData(const QVector<double> &error_data);

