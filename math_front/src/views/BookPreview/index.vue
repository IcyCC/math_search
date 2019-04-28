<template>
    <div>
        <Row>
            <Col span="5" offset="3">
                <span style="font-size: 20px;font-weight: bold">目录</span>
                <Card style="height: 580px">
                    <Tree :data="data1"></Tree>
                </Card>
            </Col>
            <Col span="12" offset="1">
                <span style="font-size: 20px;font-weight: bold">内容</span>
                <Card style="height: 580px">
                </Card>
            </Col>
        </Row>
    </div>
</template>

<script>
    export default {
        name: "index",
        data: function () {
            return {
                data1: [
                    {
                        title: 'parent 1',
                        expand: true,
                        children: [
                            {
                                title: 'parent 1-1',
                                expand: true,
                                children: [
                                    {
                                        title: 'leaf 1-1-1'
                                    },
                                    {
                                        title: 'leaf 1-1-2'
                                    }
                                ]
                            },
                            {
                                title: 'parent 1-2',
                                expand: true,
                                children: [
                                    {
                                        title: 'leaf 1-2-1'
                                    },
                                    {
                                        title: 'leaf 1-2-1'
                                    }
                                ]
                            }
                        ]
                    }
                ]
            }
        }
    }
</script>

<style scoped>

</style>