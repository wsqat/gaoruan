<template>
  <div id="todo-app">
    <h1> 请使用 postman 测试 server</h1>

    <h5> refer to /build/restful-server.js</h5>

    <ul>
      <li><label>/api/get</label> 获取所有记录;</li>
      <li><label>/api/get/:id</label> 获取指定记录;</li>
      <li><label>/api/post</label> 增加一个条记录;</li>
      <li><label>/api/put/:id</label> 修改指定记录;</li>
      <li><label>/api/delete/:id</label> 删除指定记录;</li>
    </ul>
  </div>
</template>

<script>

</script>

<style >

@import "../6-todo-vuex/style.css";

ul li label{
  background-color: gainsboro;
  padding:  2px 15px;

  border-radius: 5px;
}

</style>
