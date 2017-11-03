let axios = require("../axios");

// var API_CART_ROUTER ="/db/todo";
var API_CART_ROUTER ="/db/cart";

const actions = {

  InitCartItem ({ commit }) {
    return new Promise((on_result) =>{
        axios.get(API_CART_ROUTER)
        .then(function (response){
          commit('initCartItems', response.data);

          console.log(response);
          on_result({result:true, message:response.data});
        })
        .catch( function (error)   {
          console.log('error');
          on_result({result:false, message:error});
        } );
    });
  },



  AddCartItem({ commit }, item) {

    axios.post(API_CART_ROUTER, item)
      .then(function (response){
        commit('addCartItem', response.data);
      })
      .catch( function (error)   { console.log(error);  } );
  },

  ToggleFinishedCartItem ({ commit }, item) {

    axios.put(API_CART_ROUTER+"/"+item._id, {isFinished: !(item.isFinished)})
      .then(function (response){
        commit('toggleFinishedCartItem', item._id);
      })
      .catch( function (error)   { console.log(error);  } );
  },


  DeleteCartItem ({ commit }, id) {

    axios.delete(API_CART_ROUTER+"/"+id)
      .then(function (response){
        commit('deleteCartItem', id);
      })
      .catch( function (error)   { console.log(error);  } );
  }



};

export default actions
