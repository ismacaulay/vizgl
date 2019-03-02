export class GeometryApi {
    constructor(module) {
        this._module = module;

        this._createMesh = this._module.wrap('createMesh', 'number', [
            'number', // float* vertices
            'number', // int numVertices
        ]);

        this._createMesh2 = this._module.wrap('createMesh2', 'number', [
            'number', // float* vertices
            'number', // int numVertices
            'number', // uint32_t* triangles
            'number', // int numTriangles
        ]);
    }

    createMesh(vertices) {
        let buffer;
        return this._module.execute({
            func: () => {
                buffer = this._module.malloc(new Float32Array(vertices));
                return this._createMesh(buffer, vertices.length);
            },
            cleanup: () => {
                this._module.free(buffer);
            },
        });
    }

    createMesh2(vertices, triangles) {
        let vBuffer;
        let tBuffer;
        return this._module.execute({
            func: () => {
                vBuffer = this._module.malloc(new Float32Array(vertices));
                tBuffer = this._module.malloc(new Uint32Array(triangles));
                return this._createMesh2(vBuffer, vertices.length, tBuffer, triangles.length);
            },
            cleanup: () => {
                this._module.free(vBuffer);
                this._module.free(tBuffer);
            },
        });
    }
}
