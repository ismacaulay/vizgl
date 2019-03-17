import { Cube, LotsOfMeshes, Topography } from './meshes';
import { StaticBM, BlockModelWithNaNs } from './blockmodels';

const views = {
    mesh_cube: new Cube('mesh_cube'),
    mesh_lots_of_meshes: new LotsOfMeshes('mesh_lots_of_meshes'),
    mesh_topography: new Topography('mesh_topography'),

    bm_static: new StaticBM('bm_static'),
    bm_with_nans: new BlockModelWithNaNs('bm_with_nans'),
};

export function getMeshViews() {
    return Object.keys(views)
        .filter(view => view.startsWith('mesh'))
        .map(id => views[id]);
}

export function getBlockmodelViews() {
    return Object.keys(views)
        .filter(view => view.startsWith('bm'))
        .map(id => views[id]);
}

export function getViewForId(id) {
    return views[id];
}
