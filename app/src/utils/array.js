class ArrayUtils {
    static flattenToTypedArray(input, TypedArray) {
        const width = input[0].length;
        const out = new TypedArray(input.length * width);

        for (let i = 0; i < input.length; i++) {
            for (let j = 0; j < width; j++) {
                out[i * width + j] = input[i][j];
            }
        }
        return out;
    }
}
export default ArrayUtils;
