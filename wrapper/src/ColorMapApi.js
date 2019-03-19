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
                buffer = this._module.malloc(colors);
                return this._createColorMap(buffer, colors.length);
            },
            cleanup: () => {
                this._module.free(buffer);
            },
        });
    }
}
