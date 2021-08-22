# mpvue模板工程初始化

>  ### 参考:
>
>  [mpvue](http://mpvue.com)

## 检查环境

```powershell
# 先检查下 Node.js 是否安装成功
PS D:\> node -v
v8.9.0

PS D:\> npm -v
5.6.0

# 由于众所周知的原因，可以考虑切换源为 taobao 源
PS D:\> npm set registry https://registry.npm.taobao.org/

# 全局安装 vue-cli
# 一般是要 sudo 权限的
PS D:\> npm install --global vue-cli@2.9
```

## 初始化模板项目

```powershell
PS D:\> vue init mpvue/mpvue-quickstart <my-project-name>

PS D:\> cd ./my-project-name

PS D:\my-project-name> npm install

PS D:\my-project-name> npm run dev
```

## 打开微信开发者工具

## 导入模板工程
