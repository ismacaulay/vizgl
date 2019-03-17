import View from '../View';

import { json } from '../../utils';

class Cube extends View {
    constructor(id) {
        super(id, 'Cube');
    }

    load(vizgl) {
        return json.load('res/geometry/cube.json').then(geometry => {
            const { vertices } = geometry;
            const geometryId = vizgl.geometryApi().createMesh(vertices);
            const color = [116, 191, 165];
            const mappingId = vizgl.mappingApi().createStaticMapping(color);
            const modelId = vizgl.modelApi().createModel(geometryId, mappingId);

            console.log({ geometryId, mappingId, modelId });
            console.log(`Loaded ${this.id}`);
        });
    }
}
export default Cube;
