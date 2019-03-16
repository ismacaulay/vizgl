const path = require('path');

module.exports = {
    entry: './vizgl-wrapper/index.js',
    output: {
        filename: `vizgl-wrapper.js`,
        path: path.resolve(__dirname, '../www'),
    },
};
