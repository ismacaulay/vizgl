class JsonUtils {
    static load(path) {
        return fetch(path).then(response => response.json());
    }
}
export default JsonUtils;
