/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Value.cxx
 * Author: zipper
 * 
 * Created on August 27, 2018, 6:33 PM
 */

#include "Logger.hxx"
#include "Value.hxx"

using namespace std;

namespace even {

    /** @brief Construct integer Value */
    Value::Value(int value_, const QString &intro_) :
    Value(QVariant(value_), intro_) {

    }

    /** @brief Construct text Value */
    Value::Value(QString text_, const QString &intro_) :
    Value(QVariant(text_), intro_) {
    }

    /** @brief Construct float Value */
    Value::Value(float double_, const QString &intro_) :
    Value(QVariant(double_), intro_) {

    }

    /** @brief Construct QVariant Value */
    Value::Value(const QVariant value_, const QString &intro_) :
    _object{value_, intro_}
    {
        DEBUG(15) 
                << u8"Create value: " << value_.toString()
                << ", intro '" << intro_ << "'";
    }

    /** @brief Copy constructor. */
    Value::Value(const Value& orig) :
    QObject(),
    _object(orig._object) {
    }

    Value::~Value() {
    }

    Value::Value() :
    _object{QVariant(), u8"unnamed"}
    {

    }

    /** @brief Copy operator. */
    Value& Value::operator=(const Value& value_) {
        _object = {value_.value(), value_.name()};
        return *this;
    }

    /** 
     * @brief Set config value by name. 
     * @param intro_ - value name
     * @param value_ - value object
     * @return none
     */
    void Value::setValue(const QString &intro_, const QVariant &value_) {
        DEBUG(15) 
                << u8"Change value is " << name()
                << " to " << value_.toString()
                << ", change intro '" << value().toString()
                << "' to " << value_.toString();
        _object = {value_, intro_};
    }

    /**
     * Get value .
     * @return - QVariant object of value
     */
    const QVariant& Value::value() const {
        return _object._value;
    }

    /**
     * Get name.
     * @return - QString name of value
     */
    const QString &Value::name() const {
        return _object._intro;
    }

};

