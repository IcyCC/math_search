<style scoped>
    .ivu-layout-header {
        padding: 0px;
        background-color: #ffffff;
    }

    .layout {
        border: 1px solid #d7dde4;
        background: #f5f7f9;
        position: relative;
        border-radius: 4px;
        overflow: hidden;
        height: 100%;
    }

    .content-wrapper {
        padding: 19px;
        min-height: 750px;
        height: ~ "calc(100% - 80px)";
        overflow: scroll;
    }

    .layout-logo {
        width: 120px;
        height: 30px;
        font-weight: bold;
        font-size: 20px;
        border-radius: 3px;
        float: left;
        position: relative;
        left: 20px;
        color: #ffffff;
        size: 30px;
        cursor: pointer;
    }

    .layout-nav {
        color: #ffffff;
        width: 100%;
        margin: 0 auto;
        margin-right: 0;
    }

    .layout-footer-center {
        text-align: center;
    }

    .ivu-menu-item {
        font-size: 15px;
        color: #ffffff;
    }
</style>
<template>
    <div class="layout">
        <Layout>
            <Header :style="{ width: '100%'}">
                <Menu mode="horizontal" theme="primary" :active-name="activity_name" @on-select="onMenuSelect">
                    <div class="layout-logo" @click="()=>{$router.push({name:'search'})}">
                        <Icon type="ios-book" />
                        搜书网
                    </div>
                    <div class="layout-nav">
                        <Col span="4" offset="3">
                            <MenuItem name="search">
                                <Icon type="ios-search"/>
                                通用搜索
                            </MenuItem>
                        </Col>
                        <Col span="4">
                            <MenuItem name="book">
                                <Icon type="ios-book"/>
                                课本预览
                            </MenuItem>
                        </Col>
                        <Col span="4">
                            <MenuItem name="graph">
                                <Icon type="ios-planet"/>
                                知识图谱
                            </MenuItem>
                        </Col>
                    </div>
                </Menu>
            </Header>
            <Content style="margin: 10px 20px 0; min-height: 620px; overflow: hidden;height:100%">
                <div style="margin-top: 25px">
                    <router-view></router-view>
                </div>
            </Content>
            <Footer class="layout-footer-center">2019 &copy; suchang cyy zzz lyf fxf xwq ssj </Footer>
        </Layout>
    </div>
</template>
<script>
    export default {
        data() {
            return {
                activity_name: "search"
            }
        },
        methods: {
            onMenuSelect: function (name) {
                this.$router.push({name: name});
            },
            highlightMenu() {
                this.activity_name = this.$route.name
            },
        },
        watch: {
            '$route': {
                handler: function () {
                    this.highlightMenu()
                },
                deep: true
            }
        }
    }
</script>
