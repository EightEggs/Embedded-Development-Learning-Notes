# 小程序连接mqtt服务器与订阅Topic实现

> ### 参考：
>
> [网络 | 微信开放文档](https://developers.weixin.qq.com/miniprogram/dev/framework/ability/network.html)
>
> [MQTT WebSocket Toolkit](http://tools.emqx.io)

## 微信小程序对网络通信的限制

每个微信小程序需要事先设置通讯域名，小程序**只可以跟指定的域名进行网络通信**。包括普通 HTTPS 请求（[wx.request](https://developers.weixin.qq.com/miniprogram/dev/api/network/request/wx.request.html)）、上传文件（[wx.uploadFile](https://developers.weixin.qq.com/miniprogram/dev/api/network/upload/wx.uploadFile.html)）、下载文件（[wx.downloadFile](https://developers.weixin.qq.com/miniprogram/dev/api/network/download/wx.downloadFile.html)) 和 WebSocket 通信（[wx.connectSocket](https://developers.weixin.qq.com/miniprogram/dev/api/network/websocket/wx.connectSocket.html)）。

- 从基础库 2.4.0 开始，网络接口允许与**局域网** IP 通信，但要注意**不允许与本机 IP 通信**。
- 从 2.7.0 开始，提供了 UDP 通信（[wx.createUDPSocket](https://developers.weixin.qq.com/miniprogram/dev/api/network/udp/wx.createUDPSocket.html)）。
- 从 2.18.0 开始，提供了 TCP 连接（[wx.createTCPSocket](https://developers.weixin.qq.com/miniprogram/dev/api/network/tcp/wx.createTCPSocket.html))，只允许与同个局域网内的非本机 IP 以及配置过的服务器域名通信。

## 参考源码

```vue
<script>
import { connect } from "mqtt";
const mqttUrl = 'wxs://mqtt.mqttssledu.xyz:8084/mqtt'; // Test URL, only for learning use.
export default {
    data() {
        return {
            client: {}
        };
    }
    components: {},
    methods: {},
    onShow() {
        var that = this
        that.client = connect(mqttUrl)
        that.client.on('connect', function() {
            console.log("Connection to mqtt server succesful!")
            that.client.subscribe("/mysmarthome/pub", function(err) {
                if(!err) console.log("Subscription successful!")
            })
        })
    }
} 
</script>
```
