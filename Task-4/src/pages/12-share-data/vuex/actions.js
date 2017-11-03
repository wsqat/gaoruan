let axios = require("../axios");

var API_TODO_ROUTER ="/db/todo";

const actions = {

  InitTodoItem ({ commit }) {
    return new Promise((on_result) =>{
      axios.get(API_TODO_ROUTER)
        .then(function (response){
          commit('initTodoItems', response.data);

          console.log(response);
          on_result({result:true, message:response.data});
        })
        .catch( function (error)   {
          console.log('error');
          on_result({result:false, message:error});
        } );
    });
  },




  AddTodoItem({ commit }, item) {

    axios.post(API_TODO_ROUTER, item)
      .then(function (response){
        commit('addTodoItem', response.data);
      })
      .catch( function (error)   { console.log(error);  } );
  },

  ToggleFinishedTodoItem ({ commit }, item) {

    axios.put(API_TODO_ROUTER+"/"+item._id, {isFinished: !(item.isFinished)})
      .then(function (response){
        commit('toggleFinishedTodoItem', item._id);
      })
      .catch( function (error)   { console.log(error);  } );
  },


  DeleteTodoItem ({ commit }, id) {

    axios.delete(API_TODO_ROUTER+"/"+id)
      .then(function (response){
        commit('deleteTodoItem', id);
      })
      .catch( function (error)   { console.log(error);  } );
  }



};

export default actions
