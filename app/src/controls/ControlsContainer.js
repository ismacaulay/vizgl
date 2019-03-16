import * as dat from 'dat.gui';
import PlotControls from './PlotControls';

class ControlsContainer {
    constructor(vizgl) {
        this.gui = new dat.GUI({ autoPlace: false });
        const controlsElement = document.getElementById('controls');
        controlsElement.appendChild(this.gui.domElement);

        const controlsFolder = this.gui.addFolder('Controls');
        this.plotControls = new PlotControls(controlsFolder, vizgl.plotApi());
    }
}
export default ControlsContainer;
