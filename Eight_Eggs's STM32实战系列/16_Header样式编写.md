# 顶部Header样式编写

## 参考图

![image](../src/s2_16.png)

## 参考源码

> 注：数据不代表真实情况。

```html
<template>
	<div class="wrapper"> </div>
		<div class="header-wrapper"> </div>
			<div class="header-title">
				<span>空气质量-良好</span>
				<span>南宁市</span>
			</div>
			<div class="header-text">
				<span>55</span>
				<span>阴</span>
			</div>
			<div class="weather-advice">空气质量良好，健康人群外出活动无需刻意防护</div>
		<div class="body-wrapper"> </div>
</template>
```

```scss
<style lang="scss" scoped>
.wrapper {
    padding: 15px;
    .header-wrapper {
        background-color: #3d7ef9;
        border-radius: 20px;
        color: #fff;
        box-shadow: #d6d6d6 0 0 5px;
        padding: 15px 30px;
        .header-title {
            display: flex;
            justify-content: space-between;
        }
        .header-text {
            font-size: 32px;
            font-weight: 400;
            display: flex;
            justify-content: space-between;
        }
        .weather-advice {
            margin-top: 20px;
            font-size: 12px;
        }
    }
}
</style>
```
