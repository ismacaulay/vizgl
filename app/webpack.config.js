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
    module: {
        rules: [
            {
                test: /\.(js|jsx)$/,
                exclude: /(node_modules|bower_components)/,
                loader: 'babel-loader',
                options: { presets: ['@babel/env'] },
            },
            {
                test: /\.css$/,
                use: ['style-loader', 'css-loader'],
            },
        ],
    },
    resolve: { extensions: ['*', '.js', '.jsx'] },
};
