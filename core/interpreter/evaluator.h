#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "core/module.h"
#include "core/interpreter/variable.h"
#include "core/interpreter/variablepath.h"
#include "core/interpreter/scope/scope.h"

class Program;

/**
 * @brief Provides functions to evaluate \link Program program nodes\endlink
 */
class Evaluator
{
public:
    /**
     * @param scope Used to access variables
     * @param module Used to access function
     */
    Evaluator(const Scope& scope = Scope(), const Module& module = Module());

    /**
     * @brief Evaluate a right value tagged \link Program program node\endlink
     */
    Variable rightValue(const Program& program) const;

    /**
     * @brief Get the \link VariablePath variable path\endlink of a variable
     * tagged \link Program program node\endlink.
     */
    VariablePath variablePath(const Program& program) const;

    /**
     * @brief Evaluate a type tagged \link Program program node\endlink
     */
    ObjectType type(const Program& program) const;
private:
    Variable unaryOperation(int op, Variable a) const;
    Variable binaryOperation(int op, Variable a, Variable b) const;
    Variable ternaryOperation(int op, Variable a, Variable b, Variable c) const;
    Variable function(const Program& program) const;
    Variable variable(const Program& program) const;

    const Scope& scope;
    const Module& module;
};

#endif // EVALUATOR_H
