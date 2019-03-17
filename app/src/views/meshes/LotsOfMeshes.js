import View from '../View';

import { array, color, json } from '../../utils';

class LotsOfMeshes extends View {
    constructor(id) {
        super(id, 'Lots of Meshes');
    }

    load(vizgl) {
        return json.load('res/large-data/lots-of-meshes.json').then(meshes => {
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
                vizgl.modelApi().createModel(geometryId, mappingId);
                totalTris += triangles.length;
            }
            console.log({ totalTris });
            console.log(`Loaded ${this.id}`);
        });
    }
}
export default LotsOfMeshes;
