import json from '../utils/json';
import array from '../utils/array';
import color from '../utils/color';

class LotsOfMeshes {
    constructor(vizgl) {
        json.load('res/large-data/lots-of-meshes.json').then(meshes => {
            console.log('Processing...');

            let totalTris = 0;
            for (let i = 0; i < 100; i++) {
                const {
                    vertices,
                    triangles,
                    color: { value: hexColor },
                } = meshes[i];
                const verts = array.flattenToTypedArray(vertices, Float32Array);
                const tris = array.flattenToTypedArray(triangles, Uint32Array);

                const geometryId = vizgl.geometryApi().createMesh2(verts, tris);
                const mappingId = vizgl.mappingApi().createStaticMapping(color.hexToRgb(hexColor));
                const modelId = vizgl.modelApi().createModel(geometryId, mappingId);
                totalTris += triangles.length;
                console.log({
                    modelId,
                    geometryId,
                    mappingId,
                    totalTris,
                    tris: triangles.length,
                });
            }
            console.log({ totalTris });
        });
    }
}
export default LotsOfMeshes;
