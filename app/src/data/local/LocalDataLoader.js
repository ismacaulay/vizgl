import { json, binary } from '../../utils';

class LocalDataLoader {
    constructor() {}

    loadJson(path) {
        const url = this._buildUrl(path);
        return json.load(url);
    }

    loadBinary(path, OutType) {
        const url = this._buildUrl(path);
        return binary.load(url, OutType);
    }

    _buildUrl(path) {
        return `res/${path}`;
    }
}
export default LocalDataLoader;
