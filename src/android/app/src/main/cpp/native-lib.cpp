#include <jni.h>
#include <stdlib.h>
#include <android/bitmap.h>
#include <thread>

#include "shared/luna.h"

luna::Program program(800, 600);

extern "C" JNIEXPORT void JNICALL Java_com_luna_MainActivity_drawFromC(JNIEnv *env, jobject instance, jobject bmp) {
    AndroidBitmapInfo info;
    void *pixels;

    if (AndroidBitmap_getInfo(env, bmp, &info) < 0) return;
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) return;
    if (AndroidBitmap_lockPixels(env, bmp, &pixels) < 0) return;

    auto begin = std::chrono::high_resolution_clock::now();                                                                                                                                     

    program.Update();
    program.Render((u32*) pixels);

    auto end = std::chrono::high_resolution_clock::now();                                                                
    double durationMs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() / 1000000.0; 

    if(durationMs < 16.0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(16 - (u32)durationMs));
    }

    AndroidBitmap_unlockPixels(env, bmp);
}

extern "C" JNIEXPORT void JNICALL Java_com_luna_MainActivity_lunaInit(JNIEnv *env, jobject instance, int width , int height) {
    program = luna::Program(width, height);
}

extern "C" JNIEXPORT void JNICALL Java_com_luna_MainActivity_lunaPushTouchEvent(JNIEnv *env, jobject instance, int x0 , int y0) {
    luna::Event event;
    event.touchEvent = luna::TouchEvent{ luna::EventType::TOUCH_EVENT, x0, y0 };
    luna::EventManager::pushEvent(event);
}

extern "C" JNIEXPORT void JNICALL Java_com_luna_MainActivity_lunaPushTouchReleaseEvent(JNIEnv *env, jobject instance, int x0 , int y0) {
    luna::Event event;
    event.touchReleaseEvent = luna::TouchRreleaseEvent{ luna::EventType::TOUCH_RELEASE_EVENT, x0, y0 };
    luna::EventManager::pushEvent(event);
}

extern "C" JNIEXPORT void JNICALL Java_com_luna_MainActivity_lunaPushTouchMotionEvent(JNIEnv *env, jobject instance, int x0 , int y0) {
    luna::Event event;
    event.touchMotionEvent = luna::TouchMotionEvent{ luna::EventType::TOUCH_MOTION_EVENT, x0, y0 };
    luna::EventManager::pushEvent(event);
}