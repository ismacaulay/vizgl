import { ModuleWrapper } from './ModuleWrapper';
import { GeometryApi } from './GeometryApi';
import { ColorMapApi } from './ColorMapApi';
import { MappingApi } from './MappingApi';
import { ModelApi } from './ModelApi';
import { PlotApi } from './PlotApi';
import { vizglInstance } from './ModuleLoader';
import { CoreApi } from './CoreApi';

class VizGL {
    constructor() {
        this._initalized = false;

        this._ready = new Promise(resolve => {
            vizglInstance().then(module => {
                this._initialize(module);
                resolve();
            });
        });
    }

    _initialize(module) {
        this._moduleWrapper = new ModuleWrapper(module);
        this._geometryApi = new GeometryApi(this._moduleWrapper);
        this._colorMapApi = new ColorMapApi(this._moduleWrapper);
        this._mappingApi = new MappingApi(this._moduleWrapper);
        this._modelApi = new ModelApi(this._moduleWrapper);
        this._plotApi = new PlotApi(this._moduleWrapper);
        this._core = new CoreApi(this._moduleWrapper);

        this._initalized = true;
    }

    _checkInitalized() {
        if (!this._initalized) {
            throw new Error('[VizGL] module not initilized yet');
        }
    }

    ready() {
        return this._ready;
    }

    reset() {
        if (this._initalized) {
            this._core.reset();
        }
    }

    geometryApi() {
        this._checkInitalized();
        return this._geometryApi;
    }

    colorMapApi() {
        this._checkInitalized();
        return this._colorMapApi;
    }

    mappingApi() {
        this._checkInitalized();
        return this._mappingApi;
    }

    modelApi() {
        this._checkInitalized();
        return this._modelApi;
    }

    plotApi() {
        this._checkInitalized();
        return this._plotApi;
    }
}
export default VizGL;
