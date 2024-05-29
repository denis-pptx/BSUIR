package edu.deniskonchik.calculator.activities;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.GridLayout;
import android.widget.Switch;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;
import androidx.appcompat.widget.AppCompatButton;
import androidx.lifecycle.ViewModelProvider;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import edu.deniskonchik.calculator.R;
import edu.deniskonchik.calculator.models.CalculatorViewModel;
import edu.deniskonchik.calculator.models.DarkModeManager;
import edu.deniskonchik.calculator.models.LightManager;
import edu.deniskonchik.calculator.models.OperationManager;
import edu.deniskonchik.calculator.models.OrientationManager;

public class MainActivity extends AppCompatActivity {
    private Switch switcher;
    private TextView resultField;
    private TextView operationField;
    private CalculatorViewModel viewModel;

    private OrientationManager orientationManager;
    private LightManager lightManager;
    private DarkModeManager darkModeManager;
    private OperationManager operationManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        resultField = findViewById(R.id.resultField);
        operationField = findViewById(R.id.operationField);

        viewModel = new ViewModelProvider(this).get(CalculatorViewModel.class);
        viewModel.operation.observe(this, operation -> {
            operationField.setText(operation);
        });
        viewModel.result.observe(this, result -> {
            resultField.setText(result);
        });

        GridLayout gridLayout = findViewById(R.id.buttonGrid);
        for (int i = 0; i < gridLayout.getChildCount(); i++) {
            View view = gridLayout.getChildAt(i);
            if (view instanceof AppCompatButton) {
                AppCompatButton button = (AppCompatButton) view;
                button.setOnClickListener((View v) -> onButtonClick(button));
            }
        }

        orientationManager = new OrientationManager(this, gridLayout);
        orientationManager.startListening();

        lightManager = new LightManager(this);
        lightManager.startListening();

        switcher = findViewById(R.id.switcher);

        if (switcher != null) {
            darkModeManager = new DarkModeManager(switcher);
        }

        operationManager = new OperationManager();

    }

    public void onButtonClick(AppCompatButton button){
        String text = button.getText().toString();

        switch (text) {
            case "sqrt":
            case "log2":
            case "log":
            case "sin":
            case "cos":
                viewModel.Append(text + "(");
                break;
            case "x^y":
                viewModel.Append("^");
                break;
            case "AC":
                viewModel.Clear();
                break;
            case "back":
                viewModel.RemoveLast();
                break;
            case "=":
                viewModel.Evaluate();
                operationManager.saveOperation(operationField.getText().toString(), resultField.getText().toString());
                break;
            default:
                viewModel.Append(text);
                break;
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        outState.putString("result", resultField.getText().toString());
        outState.putString("operation", operationField.getText().toString());
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        String result = savedInstanceState.getString("result");
        String operation = savedInstanceState.getString("operation");
        resultField.setText(result);
        operationField.setText(operation);
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        orientationManager.stopListening();
        lightManager.stopListening();
    }

    public void onLoadLastClick(View view) {
        operationManager.loadLastOperation(viewModel);
    }
}