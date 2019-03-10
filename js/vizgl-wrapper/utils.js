export function flattenArrayToTypedArray(input, TypedArray) {
    const width = input[0].length;
    const out = new TypedArray(input.length * width);

    input.forEach((v, i) => {
        for (let j = 0; j < width; j++) {
            out[i * width + j] = v[j];
        }
    });
    return out;
}

export function isTypedArray(array) {
    return (
        array instanceof Float32Array || array instanceof Uint32Array || array instanceof Uint8Array
    );
}
