import Vue from 'vue'
import Router from 'vue-router'
import Home from './views/Home.vue'

Vue.use(Router)

export default new Router({
    routes: [
        {
            path: '/',
            name: 'home',
            component: Home,
            children: [
                {
                    path: '/search',
                    name: 'search',
                    component: () => import('@/views/CommSearch')
                },
                {
                    path: '/result',
                    name: 'result',
                    component: () => import('@/views/ResultPage')
                },
                {
                    path: '/book',
                    name: 'book',
                    component: () => import('@/views/BookPreview')
                },
                {
                    path: '/graph',
                    name: 'graph',
                    component: () => import('@/views/KnowledgeGraph')
                },
            ]
        },
    ]
})