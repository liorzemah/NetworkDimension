#ifndef IVALIDEXPRESSION_H
#define IVALIDEXPRESSION_H

// Implement The Curiously Recurring Template Pattern (CRTP)
template<class DerivedClass, class ExpressionType>
class IValidExpression
{
public:
    static bool isValid(const ExpressionType& expression)
    {
        return DerivedClass::isValid(expression);
    }
};

#endif