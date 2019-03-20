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

        this._createVoxelMesh = this._module.wrap('createVoxelMesh', 'number', [
            'number', // uint32_t[3] dims
        ]);

        this._createVoxelMesh2 = this._module.wrap('createVoxelMesh2', 'number', [
            'number', // float* tensor_u
            'number', // int tensor_u_length
            'number', // float* tensor_v
            'number', // int tensor_v_length
            'number', // float* tensor_w
            'number', // int tensor_w_length
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

    createVoxelMesh(dims, blockSize) {
        if (blockSize === undefined) {
            blockSize = [1, 1, 1];
        }

        let buffer;
        let blocksizeBuffer;
        return this._module.execute({
            func: () => {
                buffer = this._module.malloc(new Uint32Array(dims));
                blocksizeBuffer = this._module.malloc(new Float32Array(blockSize));
                return this._createVoxelMesh(buffer, blocksizeBuffer);
            },
            cleanup: () => {
                this._module.free(buffer);
                this._module.free(blocksizeBuffer);
            },
        });
    }

    createVoxelMesh2(tensor_u, tensor_v, tensor_w) {
        let uBuffer;
        let vBuffer;
        let wBuffer;
        return this._module.execute({
            func: () => {
                uBuffer = this._module.malloc(new Float32Array(tensor_u));
                vBuffer = this._module.malloc(new Float32Array(tensor_v));
                wBuffer = this._module.malloc(new Float32Array(tensor_w));
                return this._createVoxelMesh2(
                    uBuffer,
                    tensor_u.length,
                    vBuffer,
                    tensor_v.length,
                    wBuffer,
                    tensor_w.length,
                );
            },
            cleanup: () => {
                this._module.free(uBuffer);
                this._module.free(vBuffer);
                this._module.free(wBuffer);
            },
        });
    }
}
