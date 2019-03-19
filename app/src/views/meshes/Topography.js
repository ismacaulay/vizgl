import View from '../View';

class Topography extends View {
    constructor(id) {
        super(id, 'Topography');
    }

    load(vizgl, dataloader) {
        return dataloader.loadJson('manifests/topography.json').then(manifest => {
            const { elements } = manifest;
            const [element] = elements;

            const vertLoader = dataloader.loadBinary(element.vertices, Float32Array);
            const triLoader = dataloader.loadBinary(element.triangles, Uint32Array);
            const dataLoader = dataloader.loadBinary(element.data, Float32Array);
            const colormapLoader = dataloader.loadBinary(element.colormap, Uint8Array);

            return Promise.all([vertLoader, triLoader, dataLoader, colormapLoader]).then(
                loadedData => {
                    const [vertices, triangles, data, colors] = loadedData;

                    const transformedData = new Float32Array(triangles.length);
                    triangles.forEach((vertexIdx, i) => {
                        transformedData[i] = data[vertexIdx];
                    });

                    const geometryId = vizgl.geometryApi().createMesh2(vertices, triangles);
                    const colorMapId = vizgl.colorMapApi().createColorMap(colors);
                    const mappingId = vizgl
                        .mappingApi()
                        .createContinuosMapping(transformedData, colorMapId);
                    vizgl.modelApi().createModel(geometryId, mappingId);

                    console.log(`Loaded ${this.id}`);
                },
            );
        });
    }
}
export default Topography;
