const path = require("path");

const moduleName = "vizgl-wrapper";

module.exports = {
  entry: "./vizgl-wrapper/index.js",
  output: {
    filename: `${moduleName}-umd.js`,
    // path: path.resolve(__dirname, "dist"),
    path: path.resolve(__dirname, "../www"),
    library: moduleName,
    libraryTarget: "umd"
  },
  mode: "development",
  watch: true,
  devtool: "inline-source-map"
};
