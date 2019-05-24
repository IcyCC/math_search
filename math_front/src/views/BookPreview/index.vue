<template>
    <div>
        <Row>
            <Col span="5" offset="3">
                <span style="font-size: 20px;font-weight: bold">目录</span>
                <Card style="height: 780px;overflow: scroll;">
                    <Tree  :data="book_index"></Tree>
                </Card>
            </Col>
            <Col span="12" offset="1">
                <span style="font-size: 20px;font-weight: bold">内容</span>
                <Card style="height: 780px;overflow: scroll;">
                    <div v-html="latex"> </div>
                </Card>
            </Col>
        </Row>
    </div>
</template>

<script>
    import { parse, HtmlGenerator } from 'latex.js'
    import {getBookIndex, getBookPage} from '@/service/api'
    export default {
        name: "index",
        watch: {
            latex: function (val) {
                let generator = new HtmlGenerator({ hyphenate: false })
                let c = parse(this.latex, { generator: generator }).htmlDocument()
                console.log(c )
            }
        },
        data: function () {
            return {
                book_index: [
                    {
                        title: "课本目录",
                        expand: true,
                        children: [
                        ]
                    }
                ],
                content: '',
                latex : '<h1>数学课本</h1>',
                select_title: ''
            }
        },
        methods:{
           onPageClick: function (page) {
               this.select_page = page
               getBookPage(page).then((resp)=>{
                    this.latex = resp.data
               })
           }

        },
        mounted: function () {
            getBookIndex().then((resp)=>{
                this.book_index[0].render =  (h, params) => {
                    return h('span', {
                        class: 'tree-font-title',
                    }, this.book_index[0].title)
                }
                this.book_index[0].children = resp.data.book_index.map((item)=>{
                    item.render = (h, params) => {
                        let height = this.select_title === item.title ? '#38f': '#555'
                        return h('span', {
                            class: 'tree-font',
                            style: {
                                color: height,
                            },
                            on: {
                                click: () => {
                                    this.select_title = item.title
                                    this.onPageClick(item.page)
                                }
                            }
                        }, item.title)
                    }
                    return item
                })
            })
        }
    }
</script>

<style >
.tree-font {
    font-size: 18px !important;
}

.tree-font-title {
    font-size: 30px !important;
    }

</style>