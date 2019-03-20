import View from '../View';

function generateTensor(length, start, inc) {
    let tensor = [];
    let value = start === 0.0 ? 0.1 : start;
    for (let i = 0; i < length; i++) {
        tensor.push(value);
        value += inc;
    }
    return tensor;
}

class StaticTensorBM extends View {
    constructor(id) {
        super(id, 'Static Tensor BM');
    }

    load(vizgl) {
        return new Promise(resolve => {
            const tensor_u = generateTensor(12, 0.2, 0.1);
            const tensor_v = generateTensor(4, 0.0, 1.0);
            const tensor_w = generateTensor(16, 0.25, 0.25);

            const geometryId = vizgl.geometryApi().createVoxelMesh2(tensor_u, tensor_v, tensor_w);

            const color = [19, 55, 130];
            const data = new Float32Array(tensor_u.length * tensor_v.length * tensor_w.length);
            const mappingId = vizgl.mappingApi().createVoxelMapping(data, color, geometryId);

            vizgl.modelApi().createModel(geometryId, mappingId);

            console.log(`Loaded ${this.id}`);
            resolve();
        });
    }
}
export default StaticTensorBM;
