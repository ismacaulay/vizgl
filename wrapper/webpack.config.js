const path = require('path');

module.exports = {
    entry: './index.js',
    output: {
        filename: `wrapper.js`,
        path: path.resolve(__dirname, './dist'),
    },
};
