package edu.deniskonchik.calculator.models;

import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class OperationManager {
    private DatabaseReference operationsRef;

    public OperationManager() {
        // Получаем ссылку на узел операций в Firebase
        operationsRef = FirebaseDatabase.getInstance().getReference().child("operations");
    }

    public void saveOperation(String operation, String result) {
        String operationId = operationsRef.push().getKey();

        Operation operationObj = new Operation(operation, result);

        if (operationId != null) {
            operationsRef.child(operationId).setValue(operationObj);
        }
    }

    public void loadLastOperation(CalculatorViewModel viewModel) {
        operationsRef.limitToLast(1).addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                for (DataSnapshot snapshot : dataSnapshot.getChildren()) {
                    Operation operation = snapshot.getValue(Operation.class);
                    if (operation != null) {
                        viewModel.operation.setValue(operation.getOperation());
                        viewModel.result.setValue(operation.getResult());
                    }
                }
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {

            }
        });
    }
}