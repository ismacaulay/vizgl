class BinaryUtils {
    static load(path, OutType) {
        return fetch(path)
            .then(response => response.arrayBuffer())
            .then(buffer => new OutType(buffer));
    }
}
export default BinaryUtils;
