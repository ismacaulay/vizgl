import View from '../View';

import { array, color } from '../../utils';

class LotsOfMeshes extends View {
    constructor(id) {
        super(id, 'Lots of Meshes');
    }

    load(vizgl, dataloader) {
        return dataloader.loadJson('manifests/lots-of-meshes.json').then(manifest => {
            const { elements } = manifest;

            let totalTris = 0;
            const elementLoaders = elements.map(element => {
                const vertLoader = dataloader.loadBinary(element.vertices, Float32Array);
                const triLoader = dataloader.loadBinary(element.triangles, Uint32Array);

                return Promise.all([vertLoader, triLoader]).then(loadedData => {
                    const [vertices, triangles] = loadedData;

                    const geometryId = vizgl.geometryApi().createMesh2(vertices, triangles);
                    const mappingId = vizgl
                        .mappingApi()
                        .createStaticMapping(color.hexToRgb(element.color));
                    vizgl.modelApi().createModel(geometryId, mappingId);
                    totalTris += triangles.length;
                });
            });

            return Promise.all(elementLoaders).then(() => {
                console.log({ count: elementLoaders.length, totalTris });
                console.log(`Loaded ${this.id}`);
            });
        });
    }
}
export default LotsOfMeshes;
