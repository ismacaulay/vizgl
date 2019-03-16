import json from '../utils/json';

class Cube {
    constructor(vizgl) {
        json.load('res/geometry/cube.json').then(geometry => {
            const { vertices } = geometry;

            console.log({ geometry });

            const geometryId = vizgl.geometryApi().createMesh(vertices);

            const color = [116, 191, 165];
            const mappingId = vizgl.mappingApi().createStaticMapping(color);

            const modelId = vizgl.modelApi().createModel(geometryId, mappingId);
            console.log({ geometryId, mappingId, modelId });
        });
    }
}
export default Cube;
