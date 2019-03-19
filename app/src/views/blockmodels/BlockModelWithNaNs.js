import View from '../View';

class BlockModelWithNaNs extends View {
    constructor(id) {
        super(id, 'Block Model with NaNs');
    }

    load(vizgl, dataloader) {
        return dataloader.loadJson('manifests/blockmodel-with-nans.json').then(manifest => {
            const { elements } = manifest;
            const [element] = elements;

            const { tensor_u, tensor_v, tensor_w } = element;
            const dims = [tensor_u.length, tensor_v.length, tensor_w.length];

            const dataLoader = dataloader.loadBinary(element.data, Float32Array);
            // const colormapLoader = dataloader.loadBinary(element.gradient, Uint8Array);

            return Promise.all([dataLoader]).then(loadedData => {
                const [data] = loadedData;

                const geometryId = vizgl.geometryApi().createVoxelMesh(dims);
                const color = [19, 55, 130];
                const mappingId = vizgl.mappingApi().createVoxelMapping(data, color, geometryId);
                vizgl.modelApi().createModel(geometryId, mappingId);

                console.log(`Loaded ${this.id}`);
            });
        });
    }
}
export default BlockModelWithNaNs;
