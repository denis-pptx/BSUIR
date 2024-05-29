package edu.deniskonchik.calculator.models;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;

import edu.deniskonchik.calculator.R;
import edu.deniskonchik.calculator.activities.MainActivity;

public class LightManager implements SensorEventListener {
    private final SensorManager sensorManager;
    private final Sensor lightSensor;

    private final Context context;

    public LightManager(Context context) {
        this.context = context;

        sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
        if (sensorManager != null) {
            lightSensor = sensorManager.getDefaultSensor(Sensor.TYPE_LIGHT);
        } else {
            throw new UnsupportedOperationException("Sensor service not available");
        }
    }

    public void startListening() {
        if (lightSensor != null) {
            sensorManager.registerListener(this, lightSensor, SensorManager.SENSOR_DELAY_NORMAL);
        } else {
            throw new UnsupportedOperationException("Light sensor not available");
        }
    }

    public void stopListening() {
        sensorManager.unregisterListener(this);
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        float lightValue = event.values[0];
        //Log.d("Light", "Light value: " + lightValue);

        if (lightValue > 1000) {
            ((MainActivity) context).onButtonClick(((MainActivity) context).findViewById(R.id.b_equals));
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // Not used
    }
}