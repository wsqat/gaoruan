const ITEMS_KEY ='todo_items';

export default {
  fetch(){
    return JSON.parse(window.localStorage.getItem(ITEMS_KEY) ||'[]')
  },

  save(items){
    window.localStorage.setItem(ITEMS_KEY,JSON.stringify(items));
  }
}
