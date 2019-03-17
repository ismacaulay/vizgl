import View from '../View';
import { json } from '../../utils';

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

class BlockModelWithNaNs extends View {
    constructor(id) {
        super(id, 'Block Model with NaNs');
    }

    load(vizgl) {
        return json.load('res/large-data/blockmodel-with-nans.json').then(data => {
            const { elements } = data;
            const [blockModel] = elements;

            const { data: bmDataList } = blockModel;
            const [bmData] = bmDataList;
            const {
                array: { data: dataArray },
            } = bmData;
            const processedDataArray = dataArray.map(value => (value === null ? NaN : value));
            const { tensor_u, tensor_v, tensor_w } = blockModel;

            const dims = [tensor_u.length, tensor_v.length, tensor_w.length];
            console.log({ dims, blockCount: dims[0] * dims[1] * dims[2] });
            const geometryId = vizgl.geometryApi().createVoxelMesh(dims);

            const color = [19, 55, 130];
            const mappingId = vizgl
                .mappingApi()
                .createVoxelMapping(processedDataArray, color, geometryId);

            vizgl.modelApi().createModel(geometryId, mappingId);
        });
    }
}
export default BlockModelWithNaNs;
