import { isTypedArray } from './utils';

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

        this._createVoxelMapping = this._module.wrap('createVoxelMapping', 'number', [
            'number', // float* data
            'number', // unsigned int numData
            'number', // int8_t* color
            'number', // unsigned int geometryId
        ]);

        this._createVoxelContinuousMapping = this._module.wrap(
            'createVoxelContinuousMapping',
            'number',
            [
                'number', // float* data
                'number', // unsigned int numData
                'number', // unsigned int gradientId
                'number', // unsigned int geometryId
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

    createVoxelMapping(data, color, geometryId) {
        let dataBuffer;
        let colorBuffer;

        return this._module.execute({
            func: () => {
                const dataArray = isTypedArray(data) ? data : new Float32Array(data);
                const colorArray = isTypedArray(color) ? color : new Uint8Array(color);
                dataBuffer = this._module.malloc(dataArray);
                colorBuffer = this._module.malloc(colorArray);
                return this._createVoxelMapping(
                    dataBuffer,
                    dataArray.length,
                    colorBuffer,
                    geometryId,
                );
            },
            cleanup: () => {
                this._module.free(dataBuffer);
                this._module.free(colorBuffer);
            },
        });
    }

    createVoxelContinuousMapping(data, gradientId, geometryId) {
        let dataBuffer;
        return this._module.execute({
            func: () => {
                const dataArray = isTypedArray(data) ? data : new Float32Array(data);
                dataBuffer = this._module.malloc(dataArray);
                return this._createVoxelContinuousMapping(
                    dataBuffer,
                    dataArray.length,
                    gradientId,
                    geometryId,
                );
            },
            cleanup: () => {
                this._module.free(dataBuffer);
            },
        });
    }
}
