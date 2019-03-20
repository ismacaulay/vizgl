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

            const dataLoader = dataloader.loadBinary(element.data, Float32Array);

            return Promise.all([dataLoader]).then(loadedData => {
                const [data] = loadedData;

                const geometryId = vizgl
                    .geometryApi()
                    .createVoxelMesh2(tensor_u, tensor_v, tensor_w);
                const color = [19, 55, 130];
                const mappingId = vizgl.mappingApi().createVoxelMapping(data, color, geometryId);
                vizgl.modelApi().createModel(geometryId, mappingId);

                console.log(`Loaded ${this.id}`);
            });
        });
    }
}
export default BlockModelWithNaNs;
