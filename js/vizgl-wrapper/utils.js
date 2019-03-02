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
