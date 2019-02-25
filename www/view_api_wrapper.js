class ViewApi {
  constructor(module) {
    this._module = module;

    this._createMesh = module.cwrap("createMesh", null, [
      "number", // float* vertices
      "number" // int numVertices
    ]);

    this._createMesh2 = module.cwrap("createMesh2", null, [
      "number", // float* vertices
      "number", // int numVertices
      "number", // uint32_t* indices
      "number" // int numIndices
    ]);
  }

  createMesh(vertices) {
    let verticesBuffer;
    let error;

    try {
      const typedVertices = new Float32Array(vertices);

      verticesBuffer = this._module._malloc(
        typedVertices.length * typedVertices.BYTES_PER_ELEMENT
      );
      this._module.HEAPF32.set(typedVertices, verticesBuffer >> 2);

      this._createMesh(verticesBuffer, typedVertices.length);
    } catch (e) {
      error = e;
    } finally {
      this._module._free(verticesBuffer);
    }

    if (error) {
      throw error;
    }
  }

  createMesh2(vertices, indices) {
    let verticesBuffer;
    let indicesBuffer;
    let error;

    try {
      const typedVertices = new Float32Array(vertices);
      const typedIndices = new Uint32Array(indices);

      verticesBuffer = this._module._malloc(
        typedVertices.length * typedVertices.BYTES_PER_ELEMENT
      );
      this._module.HEAPF32.set(typedVertices, verticesBuffer >> 2);

      indicesBuffer = Module._malloc(
        typedIndices.length * typedIndices.BYTES_PER_ELEMENT
      );
      this._module.HEAPU32.set(typedIndices, indicesBuffer >> 2);

      this._createMesh2(
        verticesBuffer,
        typedVertices.length,
        indicesBuffer,
        typedIndices.length
      );
    } catch (e) {
      error = e;
    } finally {
      this._module._free(verticesBuffer);
      this._module._free(indicesBuffer);
    }

    if (error) {
      throw error;
    }
  }
}
