const merge = require('webpack-merge');
const common = require('./webpack.common.js');

module.exports = merge(common, {
    mode: 'development',
    devtool: 'inline-source-map',
    devServer: {
        contentBase: './dist',
        proxy: {
            "/status": {
                target: "http://192.168.30.39/status"
            },
            "/off": {
                target: "http://192.168.30.39/off"
            },
            "/on": {
                target: "http://192.168.30.39/on"
            }
        }
    }
})