module.exports = function(rest){

  var mongoose = require('mongoose');
  // var Todo = mongoose.model("Todo");
  var Todo = mongoose.model("Cart");

  rest.get('/db/cart', function(req, res) {
    Todo.find(function(err, cart) {
      res.ok(cart);
    });
  });


  rest.get('/db/cart/:id', function(req, res) {

    var id = req.params.id;
    Todo.findById(id, function (err, cart) {
       if(cart)
         res.ok(cart);
       else
         res.notFound();
    })
  });

  rest.put('/db/cart/:id', function(req, res) {

    var id = req.params.id;

    Todo.update({_id:id},req.body,function(err){
      if(err) {
        return res.internalServerError();
      }

      return res.accepted('/db/cart/' + encodeURI(id));
    });

  });

  rest.post('/db/cart', function(req, res) {

    var cart = new Todo(req.body);
    cart.save();

    res.ok(cart);
  });

  rest.delete('/db/cart/:id', function(req, res) {

    var id = req.params.id;
    Todo.findByIdAndRemove(id, function (err) {
      if (err) {

        console.log(err);
        return res.internalServerError();
      }
      return res.accepted();
    });
  });

  return rest;

};
