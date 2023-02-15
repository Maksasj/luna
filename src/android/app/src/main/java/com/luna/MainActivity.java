package com.luna;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.os.Bundle;
import android.os.Debug;
import android.os.SystemClock;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.luna.databinding.ActivityMainBinding;

import java.io.Console;
import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.Logger;

public class MainActivity extends AppCompatActivity {
    private SkiaDrawView fMainView;

    // Used to load the 'luna' library on application startup.
    static {
        System.loadLibrary("luna");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        //binding = ActivityMainBinding.inflate(getLayoutInflater());
        //setContentView(binding.getRoot());

        fMainView = new SkiaDrawView(this);
        setContentView(fMainView);

        Timer fAnimationTimer = new Timer();
        fAnimationTimer.schedule(new TimerTask() {
            public void run()
            {
                // This will request an update of the SkiaDrawView, even from other threads
                fMainView.postInvalidate();
            }
        }, 0, 5); // 0 means no delay before the timer starts; 5 means repeat every 5 milliseconds
    }

    private class SkiaDrawView extends View {
        Bitmap fSkiaBitmap;
        public SkiaDrawView(Context ctx) {
            super(ctx);
            fSkiaBitmap = Bitmap.createBitmap(800, 600, Bitmap.Config.ARGB_8888);
        }

        @Override
        protected void onDraw(Canvas canvas) {
            // Call into our C++ code that renders to the bitmap using Skia
            drawFromC(fSkiaBitmap);
            Log.d("TEST", "Drawing on canvas");
            // Present the bitmap on the screen
            canvas.drawBitmap(fSkiaBitmap, 0, 0, null);
        }
    }

    private native void drawFromC(Bitmap image);
}