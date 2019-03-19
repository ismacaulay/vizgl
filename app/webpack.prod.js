const merge = require('webpack-merge');
const webpack = require('webpack');
const common = require('./webpack.common.js');

module.exports = (env, args) => {
    const isLocalProduction = args.local !== undefined;

    return merge(common, {
        mode: 'production',
        plugins: [
            new webpack.DefinePlugin({
                'process.env.DATALOADER': JSON.stringify('firebase'),
                LOCAL_PRODUCTION: JSON.stringify(isLocalProduction),
            }),
        ],
    });
};
