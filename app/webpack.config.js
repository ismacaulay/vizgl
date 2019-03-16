const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
    entry: './src/index.js',
    output: {
        filename: `app.bundle.js`,
        path: path.resolve(__dirname, '../www'),
    },
    plugins: [
        new HtmlWebpackPlugin({
            hash: true,
            filename: 'index.html', //relative to root of the application
            template: './src/index.html',
        }),
    ],
};
