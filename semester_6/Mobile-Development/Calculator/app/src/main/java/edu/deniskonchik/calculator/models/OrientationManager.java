package edu.deniskonchik.calculator.models;

import android.content.Context;
import android.content.res.ColorStateList;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.View;
import android.widget.GridLayout;

import androidx.appcompat.widget.AppCompatButton;

public class OrientationManager implements SensorEventListener {
    private final SensorManager sensorManager;
    private final Sensor accelerometer;
    private final Sensor magnetometer;

    private final float[] accelerometerData = new float[3];
    private final float[] magnetometerData = new float[3];
    private final float[] rotationMatrix = new float[9];
    private final float[] orientationAngles = new float[3];

    private GridLayout buttonGrid;

    public OrientationManager(Context context, GridLayout buttonGrid) {
        this.buttonGrid = buttonGrid;

        sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
        if (sensorManager != null) {
            accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
            magnetometer = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        } else {
            throw new UnsupportedOperationException("Sensor service not available");
        }
    }

    public void startListening() {
        if (accelerometer != null && magnetometer != null) {
            sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_NORMAL);
            sensorManager.registerListener(this, magnetometer, SensorManager.SENSOR_DELAY_NORMAL);
        } else {
            throw new UnsupportedOperationException("Accelerometer or magnetometer not available");
        }
    }

    public void stopListening() {
        sensorManager.unregisterListener(this);
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor == accelerometer) {
            System.arraycopy(event.values, 0, accelerometerData, 0, accelerometerData.length);
        } else if (event.sensor == magnetometer) {
            System.arraycopy(event.values, 0, magnetometerData, 0, magnetometerData.length);
        }

        updateOrientationAngles();
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // Not used
    }

    private void updateOrientationAngles() {
        SensorManager.getRotationMatrix(rotationMatrix, null, accelerometerData, magnetometerData);
        SensorManager.getOrientation(rotationMatrix, orientationAngles);

        float azimuthDegrees = (float) Math.toDegrees(orientationAngles[0]);
        float pitchDegrees = (float) Math.toDegrees(orientationAngles[1]);
        float rollDegrees = (float) Math.toDegrees(orientationAngles[2]);

        int r = Math.round(Math.abs(azimuthDegrees) / 180 * 255) % 256;
        int g = Math.round(Math.abs(pitchDegrees) / 90 * 255) % 256;
        int b = Math.round(Math.abs(rollDegrees) / 180 * 255) % 256;

        int color = Color.rgb(r, g, b);

        applyBackgroundColor(color);
    }

    private void applyBackgroundColor(int color) {
        ColorStateList colorStateList = ColorStateList.valueOf(color);

        for (int i = 0; i < buttonGrid.getChildCount(); i++) {
            View view = buttonGrid.getChildAt(i);
            if (view instanceof AppCompatButton) {
                AppCompatButton button = (AppCompatButton) view;
                button.setBackgroundTintList(colorStateList);
            }
        }
    }
}
