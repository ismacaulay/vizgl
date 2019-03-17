import { flattenArrayToTypedArray } from './utils';

export class PlotApi {
    constructor(module) {
        this._module = module;

        this._setPlotRotation = this._module.wrap('setPlotRotation', null, [
            'number', // float* rotation
        ]);
    }

    setRotation(rotation) {
        let buffer;
        return this._module.execute({
            func: () => {
                buffer = this._module.malloc(new Float32Array(rotation));
                this._setPlotRotation(buffer);
            },
            cleanup: () => {
                this._module.free(buffer);
            },
        });
    }
}
