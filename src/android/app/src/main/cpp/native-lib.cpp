#include <jni.h>
#include <stdlib.h>
#include <android/bitmap.h>

#include "shared/luna.hpp"

luna::Program program(800, 600);

extern "C" JNIEXPORT void JNICALL Java_com_luna_MainActivity_drawFromC(JNIEnv *env, jobject instance, jobject bmp) {
    AndroidBitmapInfo info;
    void *pixels;

    if (AndroidBitmap_getInfo(env, bmp, &info) < 0) return;
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) return;
    if (AndroidBitmap_lockPixels(env, bmp, &pixels) < 0) return;

    //program.Update();
    program.Render((u32*) pixels);

    AndroidBitmap_unlockPixels(env, bmp);
}

extern "C" JNIEXPORT void JNICALL Java_com_luna_MainActivity_lunaInit(JNIEnv *env, jobject instance, int width , int height) {
    program = luna::Program(width, height);
}