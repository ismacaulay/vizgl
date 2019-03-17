import VizGLModule from '../../src/.build/wasm/vizgl.js';

let _instance;
export function vizglInstance() {
    if (_instance === undefined) {
        const moduleOptions = {
            canvas: document.getElementById('canvas'),
        };
        _instance = new VizGLModule(moduleOptions);
    }
    return _instance;
}
