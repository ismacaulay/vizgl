export class ModelApi {
    constructor(module) {
        this._module = module;

        this._createModel = this._module.wrap('createModel', 'number', [
            'number', // unsigned int geometryId
            'number', // unsigned int mappingId
        ]);
    }

    createModel(geometryId, mappingId) {
        return this._module.execute({
            func: () => {
                return this._createModel(geometryId, mappingId);
            },
        });
    }
}
