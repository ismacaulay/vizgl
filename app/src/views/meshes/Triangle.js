import View from '../View';

import { json } from '../../utils';

class Triangle extends View {
    constructor(id) {
        super(id, 'Triangle');
    }

    load(vizgl) {
        const geometryLoader = json.load('res/geometry/triangle.json');
        const dataLoader = json.load('res/data/triangle.json');
        const colormapLoader = json.load('res/colormaps/viridis.json');

        return Promise.all([geometryLoader, dataLoader, colormapLoader]).then(loadedData => {
            const [geometry, data, colormap] = loadedData;
            const { vertices } = geometry;
            const { values } = data;
            const { colors } = colormap;

            const geometryId = vizgl.geometryApi().createMesh(vertices);
            const colorMapId = vizgl.colorMapApi().createColorMap(colors);
            const mappingId = vizgl.mappingApi().createContinuosMapping(values, colorMapId);

            vizgl.modelApi().createModel(geometryId, mappingId);

            console.log(`Loaded ${this.id}`);
        });
    }
}
export default Triangle;
