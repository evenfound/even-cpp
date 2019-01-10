/**
 * @file    Scene.cxx
 * @author  E. Pozdnyakov
 *
 * @brief   Class methods of Scene Entity.
 *
 * @date    Created on October 17, 2018, 05:12 PM
 */

#include "Scene.hxx"
#include "Logger.hxx"

#include <QWidget>
#include <QtMath>

using namespace even;

//------------------------------------------------------------------------------
Scene::Scene(QPaintDevice* device_,
             qreal margin_[4], qreal xmin_, qreal xmax_, qreal ymin_, qreal ymax_)
    : QPainter(device_)
    , _margin{margin_[0], margin_[1], margin_[2], margin_[3]}
    , _xmin(xmin_)
    , _xmax(xmax_)
    , _ymin(ymin_)
    , _ymax(ymax_)
    , _fontMetrics(_font)
{
    fillRect(0, 0, device_->width(), device_->height(), {Qt::lightGray});
    setRenderHint(QPainter::Antialiasing, true);

    _scale_x = (device_->width() - _margin[3] - _margin[1])/(_xmax - _xmin);
    _scale_y = (device_->height() - _margin[2] - _margin[0])/(_ymax - _ymin);

    _font.setStyleHint(QFont::Times, QFont::PreferAntialias);
    _font.setStretch(_fontStretch);
    _font.setPixelSize(9);
    _font.setFixedPitch(true);
    setFont(_font);


}

//------------------------------------------------------------------------------
void Scene::drawText(qreal x_, qreal y_, QString text_, QPen pen_) {
    QRectF rect = _fontMetrics.boundingRect(text_);
    setPen(pen_);
    QPainter::drawText({
                           _margin[3] - _scale_x * (_xmin - x_)
                           ,  device()->height() - _margin[2] + _ymin * _scale_y - y_
                           , _scale_x * rect.width()
                           , _scale_y * rect.height()
                       }, text_, Qt::AlignLeft | Qt::AlignTop);
}

//------------------------------------------------------------------------------
void Scene::drawLine(qreal x1_, qreal y1_, qreal x2_, qreal y2_, const QPen &pen_) {
    setPen(pen_);
    QPainter::drawLine(
                QPointF(_margin[3] - _scale_x * (_xmin - x1_)
                , device()->height() - _margin[2] + _scale_y * (_ymin - y1_))
                , QPointF(_margin[3] - _scale_x * (_xmin - x2_)
                , device()->height() - _margin[2] + _scale_y * (_ymin - y2_))
            );
}

//------------------------------------------------------------------------------
void Scene::drawRect(const QRectF& rect_, const QPen &pen_, const QBrush &brush_) {
    setPen(pen_);
    setBrush(brush_);
    QPainter::drawRect(rect_);
}

//------------------------------------------------------------------------------
void Scene::drawRectOnChart(const QRectF& rect_, const QPen &pen_, const QBrush &brush_) {
    setPen(pen_);
    setBrush(brush_);
    QPainter::drawRect(QRectF(
            _margin[3] - _scale_x * (_xmin - rect_.left())
            , device()->height() - _margin[2] + _scale_y * (_ymin - rect_.top())
            , _scale_x * rect_.width()
            , _scale_y * rect_.height()
            ));
}




