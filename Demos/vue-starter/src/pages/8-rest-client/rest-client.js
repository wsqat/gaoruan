var axios= require('axios');

axios.defaults.baseURL = 'http://localhost:8080';
axios.defaults.timeout = 1000 * 15;
axios.defaults.headers['Content-Type'] = 'application/json';

var API_TODO_ROUTER ="/api/todo";


var rest = {
  ok : null,  /*ok, callback function*/
  err: null   /*err, callback function*/
};

rest.list= function() {
  axios.get(API_TODO_ROUTER)
    .then(  function (response) { rest.ok(response); } )
    .catch( function (error)   { rest.err(error);  }   );
};

//获取一条记录
rest.get = function(id) {
  axios.get(API_TODO_ROUTER+"/"+id)
    .then(  function (response) { rest.ok(response); } )
    .catch( function (error)   { rest.err(error);  }   );
};

//增加一条记录
rest.add= function(obj) {
  axios.post(API_TODO_ROUTER,obj)
    .then(  function (response) { rest.ok(response); } )
    .catch( function (error)   { rest.err(error);  }   );
};

//修改一条记录
rest.modify = function(id, obj) {
  axios.put(API_TODO_ROUTER+"/"+id, obj)
    .then(  function (response) { rest.ok(response); } )
    .catch( function (error)   { rest.err(error);  }   );
};

//删除一条记录
rest.delete = function(id) {
  axios.delete(API_TODO_ROUTER+"/"+id)
    .then(  function (response) { rest.ok(response); } )
    .catch( function (error)   { rest.err(error);  }   );
};

module.exports = rest;
