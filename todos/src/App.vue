<template>
  <div id="app">
    <h1 v-text="title"></h1>
    <input v-model="newItem" v-on:keyup.enter="addNew" type="text" id="search">
    <ul style="list-style-type:none;font-size: 25px;color:blue;">
      <li v-for="item in items" v-bind:class="{finished:item.isFinished}"
       v-on:click="toggleFinish(item)">{{item.label}}</li>
    </ul>
  </div>
</template>

<script>
import Store from './store'
export default {
  data () {
    return {
      title: 'This is a todo list.',
      items: Store.fetch(),
      newItem: ''
    }
  },
  watch: {
    items: {
      handler: function(items){
        Store.save(items)
      },
      deep: true
    }
  },
  methods: {
    toggleFinish:function (item) {
      // console.log(item)
      item.isFinished = !item.isFinished
    },
    addNew:function(){
      // console.log(this.newItem)
      this.items.push({
        label: this.newItem,
        isFinished: false
      })
      this.newItem = ''
    }
  }
}
</script>

<style>
#search{
  width: 235px;
  height: 28px;
  border-radius: 10px;
  margin: 36px,0,20px,0;
  border: 1px solid #ccc;
  background-color: transparent;
  transition: border-color ease-in-out .15s,box-shadow ease-in-out .15s;
}

.finished{
  text-decoration: line-through;
  color: red;
}
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
