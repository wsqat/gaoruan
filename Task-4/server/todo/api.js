module.exports = function(rest){

  var mongoose = require('mongoose');
  var Todo = mongoose.model("Todo");

  rest.get('/db/todo', function(req, res) {
    Todo.find(function(err, todo) {
      res.ok(todo);
    });
  });


  rest.get('/db/todo/:id', function(req, res) {

    var id = req.params.id;
    Todo.findById(id, function (err, todo) {
       if(todo)
         res.ok(todo);
       else
         res.notFound();
    })
  });

  rest.put('/db/todo/:id', function(req, res) {

    var id = req.params.id;

    Todo.update({_id:id},req.body,function(err){
      if(err) {
        return res.internalServerError();
      }

      return res.accepted('/db/todo/' + encodeURI(id));
    });

  });

  rest.post('/db/todo', function(req, res) {

    var todo = new Todo(req.body);
    todo.save();

    res.ok(todo);
  });

  rest.delete('/db/todo/:id', function(req, res) {

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
