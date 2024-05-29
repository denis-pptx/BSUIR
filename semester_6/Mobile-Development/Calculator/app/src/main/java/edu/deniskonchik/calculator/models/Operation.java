package edu.deniskonchik.calculator.models;

public class Operation {
    private String operation;
    private String result;

    public Operation() {
        // Пустой конструктор требуется для работы с Firebase
    }

    public Operation(String operation, String result) {
        this.operation = operation;
        this.result = result;
    }

    public String getOperation() {
        return operation;
    }

    public String getResult() {
        return result;
    }
}
