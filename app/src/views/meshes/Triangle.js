import View from '../View';

class Triangle extends View {
    constructor(id) {
        super(id, 'Triangle');
    }

    load(vizgl, dataloader) {
        return dataloader.loadJson('manifests/triangle.json').then(manifest => {
            const { elements } = manifest;
            const [element] = elements;

            const vertLoader = dataloader.loadBinary(element.vertices, Float32Array);
            const dataLoader = dataloader.loadBinary(element.data, Float32Array);
            const colormapLoader = dataloader.loadBinary(element.colormap, Uint8Array);

            return Promise.all([vertLoader, dataLoader, colormapLoader]).then(loadedData => {
                const [vertices, data, colors] = loadedData;

                const geometryId = vizgl.geometryApi().createMesh(vertices);
                const colorMapId = vizgl.colorMapApi().createColorMap(colors);
                const mappingId = vizgl.mappingApi().createContinuosMapping(data, colorMapId);

                vizgl.modelApi().createModel(geometryId, mappingId);

                console.log(`Loaded ${this.id}`);
            });
        });
    }
}
export default Triangle;
