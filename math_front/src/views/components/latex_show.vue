<template>
    <div>
        <template v-for="(t) in text_blocks">
            <span v-if="t && t[0] === '$' " v-katex="replaceTex(t)" style="background-color: #dcdee2; "></span>
            <span v-else v-html="t">  </span>
        </template>
    </div>
</template>

<script>
    export default {
        name: "latex_show",
        props: {
            text: String
        },
        data: function(){
            return {
                text_blocks : []
            }
        },
        watch: {
            text: function () {
                this.getTextBlocks()
            }
        },
        methods:{
            getTextBlocks: function () {
                let buffer = ""
                let in_tex = false;
                for (let i in this.text) {
                    if (this.text[i] === '$'){
                        if (!in_tex) {
                            in_tex = true
                            this.text_blocks.push(buffer)
                            buffer  = "";
                            buffer = buffer + this.text[i]
                        } else {
                            in_tex = false
                            buffer = buffer + this.text[i]
                            this.text_blocks.push(buffer)
                            buffer  = "";
                        }
                    } else {
                        buffer = buffer + this.text[i]
                    }
                }
                if(buffer){
                    this.text_blocks.push(buffer)
                }
                this.$forceUpdate();
            },
            replaceTex: function (item) {
                return item.replace(new RegExp(String.raw`\$`, 'g'),'')
            }
        },
        mounted: function () {
           this.getTextBlocks()
        }
    }
</script>

<style scoped>

</style>