import { Cube, LotsOfMeshes, Topography } from './meshes';

const views = {
    mesh_cube: new Cube('mesh_cube'),
    mesh_lots_of_meshes: new LotsOfMeshes('mesh_lots_of_meshes'),
    mesh_topography: new Topography('mesh_topography'),
    // mesh_triangle: {
    //     title: 'Triangle',
    // },

    // bm_2x3x4_static: {
    //     title: '2x3x4 - Static',
    // },
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
