/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Value.hxx
 * Author: zipper
 *
 * Created on August 27, 2018, 6:33 PM
 */

#ifndef VALUE_HXX
#define VALUE_HXX

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>

namespace even {

class Value : public QObject {
        Q_OBJECT
    public:
        /**
         * @brief Entitu for create control of range value set
         */
        struct Property {
                qreal min=0.0;      ///< @brief Minimum value set
                qreal max=1000.0;   ///< @brief Maximum value set
                qreal step=100.0;   ///< @brief Step of change value
                int prec=2;         ///< @brief Floatinp point precision
                bool visible=true;  ///< @brief Flag of show
        };

        /**
         * @brief Construct integer Value
         * @param value_    - same value
         * @param name_     - short name
         * @param intro_    - introduction for display
         * @param property_ - set range interval and step of change
         */
        Value(int value_, const QString &name_
              , const QString &intro_
              , Value::Property property_ = {0.0, 1000.0, 100.0, 2, true} );

        /**
         * @brief Construct text Value
         * @param text_     - same value
         * @param name_     - short name
         * @param intro_    - introduction for display
         */
        Value(QString text_
              , const QString &name_
              , const QString &intro_);

        /**
         * @brief Construct float Value
         * @param double_   - same value
         * @param name_     - short name
         * @param intro_    - introduction for display
         * @param property_ - set range interval and step of change
         */
        Value(float double_
              , const QString &name_
              , const QString &intro_
              , Value::Property property_ = {0.0, 1000.0, 100.0, 2, true});

        /**
         * @brief Construct QVariant Value
         * @param value_    - same value
         * @param name_     - short name
         * @param intro_    - introduction for display
         * @param property_ - set range interval and step of change
         */
        Value(const QVariant value_
              , const QString &name_= u8"unnamed"
                , const QString &intro_ = u8"unknown usage"
                , Value::Property property_ = {0.0, 1000.0, 100.0, 2, true});

        Value(const Value& orig);

        /** @brief Default constructor */
        Value();

        ~Value() final = default;

        /** @brief Copy operator. */
        Value& operator=(const Value& value_);

        /**
         * @brief Set config value by name.
         * @param value_ - value object
         */
        void setValue(const QVariant &value_);

        /**
         * @brief Get value.
         * @return - QVariant object of value
         */
        inline const QVariant& get() const {
            return _object._value;
        }

        /**
         * @brief Get name.
         * @return - QString name of value
         */
        inline const QString &name() const {
            return _object._name;
        }

        /**
         * @brief Get introduction string
         * @return explanation string
         */
        inline const QString &intro() const {
            return _object._intro;
        }

        /**
         * @brief Got value range of change
         * @return Range value
         */
        inline const Property &property() const {
            return _property;
        }

        /** @brief Return value set in json array packed */
        virtual QJsonObject encode();

    public slots:
        /** @brief Accepting value changes from slider control -- integer
         *         explanation
         */
        void sliderUpdated(int value_);

        
    private:

        /** @brief Private value data struct.*/
        struct _Value {
                QVariant _value;    ///< @brief Value data
                QString _name;      ///< @brief Value short name.
                QString _intro;     ///< @brief Value introduction.
        };

        _Value _object;                                     ///< @brief Object of private _Value struct
        Property _property = {0.0, 1000.0, 100.0, 2, true}; ///< @brief Range interval and step of change

};

};

#endif /* VALUE_HXX */

