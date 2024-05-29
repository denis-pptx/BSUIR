package edu.deniskonchik.calculator.models;

import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import net.objecthunter.exp4j.*;

public class CalculatorViewModel extends ViewModel {
    private final int maxExpressionLength = 30;
    public MutableLiveData<String> operation = new MutableLiveData<>();
    public MutableLiveData<String> result = new MutableLiveData<>();

    public CalculatorViewModel() {
        Clear();
    }

    public void Clear() {
        operation.setValue("");
        result.setValue("");
    }
    public void Append(String value) {
        if (operation.getValue().length() < maxExpressionLength) {
            String currentOperation = operation.getValue();
            operation.setValue(currentOperation + value);
        }
    }

    public void RemoveLast() {
        String currentOperation = operation.getValue();
        if (!currentOperation.isEmpty()) {
            operation.setValue(currentOperation.substring(0, currentOperation.length() - 1));
        }
    }

    public void Evaluate() {
        String currentOperation = operation.getValue();
        if (!currentOperation.isEmpty()) {
            try {
                double result_number = Calculator.Evaluate(currentOperation);
                if (result_number % 1 == 0) {
                    result.setValue(String.valueOf((int) result_number));
                } else {
                    result.setValue(String.valueOf(result_number));
                }
            } catch (Exception e) {
                result.setValue("Invalid input");
            }
        }
    }
}