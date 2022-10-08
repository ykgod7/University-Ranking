<template>

    <Navbar />
<div class="container" style="">

<router-view />

</div>
    <Footer />
</template>


<script>
import Navbar from '@/components/NavbarPage.vue'
import Footer from '@/components/FooterPage.vue'


export default {
    components: {
        Navbar,
        Footer
    }

}
</script>

<style>
#app {
    min-height: 800px;
    display:flex; 
    flex-direction:column; 
}
</style>