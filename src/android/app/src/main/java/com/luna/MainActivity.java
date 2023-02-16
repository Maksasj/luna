package com.luna;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.os.Bundle;
import android.os.Debug;
import android.os.SystemClock;
import android.util.DisplayMetrics;
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
    private int height;
    private int width;

    static {
        System.loadLibrary("luna");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        DisplayMetrics displayMetrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
        height = displayMetrics.heightPixels;
        width = displayMetrics.widthPixels;

        lunaInit(width, height);

        fMainView = new SkiaDrawView(this);
        setContentView(fMainView);

        new Thread(() -> {
            while(true) {
                fMainView.invalidate();

                try {
                    Thread.sleep(1);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }

            }
        }).start();
    }

    private class SkiaDrawView extends View {
        Bitmap fSkiaBitmap;
        public SkiaDrawView(Context ctx) {
            super(ctx);
            fSkiaBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        }

        @Override
        protected void onDraw(Canvas canvas) {
            long startTime = System.nanoTime();

            drawFromC(fSkiaBitmap);

            long endTime = System.nanoTime();
            long duration = (endTime - startTime);  //divide by 1000000 to get milliseconds.
            Log.i("INFO", String.valueOf((duration / 1000000.0)));

            canvas.drawBitmap(fSkiaBitmap, 0, 0, null);
        }
    }

    private native void drawFromC(Bitmap image);
    private native void lunaInit(int width, int height);
}