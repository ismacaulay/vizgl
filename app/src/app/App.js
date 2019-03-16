import { Cube, Topography, LotsOfMeshes } from '../meshes';
import ControlsContainer from '../controls/ControlsContainer';

class App {
    constructor(vizgl) {
        this.vizgl = vizgl;
    }

    run() {
        if (!this.vizgl.isInitalized()) {
            throw Error('VizGL not initialized');
        }

        this.controls = new ControlsContainer(this.vizgl);
        this.view = new Topography(this.vizgl);
    }
}
export default App;
