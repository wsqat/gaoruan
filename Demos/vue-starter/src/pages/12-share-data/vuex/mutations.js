

function getIndexbyId(state, id) {
  for(var i in state.todoItems)
  {
    var item = state.todoItems[i];

    if(item._id === id)
    {
      return i;
    }
  }
  return -1;
}

function getItembyId(state, id) {
  var index = getIndexbyId(state, id);
  if(index === -1)
    return null;

  return state.todoItems[index];
}

const mutations = {

  initTodoItems(state, todoItems) {
    state.todoItems = todoItems
  },


  toggleFinishedTodoItem(state, id){


    var item = getItembyId(state, id);

    if(item)
    {
      item.isFinished = !item.isFinished;
    }
  },


  addTodoItem(state, item){

    if(typeof(item) ==='string')
    {
      item = JSON.parse(item);
    }
    state.todoItems.push(item);
  },



  deleteTodoItem(state, id){

    var index = getIndexbyId(state, id);

    if(index === -1)
    {
       return ;
    }

    state.todoItems.splice(index, 1);
  }
};

export default mutations
