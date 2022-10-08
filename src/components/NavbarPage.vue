<template>
<nav class="navbar navbar-dark bg-dark navbar-expand-lg py-2 fixed-top">
    <div class="container-fluid">
        <router-link class="navbar-brand" :to="{name: 'Home'}" style="font-size: 25px">K-Ranking</router-link>
        <!-- <div>
            <ul class="navbar-nav">
                메뉴 추후 수정 요망
                <li class="nav-item">
                    <a class="nav-link active" aria-current="page" href="#">Menu</a>
                </li>

                <li class="nav-item">
                    <router-link class="nav-link active" aria-current="page" :to="{name: 'Login'}">Login</router-link>
                </li>
            </ul>
        </div> -->
    </div>
</nav>
</template>
<style scoped>
.navbar {
    font-family: 'Bebas Neue', cursive;
}
</style>