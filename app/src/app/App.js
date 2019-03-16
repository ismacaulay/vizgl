import { Cube, Topography, LotsOfMeshes } from '../meshes';

class App {
    constructor(vizgl) {
        this.vizgl = vizgl;
    }

    run() {
        if (!this.vizgl.isInitalized()) {
            throw Error('VizGL not initialized');
        }

        this.view = new LotsOfMeshes(this.vizgl);
    }
}
export default App;
