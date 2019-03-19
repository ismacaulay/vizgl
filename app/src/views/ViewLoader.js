import { getViewForId } from './views';
import { VizGL } from '@vizgl/wrapper';
import { Controls } from '../controls';
import { DataLoader } from '../data';

export class ViewLoader {
    constructor() {
        this._isLoading = false;
        this._vizgl = new VizGL();
        this._dataLoader = DataLoader.create();
        this._vizgl.ready().then(() => {
            this._controls = new Controls(this._vizgl);
        });
    }

    load(viewId) {
        this._isLoading = true;

        return new Promise(resolve => {
            const view = getViewForId(viewId);
            this._vizgl.ready().then(() => {
                this._vizgl.reset();
                this._controls.reset();

                view.load(this._vizgl, this._dataLoader).then(() => {
                    this._isLoading = false;
                    resolve();
                });
            });
        });
    }

    isLoading() {
        return this._isLoading;
    }
}
