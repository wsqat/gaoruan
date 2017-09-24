<template>

  <div class="grey-box">

    <h1> 父组件(灰色背景)</h1>


    <Panel v-model="panel" title="模块A (点击展开/收起)">

      slot 内容在这里 <br>
      slot 内容在这里 <br>
      slot 内容在这里 <br>

    </Panel>

    <br />

    <div style="float:left; width: 100%">
    <h2>这里显示父组件传入的值， 会被子组件改变</h2>
    <ul>
      <li>模块A 详细功能1</li>
      <li>模块A 详细功能2</li>
      <li>模块A 详细功能3</li>


      panel.isshow ={{panel.isshow}} <br />
      panel.name= {{panel.name}};
    </ul>
    </div>
  </div>

</template>

<script>

  import Panel from "./Panel.vue";

  export default {

    data(){
      return {
        panel: {
            isshow : false,
            name  : "name is here"
        }
      }
    },
    components: {Panel}
  }
</script>

