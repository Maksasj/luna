del main.o
del wasm.wasm
del *.o

clang -Wall -Wextra --target=wasm32-wasi --sysroot=C:/wasi-sdk-19.0/share/wasi-sysroot -I../shared -c ./main.cpp  ../shared/*.cpp ../shared/rendering/*.cpp ../shared/events/*.cpp

wasm-ld -m wasm32 --no-entry --export-all --allow-undefined -o wasm.wasm ./*.o