import { getViewForId } from './views';
import { VizGL } from '@vizgl/wrapper';
import ControlsContainer from '../controls/ControlsContainer';

export class ViewLoader {
    constructor() {
        this._isLoading = false;
        this._vizgl = new VizGL();
        this._vizgl.ready().then(() => {
            this._controls = new ControlsContainer(this._vizgl);
        });
    }

    load(viewId) {
        this._isLoading = true;

        return new Promise(resolve => {
            const view = getViewForId(viewId);
            this._vizgl.ready().then(() => {
                this._vizgl.reset();
                view.load(this._vizgl).then(() => {
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
