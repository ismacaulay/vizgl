import * as dat from 'dat.gui';
import PlotControls from './PlotControls';

class Controls {
    constructor(vizgl) {
        this.gui = new dat.GUI({ autoPlace: false });
        const controlsElement = document.getElementById('controls');
        controlsElement.appendChild(this.gui.domElement);

        const controlsFolder = this.gui.addFolder('Controls');
        this._plotControls = new PlotControls(controlsFolder, vizgl.plotApi());
    }

    reset() {
        this._plotControls.reset();
    }
}
export default Controls;
