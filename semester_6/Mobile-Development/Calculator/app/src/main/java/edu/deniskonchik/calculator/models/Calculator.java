package edu.deniskonchik.calculator.models;

import net.objecthunter.exp4j.*;

public class Calculator {
    public static double Evaluate(String expression) {
        return new ExpressionBuilder(expression).build().evaluate();
    }
}
