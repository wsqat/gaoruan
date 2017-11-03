

function getIndexbyId(state, id) {
  for(var i in state.cartItems)
  {
    var item = state.cartItems[i];

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

  return state.cartItems[index];
}

const mutations = {

  initCartItems(state, cartItems) {
    state.cartItems = cartItems
  },


  toggleFinishedCartItem(state, id){


    var item = getItembyId(state, id);

    if(item)
    {
      item.isFinished = !item.isFinished;
    }
  },


  addCartItem(state, item){

    if(typeof(item) ==='string')
    {
      item = JSON.parse(item);
    }
    state.cartItems.push(item);
  },



  deleteCartItem(state, id){

    var index = getIndexbyId(state, id);

    if(index === -1)
    {
       return ;
    }

    state.cartItems.splice(index, 1);
  }
};

export default mutations
