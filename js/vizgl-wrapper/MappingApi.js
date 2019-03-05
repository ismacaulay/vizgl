export class MappingApi {
    constructor(module) {
        this._module = module;

        this._createStaticMapping = this._module.wrap('createStaticMapping', 'number', [
            'number', // int8_t* color
        ]);

        this._createContinuousMapping = this._module.wrap('createContinuousMapping', 'number', [
            'number', // float* data
            'number', // unsigned int numData
            'number', // unsigned int gradientId
        ]);

        this._setContinuousMappingGradient = this._module.wrap(
            'setContinuousMappingGradient',
            null,
            [
                'number', // unsigned int mappingId
                'number', // unsigned int gradientId
            ],
        );
    }

    createStaticMapping(color) {
        let buffer;
        return this._module.execute({
            func: () => {
                const typedBuffer = new Uint8Array(color);
                buffer = this._module.malloc(typedBuffer);
                return this._createStaticMapping(buffer);
            },
            cleanup: () => {
                this._module.free(buffer);
            },
        });
    }

    createContinuosMapping(data, gradientId) {
        let buffer;
        return this._module.execute({
            func: () => {
                buffer = this._module.malloc(new Float32Array(data));
                return this._createContinuousMapping(buffer, data.length, gradientId);
            },
            cleanup: () => {
                this._module.free(buffer);
            },
        });
    }

    setContinuousMappingGradient(mappingId, gradientId) {
        return this._module.execute({
            func: () => {
                return this._setContinuousMappingGradient(mappingId, gradientId);
            },
        });
    }
}
