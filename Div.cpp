/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Div.h"

Div::Div(Expression* newLeft, Expression* newRight) {
    left = newLeft;
    right = newRight;
}

double Div::calculate() {
    return (left->calculate() / right->calculate());
}