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


namespace even {

    class Value : public QObject {
        Q_OBJECT
    public:

        /** @brief Construct integer Value */
        Value(int value_, const QString &intro_);

        /** @brief Construct text Value */
        Value(QString text_, const QString &intro_);

        /** @brief Construct float Value */
        Value(float double_, const QString &intro_);

        /** @brief Construct QVariant Value */
        Value(const QVariant value_, const QString &intro_ = u8"unnamed");

        Value(const Value& orig);

        /** @brief Default constructor */
        Value();

        virtual ~Value();

        /** @brief Copy operator. */
        Value& operator=(const Value& value_);

        /**
         * @brief Set config value by name. 
         * @param intro_ - value name
         * @param value_ - value object
         * @return none
         */
        void setValue(const QString &intro_, const QVariant &value_);

        /**
         * Get value .
         * @return - QVariant object of value
         */
        const QVariant& value() const;

        /**
         * Get name.
         * @return - QString name of value
         */
        const QString &name() const;
        
    private:

        /** @brief Private value data struct.*/
        struct _Value {
            /** @brief Value data */
            QVariant _value;
            /** @brief Valur introduction. */
            QString _intro;
        };

        /** @brief Object of private _Value struct */
        _Value _object;

    };

};

#endif /* VALUE_HXX */

