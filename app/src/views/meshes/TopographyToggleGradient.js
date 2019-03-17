import View from '../View';

import { json } from '../../utils';

class TopographyToggleGradient extends View {
    constructor(id) {
        super(id, 'Topography - Toggle Gradient');
    }

    load(vizgl) {
        const geometryLoader = json.load('res/geometry/topography.json');
        const dataLoader = json.load('res/data/topography.json');
        const crazyColorMapLoader = json.load('res/colormaps/joes-crazy-colors.json');
        const viridisColorMapLoader = json.load('res/colormaps/viridis.json');

        return Promise.all([
            geometryLoader,
            dataLoader,
            crazyColorMapLoader,
            viridisColorMapLoader,
        ]).then(loadedData => {
            const [geometry, data, crazyColorMap, viridisColorMap] = loadedData;

            const { vertices, triangles } = geometry;
            const { values } = data;

            const transformedData = triangles.map(vertexIdx => {
                return values[vertexIdx];
            });
            // console.log({ transformedData });
            const geometryId = vizgl.geometryApi().createMesh2(vertices, triangles);
            const crazyId = vizgl.colorMapApi().createColorMap(crazyColorMap.colors);
            const viridisId = vizgl.colorMapApi().createColorMap(viridisColorMap.colors);
            const mappingId = vizgl.mappingApi().createContinuosMapping(transformedData, crazyId);

            vizgl.modelApi().createModel(geometryId, mappingId);

            let index = 0;
            const colormaps = [crazyId, viridisId];
            const toggleColorMap = () => {
                index = (index + 1) % colormaps.length;
                vizgl.mappingApi().setContinuousMappingGradient(mappingId, colormaps[index]);
                setTimeout(toggleColorMap, 2500);
            };
            setTimeout(toggleColorMap, 2500);

            console.log(`Loaded ${this.id}`);
        });
    }
}
export default TopographyToggleGradient;
