var webpack = require("webpack");
module.exports = {
  entry: './entry.jsx',
  devtool: 'source-map',
  module: {
    loaders: [
      {
        test: /\.(jsx|js)$/,
        loader: 'babel-loader',
        exclude: /node_modules/,
        query: {presets: ['react', 'es2015']}
      },
      {test: /\.(woff|woff2)$/, loader: "url-loader"},
      {test: /\.ttf$/, loader: "url-loader"},
      {test: /\.eot$/, loader: "file-loader"},
      {test: /\.svg$/, loader: "file-loader"}, {
        test: /\.styl/,
        loaders: [
          'style',
          'css?modules&importLoaders=2&localIdentName=[name]__[local]__[hash:base64:6]',
          'autoprefixer', 'stylus'
        ]
      }
    ]
  },
  plugins: [new webpack.ProvidePlugin({$: "jquery", jQuery: "jquery"})],
  output: {
    path: __dirname + '/app/',
    filename: 'application.js',
  }
};
