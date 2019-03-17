const views = {
    mesh_cube: {
        title: 'Cube',
    },

    mesh_triangle: {
        title: 'Triangle',
    },

    bm_2x3x4_static: {
        title: '2x3x4 - Static',
    },
};

function buildViewData(id) {
    return { id, ...views[id] };
}

export function getMeshViews() {
    return Object.keys(views)
        .filter(view => view.startsWith('mesh'))
        .map(buildViewData);
}

export function getBlockmodelViews() {
    return Object.keys(views)
        .filter(view => view.startsWith('bm'))
        .map(buildViewData);
}

export function getViewForId(id) {
    return buildViewData(id);
}
