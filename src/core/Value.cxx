/**
 * @file    Value.cxx
 * @author  E. Pozdnyakov
 *
 * @date    Created on August 27, 2018, 7:49 PM
 */


#include "Logger.hxx"
#include "Value.hxx"

using namespace std;
using namespace even;

//------------------------------------------------------------------------------
void Value::sliderUpdated(int) {
    //_object._value = value_;
    switch(_object._value.type()) {
    case QVariant::Double:
        break;
    }
    DEBUG(15)
            << u8"Update value: " <<_object._value.toString()
            << ", name: '" << _object._name  << "'"
            << ", intro: '" << _object._intro << "'";
}

//------------------------------------------------------------------------------
Value::Value(int value_, const QString &name_,
             const QString &intro_, Value::Range range_) :
    Value(QVariant(value_), name_, intro_, range_) {
}

//------------------------------------------------------------------------------
Value::Value(QString text_, const QString &name_, const QString &intro_) :
    Value(QVariant(text_), name_, intro_) {
}

//------------------------------------------------------------------------------
Value::Value(float double_, const QString &name_,
             const QString &intro_, Value::Range range_) :
    Value(QVariant(double_), name_, intro_, range_) {

}

//------------------------------------------------------------------------------
Value::Value(const QVariant value_, const QString &name_,
             const QString &intro_, Value::Range range_) :
    _object{value_, name_, intro_},
    _range(range_)
{
    DEBUG(20)
            << u8"Create value: " << QString("%1").arg(_object._value.toDouble(), 0, 'f', 2)
            << ", name: '"  << _object._name  << "'"
            << ", intro: '" << _object._intro << "'"
            << ", min: "    << QString("%1").arg(_range.min)
            << ", max: "    << QString("%1").arg(_range.max)
            << ", step: "   << QString("%1").arg(_range.step);
}

//------------------------------------------------------------------------------
Value::Value(const Value& orig) :
    QObject(),
    _object (orig._object),
    _range  (orig._range)
{
}

//------------------------------------------------------------------------------
Value::Value() :
    _object{QVariant(), u8"unnamed", u8"unknown usage"}
{
}

//------------------------------------------------------------------------------
Value& Value::operator=(const Value& value_) {
    _object = {value_.get(), value_.name(), value_.intro()};
    _range  = {value_.range().min, value_.range().max, value_.range().step };
    return *this;
}

//------------------------------------------------------------------------------
void Value::setValue(const QVariant &value_) {
    DEBUG(15)
            << u8"Change value: '"  << name() << "'"
            << " from "             << get().toString()
            << " to "               << value_.toString();
    _object._value = value_;
}

//------------------------------------------------------------------------------
QJsonObject Value::encode() {
    QJsonObject root;
    root.insert(u8"value", _object._value.toJsonValue());
    root.insert(u8"intro", _object._intro);
    return root;
}
