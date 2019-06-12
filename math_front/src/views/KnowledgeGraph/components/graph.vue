<template>
    <v-chart :options="option" @click="handleClick" auto-resize ref="chart"></v-chart>
</template>

<script>
    import {getGexf} from  '@/service/api'
    import dataTool from 'echarts/extension/dataTool';
    export default {
        name: "graph",
        data: function () {
            return {
                option: {}
            }
        },
        methods:{
            handleClick:function(e){
                if (e.dataType === 'node') {
                    this.$router.push({
                        name: 'result',
                        query:{
                            query_text: e.data.name,
                            query_type: 'concept'
                        }

                    })
                }
            }
        },
        mounted: function () {
            getGexf().then((resp)=>{
                let xml = resp.data
                var graph = dataTool.gexf.parse(xml);
                var categories = [];
                graph.nodes.forEach(function (node) {
                    node.itemStyle = null;
                    node.symbolSize = 40;
                    node.value = node.symbolSize;
                    node.category = node.attributes.modularity_class;
                    // Use random x, y
                    node.x = node.y = null;
                    node.draggable = true;
                });
                this.option = {
                    title: {
                        text: '课本知识',
                        subtext: 'Default layout',
                        top: 'bottom',
                        left: 'center'
                    },
                    tooltip: {},
                    legend: [{
                        // selectedMode: 'single',
                        data: categories.map(function (a) {
                            return a.name;
                        })
                    }],
                    animation: false,
                    series : [
                        {
                            name: '课本知识',
                            type: 'graph',
                            layout: 'force',
                            data: graph.nodes,
                            links: graph.links,
                            categories: categories,
                            roam: true,
                            label: {
                                show: true,
                            },
                            focusNodeAdjacency: true,
                            itemStyle: {
                                normal: {
                                    borderColor: '#fff',
                                    borderWidth: 1,
                                    shadowBlur: 10,
                                    shadowColor: 'rgba(0, 0, 0, 0.3)'
                                }
                            },
                            force: {
                                repulsion: 500,
                                edgeLength: [30, 100]
                            }
                        }
                    ],
                };
            })
        }

    }
</script>

<style scoped>

</style>