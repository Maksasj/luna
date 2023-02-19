del main.o
del wasm.wasm
del *.o

clang -Wall -Wextra --stdlib=libc++ --target=wasm32 --sysroot=C:/msys64/mingw64/lib -I../shared -c ./main.cpp  ../shared/*.cpp ../shared/rendering/*.cpp ../shared/events/*.cpp

wasm-ld -m wasm32 --no-entry --export-all --allow-undefined -o wasm.wasm ./*.o