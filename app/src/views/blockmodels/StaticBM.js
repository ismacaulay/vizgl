import View from '../View';

function generateMappingData(dims) {
    const [x, y, z] = dims;
    const data = new Float32Array(x * y * z);
    for (let i = 0; i < x; i++) {
        for (let j = 0; j < y; j++) {
            for (let k = 0; k < z; k++) {
                const index = i * y * z + j * z + k;
                if (k % 2 === 0) {
                    data[index] = NaN;
                }
            }
        }
    }

    return data;
}

class StaticBM extends View {
    constructor(id) {
        super(id, 'Static BM');
    }

    load(vizgl) {
        return new Promise(resolve => {
            // const dims = [512, 512, 512];
            // const dims = [374, 263, 197];
            // const dims = [256, 256, 256];
            const dims = [15, 33, 57];
            console.log({ blockCount: dims[0] * dims[1] * dims[2] });

            const geometryId = vizgl.geometryApi().createVoxelMesh(dims);

            const color = [19, 55, 130];
            const data = generateMappingData(dims);
            const mappingId = vizgl.mappingApi().createVoxelMapping(data, color, geometryId);

            vizgl.modelApi().createModel(geometryId, mappingId);

            console.log(`Loaded ${this.id}`);
            resolve();
        });
    }
}
export default StaticBM;
