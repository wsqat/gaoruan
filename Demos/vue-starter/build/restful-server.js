module.exports = function(app){

  if (!app) throw new Error('Must provide express instance.');
  var expressRest = require('express-rest');


  //增加对 json的支持
  var rest = expressRest(app, {
    serializers: {
      'application/json': {
        deserialize: function (req, res, next) {
          next();
        },
        serialize: function (req, res, next) {
          next();
        }
      }
    }
  });


  var records =[
    {"label":"1111","isFinished":true},
    {"label":"2222","isFinished":true}
  ];


  rest.get('/api/todo', function(req, rest) {
    rest.ok(records);
  });


  rest.get('/api/todo/:id', function(req, rest) {
    var record = records[req.params.id];
    if (record){
      rest.ok(record);
    }
    else{
      rest.notFound();
    }
  });

  rest.put('/api/todo/:id', function(req, rest) {
    records[req.params.id] = req.body;
    return rest.accepted('/api/todo/' + encodeURI(req.params.id));
  });

  rest.post('/api/todo', function(req, rest) {
    records.push(req.body);
    rest.created('/api/todo/' + (records.length - 1));
  });

  rest.delete('/api/todo/:id', function(req, rest) {

    var idx = req.params.id;

    if(!records[idx]) {
      rest.notFound();
    }
    else{
      records.splice(idx, 1);
      rest.accepted();
    }
  });

  return rest;

};
