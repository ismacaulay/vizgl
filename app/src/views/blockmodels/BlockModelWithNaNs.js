import View from '../View';

class BlockModelWithNaNs extends View {
    constructor(id) {
        super(id, 'Block Model with NaNs');
    }

    load(vizgl, dataloader) {
        return new Promise(resolve => {
            return dataloader.loadJson('manifests/blockmodel-with-nans.json').then(manifest => {
                const { elements } = manifest;
                const [element] = elements;

                const { tensor_u, tensor_v, tensor_w } = element;

                const dataLoader = dataloader.loadBinary(element.data, Float32Array);
                const gradientLoader = dataloader.loadBinary(element.gradient, Uint8Array);

                return Promise.all([dataLoader, gradientLoader]).then(loadedData => {
                    const [data, gradient] = loadedData;

                    const geometryId = vizgl
                        .geometryApi()
                        .createVoxelMesh2(tensor_u, tensor_v, tensor_w);
                    const gradientId = vizgl.colorMapApi().createColorMap(gradient);

                    const mappingId = vizgl
                        .mappingApi()
                        .createVoxelContinuousMapping(data, gradientId, geometryId);
                    vizgl.modelApi().createModel(geometryId, mappingId);

                    console.log(`Loaded ${this.id}`);
                    resolve();
                });
            });
        });
    }
}
export default BlockModelWithNaNs;
