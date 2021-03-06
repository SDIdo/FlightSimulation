/*
 * File:   BinaryExpression.h
 * Author: idox
 *
 * Created on December 17, 2018, 8:43 PM
 */

#ifndef PROJECTPART1_BINARYEXPRESSION_H
#define PROJECTPART1_BINARYEXPRESSION_H

#include "Expression.h"

/**
 * Binary expressions is any type of binary operation which could hold two
 * autonomous expressions, and make calculations with them.
 */
class BinaryExpression : public Expression{
public:
    Expression* left;
    Expression* right;
    virtual void set(Expression*, Expression*);
    virtual double calculate() = 0;
    virtual ~BinaryExpression(){
        delete (left);
        delete (right);
    };
};


#endif //PROJECTPART1_BINARYEXPRESSION_H
