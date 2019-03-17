import View from '../View';

import { json } from '../../utils';

class Topography extends View {
    constructor(id) {
        super(id, 'Topography');
    }

    load(vizgl) {
        const geometryLoader = json.load('res/geometry/topography.json');
        const dataLoader = json.load('res/data/topography.json');
        const colormapLoader = json.load('res/colormaps/joes-crazy-colors.json');

        return Promise.all([geometryLoader, dataLoader, colormapLoader]).then(loadedData => {
            const [geometry, data, colormap] = loadedData;
            const { vertices, triangles } = geometry;
            const { values } = data;
            const { colors } = colormap;
            const transformedData = triangles.map(vertexIdx => {
                return values[vertexIdx];
            });
            const geometryId = vizgl.geometryApi().createMesh2(vertices, triangles);
            const colorMapId = vizgl.colorMapApi().createColorMap(colors);
            const mappingId = vizgl
                .mappingApi()
                .createContinuosMapping(transformedData, colorMapId);
            const modelId = vizgl.modelApi().createModel(geometryId, mappingId);

            console.log({ modelId, geometryId, mappingId, colorMapId });
            console.log(`Loaded ${this.id}`);
        });
    }
}
export default Topography;
