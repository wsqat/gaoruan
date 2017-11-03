var mongoose = require('mongoose');
var Schema = mongoose.Schema;

// // Define Todo schema
// var TodoSchema = new Schema({
//     label       :  String,
//     isFinished  :  Boolean
// });

// Define Cart schema
var CartSchema = new Schema({
    label       :  String,
    price       :  String,
    number      :  String,
    isFinished  :  Boolean
});

// add schema to  model
// mongoose.model('Todo', TodoSchema);
mongoose.model('Cart', CartSchema);
