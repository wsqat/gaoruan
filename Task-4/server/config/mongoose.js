
var mongoose = require('mongoose');

var config = require('./config');

module.exports = function(){
  var db = mongoose.connect(config.mongodb);

  // require("../todo/model");
  require("../cart/model");
  return db;
};
