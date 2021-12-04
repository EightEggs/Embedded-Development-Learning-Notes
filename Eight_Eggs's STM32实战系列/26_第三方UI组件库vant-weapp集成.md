# 第三方UI组件库vant-weapp集成

> ### 参考：
> 
> [Vant-Weapp官方文档](https://youzan.github.io/vant-weapp/#/home)

## 安装

```shell
npm install vant-weapp -S --production
```

## 修改配置文件

**在`app.json`中添加：**

```json
"pages":[
    "pages/login/main",
    "pages/index/main",
    "pages/logs/main"  ],

"usingComponents":{
    "van-button":"vant-weapp/dist/button/index"
}
```

**在`pages`文件夹下新建文件夹`login`, 包含`index.vue`, `main.js`, `main.json`。**

**在`webpack.base.config.js`中添加：**

```js
if(/^wx$/.test(PLATFORM)) {
  baseWebpackConfig = merge(baseWebpackConfig,{
    plugins: [
      new CopyWebpackPlugin([{
        from: resolve('node_modules/vant-weapp/dist')
        to: resolve('dist/wx/vant-weapp/dist')
      }])
    ]
  })
}
```

## 测试运行

```shell
npm run dev
```
