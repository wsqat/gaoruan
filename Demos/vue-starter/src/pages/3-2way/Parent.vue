<template>

  <div class="grey-box">

    <h1> 父组件(灰色背景)</h1>


    <Panel v-bind:value="showA" title="模块A (点击展开/收起)"
           @input="showChange">

      <ul>
        <li>模块A 详细功能1</li>
        <li>模块A 详细功能2</li>
        <li>模块A 详细功能3</li>
      </ul>

    </Panel>


    <Panel v-model="showB" title="模块B (点击展开/收起)">

      <ul>
        <li>模块B 详细功能1</li>
        <li>模块B 详细功能2</li>
      </ul>

    </Panel>
  </div>

</template>

<script>

  import Panel from "./Panel.vue";

  export default {
    data(){
      return {
          showA: false,
          showB: true
      }
    },

    methods: {
      showChange(val){
        this.showA = val;
      }
    },
    components: {Panel}
  }
</script>

