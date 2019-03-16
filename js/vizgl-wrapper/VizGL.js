import { ModuleWrapper } from './ModuleWrapper';
import { GeometryApi } from './GeometryApi';
import { ColorMapApi } from './ColorMapApi';
import { MappingApi } from './MappingApi';
import { ModelApi } from './ModelApi';

class VizGL {
    constructor() {
        this._initalized = false;
    }

    initialize(module) {
        this._moduleWrapper = new ModuleWrapper(module);
        this._geometryApi = new GeometryApi(this._moduleWrapper);
        this._colorMapApi = new ColorMapApi(this._moduleWrapper);
        this._mappingApi = new MappingApi(this._moduleWrapper);
        this._modelApi = new ModelApi(this._moduleWrapper);

        this._initalized = true;
    }

    isInitalized() {
        return this._initalized;
    }

    geometryApi() {
        return this._geometryApi;
    }

    colorMapApi() {
        return this._colorMapApi;
    }

    mappingApi() {
        return this._mappingApi;
    }

    modelApi() {
        return this._modelApi;
    }
}
export default VizGL;
