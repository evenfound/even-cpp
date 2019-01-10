/**
 * @file    ValueSlider.cpp
 * @author  E. Pozdnyakov
 *
 * @date    Created on October 2, 2018, 7:49 PM
 */

#include "ValueSlider.hxx"
#include "Logger.hxx"

#include <QtWidgets>
#include <QHBoxLayout>

using namespace even;

//------------------------------------------------------------------------------
ValueSlider::ValueSlider(QObject* value_, QWidget *parent)
    : QGroupBox(dynamic_cast<Value*>(value_)->intro(), parent),
      _value(dynamic_cast<Value*>(value_))
{
    Value::Range r = _value->range();

    QBoxLayout *slidersLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    _minLabel = new QLabel(QString("%1").arg(r.min, 0, 'f', 2));
    _minLabel->setFont({"Arial", 6, QFont::Normal});
    _maxLabel = new QLabel(QString("%1").arg(r.max, 0, 'f', 2));
    _maxLabel->setFont({"Arial", 6, QFont::Normal});
    _valueLabel = new QLabel(QString("%1").arg(_value->get().toDouble(), 0, 'f', 2));
    _valueLabel->setFont({"Arial", 12, QFont::Normal});

    _slider = new QSlider(Qt::Horizontal);
    _slider->setFocusPolicy(Qt::StrongFocus);
    _slider->setTickPosition(QSlider::TicksBothSides);
    //_slider->setTickInterval(r.step);
    _slider->setRange(0, r.step);
    _slider->setSingleStep(1);
    _slider->setValue(r.step/(r.max - r.min) * _value->get().toDouble());

    connect(_slider, SIGNAL(valueChanged(int)), value_, SLOT(sliderUpdated(int)));
    connect(_slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

    slidersLayout->addWidget(_minLabel);
    slidersLayout->addWidget(_slider);
    slidersLayout->addWidget(_maxLabel);
    slidersLayout->addWidget(_valueLabel);
    setLayout(slidersLayout);
}

//------------------------------------------------------------------------------
void ValueSlider::setValue(int value)
{
    Value::Range r = _value->range();
    _value->setValue(value * (r.max - r.min)/r.step);
    _valueLabel->setText(QString("%1").arg(_value->get().toDouble(), 0, 'f', 2));
}


