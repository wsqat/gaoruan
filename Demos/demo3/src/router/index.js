import Vue from 'vue'
import Router from 'vue-router'
// import Hello from '@/components/Hello'
// import Parent from '@/components/2way/Parent'

Vue.use(Router)

import Index from '@/components/Index'
// import Parent2Way   from '@/pages/3-2way/Parent.vue'
import Parent2Way from '@/components/2way/Parent'
import ParentObj2Way from '@/components/obj2way/Parent'

export default new Router({
  routes: [
    {
     	path: '/',
     	name: 'Index',
     	component: Index
    },
    {
    	path: '/2way',
    	name: 'Parent2Way',
    	component: Parent2Way
    },
    {
        path: '/obj2way',
        name: 'ParentObj2Way',
        component: ParentObj2Way
    }
  ]
})
