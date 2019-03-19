import View from '../View';

class TopographyToggleGradient extends View {
    constructor(id) {
        super(id, 'Topography - Toggle Gradient');
    }

    load(vizgl, dataloader) {
        return dataloader.loadJson('manifests/topography.json').then(manifest => {
            const { elements } = manifest;
            const [element] = elements;

            const vertLoader = dataloader.loadBinary(element.vertices, Float32Array);
            const triLoader = dataloader.loadBinary(element.triangles, Uint32Array);
            const dataLoader = dataloader.loadBinary(element.data, Float32Array);
            const crazyColorMapLoader = dataloader.loadBinary(
                'colormaps/joes-crazy-colors.bin',
                Uint8Array,
            );
            const viridisColorMapLoader = dataloader.loadBinary(
                'colormaps/viridis.bin',
                Uint8Array,
            );

            return Promise.all([
                vertLoader,
                triLoader,
                dataLoader,
                crazyColorMapLoader,
                viridisColorMapLoader,
            ]).then(loadedData => {
                const [vertices, triangles, data, crazyColorMap, viridisColorMap] = loadedData;

                const transformedData = new Float32Array(triangles.length);
                triangles.forEach((vertexIdx, i) => {
                    transformedData[i] = data[vertexIdx];
                });

                const geometryId = vizgl.geometryApi().createMesh2(vertices, triangles);
                const crazyId = vizgl.colorMapApi().createColorMap(crazyColorMap);
                const viridisId = vizgl.colorMapApi().createColorMap(viridisColorMap);
                const mappingId = vizgl
                    .mappingApi()
                    .createContinuosMapping(transformedData, crazyId);

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
        });
    }
}
export default TopographyToggleGradient;
