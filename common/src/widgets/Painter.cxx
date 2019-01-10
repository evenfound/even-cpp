/**
 * @file    ChartEasy.cxx
 * @author  E. Pozdnyakov
 *
 * @brief   Entity of ChartEasy class methods.
 *
 * @date    Created on October 5, 2018, 01:26 PM
 */

#include "ChartEasy.hxx"
#include "Logger.hxx"

#include <QWidget>
#include <QtMath>

using namespace even;

//------------------------------------------------------------------------------
ChartEasy::ChartEasy(QWidget* parent_)
    : QGraphicsView(parent_)
    , _scene(this)
{
    setScene(&_scene);
    fitInView(_scene.sceneRect(), Qt::KeepAspectRatio);
}

//------------------------------------------------------------------------------
void ChartEasy::setHorizontalRange(qreal min_, qreal max_) {
    _axis[0].min = min_;
    _axis[0].max = max_;
}

//------------------------------------------------------------------------------
void ChartEasy::setVerticalRange(qreal min_, qreal max_) {
    _axis[1].min = min_;
    _axis[1].max = max_;
}

//------------------------------------------------------------------------------
void ChartEasy::addSeries(int id_, int thin_, QColor color_, QString label_) {
    QGraphicsItemGroup* newGroup = new QGraphicsItemGroup();
    _scene.addItem(newGroup);
    _series.insert(id_, { thin_, color_, label_, newGroup});
}

//------------------------------------------------------------------------------
void ChartEasy::removeSeries(int id_) {
    _series.remove(id_);
}

//------------------------------------------------------------------------------
void ChartEasy::addSeriesPoint(int id_, qreal x_, qreal y_) {
    auto series = _series.find(id_);
    if(series != _series.end()) {
        series->data.insert(x_, y_);
        INFO(20) << QString("add to series %1 x = %2, y = %3")
                    .arg(id_)
                    .arg(x_)
                    .arg(y_);
    }
}

//------------------------------------------------------------------------------
void ChartEasy::setSeriesColor(int id_, QColor color_) {
    auto series = _series.find(id_);
    if(series != _series.end()) {
        series->color = color_;
    }
}

//------------------------------------------------------------------------------
void ChartEasy::setSeriesThin(int id_, int thin_) {
    auto series = _series.find(id_);
    if(series != _series.end()) {
        series->thin = thin_;
    }
}

//------------------------------------------------------------------------------
void ChartEasy::buildScene()
{
    scale(width()/(_axis[0].max - _axis[0].min),
            -height()/(_axis[1].max - _axis[1].min));
    translate(qFabs(_axis[0].min), qFabs(_axis[1].min));
    //rotate(-90);

    INFO(10) << QString("Window %1 %2").arg(width()).arg(height());

/*
    _scene.setSceneRect(_axisMargin.top(), _axisMargin.right(),
                         _axisMargin.bottom(), _axisMargin.left());*/

    for(auto &a: _series) {
        _deleteItemsFromGroup(a.group);
        _drawSeries(a);
    }
}

//------------------------------------------------------------------------------
void ChartEasy::_drawSeries(const Series& _series)
{
    for(auto a = _series.data.begin(); a != _series.data.end() - 1; ++a) {
        _series.group->addToGroup(_scene.addLine(
                                      a.key(), a.value(),
                                      (a + 1).key(), (a + 1).value(), QPen(QBrush(_series.color), _series.thin)));
        INFO(10) << QString("Line %1 %2 %3 %4").arg(a.key()).arg(a.value()).arg((a + 1).key()).arg((a + 1).value());
    }
}

//------------------------------------------------------------------------------
void ChartEasy::_deleteItemsFromGroup(QGraphicsItemGroup *group_)
{
    foreach(auto item, _scene.items(group_->boundingRect())) {
        if(item->group() == group_ ) {
            delete item;
        }
    }
}

//------------------------------------------------------------------------------
void ChartEasy::resizeEvent(QResizeEvent* event_)
{
    buildScene();
    QGraphicsView::resizeEvent(event_);
}

