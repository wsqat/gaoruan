import Vue from 'vue'
import Router from 'vue-router'
// import Hello from '@/components/Hello'
import BusDemo from '@/components/Demo'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'BusDemo',
      component: BusDemo
    }
  ]
})
