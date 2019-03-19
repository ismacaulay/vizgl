import FirebaseJsonDataLoader from './firebase/FirebaseJsonDataLoader';
import LocalJsonDataLoader from './local/LocalDataLoader';

export class DataLoader {
    static create() {
        if (process.env.NODE_ENV === 'production') {
            console.log('Creating firebase data loader');
            return new FirebaseJsonDataLoader();
        } else {
            console.log('Creating local data loader');
            return new LocalJsonDataLoader();
        }
    }
}
