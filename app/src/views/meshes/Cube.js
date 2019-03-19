import View from '../View';

class Cube extends View {
    constructor(id) {
        super(id, 'Cube');
    }

    load(vizgl, dataloader) {
        return dataloader.loadJson('manifests/cube.json').then(manifest => {
            const { elements } = manifest;

            dataloader.loadBinary(elements[0].vertices, Float32Array).then(vertices => {
                // const { vertices } = geometry;
                const geometryId = vizgl.geometryApi().createMesh(vertices);
                const color = [116, 191, 165];
                const mappingId = vizgl.mappingApi().createStaticMapping(color);

                vizgl.modelApi().createModel(geometryId, mappingId);
                console.log(`Loaded ${this.id}`);
            });
        });
    }
}
export default Cube;
