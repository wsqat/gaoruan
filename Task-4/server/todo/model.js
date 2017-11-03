var mongoose = require('mongoose');
var Schema = mongoose.Schema;

// Define Todo schema
var TodoSchema = new Schema({
    label       :  String,
    isFinished  :  Boolean
});

// add schema to  model
mongoose.model('Todo', TodoSchema);
