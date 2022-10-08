import { createRouter, createWebHistory } from 'vue-router'
import Home from '../pages/MainPage.vue'
import Info from '../pages/InfoPage.vue'
import Login from '../pages/LoginPage.vue'


const router = createRouter({
    history: createWebHistory(),
    routes: [{
            path: '/',
            name: 'Home',
            component: Home
        },
        {
            path: '/:name',
            name: 'Info',
            component: Info
        },
        {
            path: '/login',
            name: 'Login',
            component: Login
        }
    ],
    scrollBehavior(to, from, savedPosition) {
        if (savedPosition) {
            return savedPosition
        } else {
            return { top: 0 }
        }
    }
})


export default router;