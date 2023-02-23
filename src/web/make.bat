del main.o
del wasm.wasm
del *.o

clang -Wall -Wextra --target=wasm32-wasi --sysroot=C:/wasi-sdk-19.0/share/wasi-sysroot -mbulk-memory -I../shared -c ./main.cpp ../shared/*.cpp ../shared/rendering/*.cpp ../shared/events/*.cpp

wasm-ld -m wasm32 -LC:/wasi-sdk-19.0/share/wasi-sysroot/lib/wasm32-wasi --no-entry --export-all -o wasm.wasm ./*.o