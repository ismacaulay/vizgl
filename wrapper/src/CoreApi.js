export class CoreApi {
    constructor(module) {
        this._module = module;

        this._reset = this._module.wrap('reset', null, null);
    }

    reset() {
        this._reset();
    }
}
