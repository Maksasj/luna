let app = document.getElementById("app");
app.width = 800;
app.height = 600;
const ctx = app.getContext("2d");

let w = null;

function make_environment(...envs) {
    return new Proxy(envs, {
        get(target, prop, receiver) {
            for (let env of envs) {
                if (env.hasOwnProperty(prop)) {
                    return env[prop];
                }
            }
            return (...args) => {console.error("NOT IMPLEMENTED: "+prop, args)}
        }
    });
}

WebAssembly.instantiateStreaming(fetch('./wasm.wasm'), {
    "env": make_environment()
}).then(w0 => {
    w = w0;
    
    console.log(w.instance.exports);

    const buffer = w.instance.exports.memory.buffer;
    const pixels = w.instance.exports.pixels;
    
    w.instance.exports._Z6renderv();
    
    console.log(pixels);

    const image = new ImageData(new Uint8ClampedArray(buffer, pixels, app.width*app.height*4), app.width);
    
    console.log(image);

    
    ctx.putImageData(image, 0, 0);
})

console.log(ctx);