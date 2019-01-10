/**
 * @file    Chart.cxx
 * @author  E. Pozdnyakov
 *
 * @brief   Entity of Chart class methods.
 *
 * @date    Created on October 5, 2018, 01:26 PM
 */

#include "Chart.hxx"
#include "Logger.hxx"

#include <QWidget>
#include <QtMath>

using namespace even;

//------------------------------------------------------------------------------
Chart::Chart(QWidget* parent_)
    : QGraphicsView(parent_)
    , _scene(this)
{
    setScene(&_scene);
    _scene.addItem(&_axisGroup);
    fitInView(_scene.sceneRect(), Qt::KeepAspectRatio);
    setAlignment(Qt::AlignBottom|Qt::AlignLeft);
}

//------------------------------------------------------------------------------
void Chart::setHorizontalRange(qreal min_, qreal max_) {
    _axis[0].min = min_;
    _axis[0].max = max_;
}

//------------------------------------------------------------------------------
void Chart::setVerticalRange(qreal min_, qreal max_) {
    _axis[1].min = min_;
    _axis[1].max = max_;
}

//------------------------------------------------------------------------------
void Chart::addSeries(int id_, int thin_, QColor color_, QString label_) {
    QGraphicsItemGroup* newGroup = new QGraphicsItemGroup();
    _scene.addItem(newGroup);
    _series.insert(id_, { thin_, color_, label_, newGroup});
}

//------------------------------------------------------------------------------
void Chart::removeSeries(int id_) {
    _series.remove(id_);
}

//------------------------------------------------------------------------------
void Chart::addSeriesPoint(int id_, qreal x_, qreal y_) {
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
void Chart::setSeriesColor(int id_, QColor color_) {
    auto series = _series.find(id_);
    if(series != _series.end()) {
        series->color = color_;
    }
}

//------------------------------------------------------------------------------
void Chart::setSeriesThin(int id_, int thin_) {
    auto series = _series.find(id_);
    if(series != _series.end()) {
        series->thin = thin_;
    }
}
//------------------------------------------------------------------------------
void Chart::setScale()
{
    resetMatrix();
    _scale_x = width()/(_axis[0].max - _axis[0].min);
    _scale_y = height()/(_axis[1].max - _axis[1].min);
    //scale(_scale_x, -_scale_y);
    //translate(qFabs(_axis[0].min), qFabs(_axis[1].min));
    //translate(10, 10);
    QTransform transform;
    //transform.translate(20.0, 20.0);
    transform.scale(_scale_x, -_scale_y);
    centerOn(100, 100);
    setTransform(transform);
}

//------------------------------------------------------------------------------
void Chart::drawAxis()
{
    _deleteItemsFromGroup(&_axisGroup);
    _axisGroup.addToGroup(_scene.addRect(
                              0, 0,
            (width() - _axisMargin[1] - _axisMargin[3])/_scale_x,
            (height() - _axisMargin[0] - _axisMargin[2])/_scale_y,
            QPen(QBrush(Qt::lightGray), 0.4/_scale_y),
            QBrush(Qt::transparent)));
}

//------------------------------------------------------------------------------
void Chart::buildScene()
{
    setRenderHints(QPainter::Antialiasing); //| QPainter::SmoothPixmapTransform

    setScale();
    drawAxis();
    //rotate(-90);


    INFO(10) << QString("Window %1 %2").arg(width()).arg(height());

/*
    _scene.setSceneRect(_axisMargin.top(), _axisMargin.right(),
                         _axisMargin.bottom(), _axisMargin.left());*/


    //_scene.addRect(_scene.sceneRect());

    for(auto &a: _series) {
        _deleteItemsFromGroup(a.group);
        _drawSeries(a);
    }
}

//------------------------------------------------------------------------------
void Chart::_drawSeries(const Series& _series)
{
    for(auto a = _series.data.begin(); a != _series.data.end() - 1; ++a) {
        _series.group->addToGroup(_scene.addLine(
                                      a.key(), a.value(),
                                      (a + 1).key(), (a + 1).value(), QPen(QBrush(_series.color), _series.thin/_scale_y)));
        INFO(10) << QString("Line %1 %2 %3 %4").arg(a.key()).arg(a.value()).arg((a + 1).key()).arg((a + 1).value());
    }
}

//------------------------------------------------------------------------------
void Chart::_deleteItemsFromGroup(QGraphicsItemGroup *group_)
{
    foreach(auto item, _scene.items(group_->boundingRect())) {
        if(item->group() == group_ ) {
            delete item;
        }
    }
}

//------------------------------------------------------------------------------
void Chart::resizeEvent(QResizeEvent* event_)
{
    buildScene();
    QGraphicsView::resizeEvent(event_);
}

//------------------------------------------------------------------------------
//void Chart::showEvent(QShowEvent* event_)
//{
//    QGraphicsView::showEvent(event_);


////    INFO(15) << QString("[%1,%2,%3,%4]")
////                .arg(_axisMargin[2])
////            .arg(_axisMargin[0])
////            .arg(width() - _axisMargin[2] - _axisMargin[1])
////            .arg(height() - _axisMargin[0] - _axisMargin[2]);

////    fitInView({
////                  _axisMargin[2]
////                  , _axisMargin[0]
////                  , width() - _axisMargin[2] - _axisMargin[1]
////                  , height() - _axisMargin[0] - _axisMargin[2]
////              }
////              , Qt::KeepAspectRatio);
//}
