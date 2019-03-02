export class ModuleWrapper {
    constructor(module) {
        this._module = module;
    }

    wrap(name, returnVal, args) {
        return this._module.cwrap(name, returnVal, args);
    }

    malloc(typedBuffer) {
        buffer = this._module._malloc(typedBuffer.length * typedBuffer.BYTES_PER_ELEMENT);

        if (typedBuffer instanceof Uint8Array) {
            this._module.HEAPU8.set(typedBuffer, buffer);
        } else if (typedBuffer instanceof Uint32Array) {
            this._module.HEAPU32.set(typedBuffer, buffer >> 2);
        } else if (typedBuffer instanceof Float32Array) {
            this._module.HEAPF32.set(typedBuffer, buffer >> 2);
        } else {
            throw Error(
                `[malloc] Unknown buffer type: ${Object.prototype.toString.call(typedBuffer)}`,
            );
        }

        return buffer;
    }

    free(buffer) {
        this._module._free(buffer);
    }

    execute(args) {
        const { func = () => {}, cleanup = () => {} } = args;

        let result, error;
        try {
            result = func();
        } catch (e) {
            error = e;
        } finally {
            cleanup();
        }

        if (error) {
            throw error;
        }
        return result;
    }
}
