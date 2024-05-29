package edu.deniskonchik.calculator.activities;


import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;
import androidx.biometric.BiometricPrompt;
import androidx.core.content.ContextCompat;


import edu.deniskonchik.calculator.R;
import edu.deniskonchik.calculator.utils.BiometricUtils;
import edu.deniskonchik.calculator.utils.PinEncryptionUtils;
import edu.deniskonchik.calculator.databinding.ActivityAuthBinding;
import edu.deniskonchik.calculator.utils.SetPinUtil;

import java.util.concurrent.Executor;

public class AuthActivity extends AppCompatActivity {

    ActivityAuthBinding binding;
    Executor executor;
    BiometricPrompt biometricPrompt;
    BiometricPrompt.PromptInfo promptInfo;
    public PinEncryptionUtils pinEncryptionUtils;
    TextView pinInputTextView;
    final int MAX_PIN_LENGTH = 6;
    public String storedPin;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityAuthBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        pinInputTextView = findViewById(R.id.pinInputTextView);
        executor = ContextCompat.getMainExecutor(this);
        pinEncryptionUtils = new PinEncryptionUtils();

        loadStoredPin();
    }

    public void biometricAuth(View view) {
        BiometricUtils.biometricAuth(this);
    }

    private void showBiometricConfirmationDialog(String newPin) {
        BiometricUtils.showBiometricConfirmationDialog(this, newPin);
    }

    public void showPin(View view) {
        BiometricUtils.showPin(this);
    }

    private void loadStoredPin() {
        storedPin = pinEncryptionUtils.loadPinFromSecureStorage(this);
    }

    public void appendDigit(View view) {
        SetPinUtil.appendDigit(this, pinInputTextView, MAX_PIN_LENGTH, (TextView) view);
    }

    public void deleteDigit(View view) {
        SetPinUtil.deleteDigitPin(pinInputTextView);
    }

    public void deleteAll(View view) {
        SetPinUtil.deleteAllPin(pinInputTextView);
    }

    public void setPin(View view) {
        SetPinUtil.setPin(this, pinInputTextView, storedPin, MAX_PIN_LENGTH);
    }

    public void login(View view) {
        SetPinUtil.login(this, pinInputTextView, storedPin, MAX_PIN_LENGTH);
    }
}
