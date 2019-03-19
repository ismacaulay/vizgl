import firebase from 'firebase/app';
import 'firebase/storage';

import { json, binary } from '../../utils';

class FirebaseJsonDataLoader {
    constructor() {
        const config = {
            apiKey: 'AIzaSyB7v0KZyNzjIXTtacnqgmdgcITxz1BFvhM',
            authDomain: 'vizgl-6ba87.firebaseapp.com',
            databaseURL: 'https://vizgl-6ba87.firebaseio.com',
            projectId: 'vizgl-6ba87',
            storageBucket: 'vizgl-6ba87.appspot.com',
            messagingSenderId: '1094081193482',
        };
        firebase.initializeApp(config);
        this._storage = firebase.storage();
    }

    loadJson(path) {
        return this._storage
            .ref(path)
            .getDownloadURL()
            .then(url => json.load(url));
    }

    loadBinary(path, OutType) {
        return this._storage
            .ref(path)
            .getDownloadURL()
            .then(url => binary.load(url, OutType));
    }
}
export default FirebaseJsonDataLoader;
