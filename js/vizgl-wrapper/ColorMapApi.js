import { flattenArrayToTypedArray } from './utils';

export class ColorMapApi {
    constructor(module) {
        this._module = module;

        this._createColorMap = this._module.wrap('createColorMap', 'number', [
            'number', // int8_t* colors
            'number', // int numColors
        ]);
    }

    createColorMap(colors) {
        let buffer;
        return this._module.execute({
            func: () => {
                const colorsBuffer = flattenArrayToTypedArray(colors, Uint8Array);
                buffer = this._module.malloc(colorsBuffer);
                return this._createColorMap(buffer, colorsBuffer.length);
            },
            cleanup: () => {
                this._module.free(buffer);
            },
        });
    }
}
