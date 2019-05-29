<template>
    <Modal
            :value="visible"
            @on-cancel="handleClose"
    >
            <div slot="header">
                {{ result.chapter }}
            </div>
            <div>
                <template v-for="w in words">
                    <span @click="handleWordClick(w)" v-if="key_words.includes(w)" style="color: rgb(26, 13, 171)">{{w}}</span>
                    <span v-else>{{w}}</span>
                </template>
            </div>
            <div slot="footer">

            </div>
    </Modal>
</template>

<script>

    import {segmentWords,getKeyWords} from '@/service/api'
    export default {
        name: "detail.vue",
        props: {
            result: {type:Object},
            query_text: String,
            visible: Boolean
        },
        data: function(){
            return {
                words:[],
                key_words: []
            }
        },
        watch: {
            visible: function () {
                if (this.visible) {
                    segmentWords(this.result.raw).then((resp)=>{
                        this.words = resp.data.words
                    })
                }
            }
        },
        methods:{
            highLight: function(text){
                let replaceReg = new RegExp(this.query_text, 'g');
                // 高亮替换v-html值
                let replaceString = '<span class="search-text" style="color: darkred;">' + this.query_text + '</span>';
                // 开始替换
                return text.replace(replaceReg, replaceString);
            },
            handleClose() {
                this.$emit('onClose')
            },
            handleWordClick(w) {
                this.$router.push({
                    name: 'result',
                    query: {
                        query_text: w,
                        query_type: 'concept'
                    }
                })
            }

        },
        mounted: function () {
            if (this.visible){

            }
        },
        created: function () {
            getKeyWords().then((resp)=>{
                this.key_words = resp.data.data
            })
        }

    }
</script>

<style scoped>

</style>