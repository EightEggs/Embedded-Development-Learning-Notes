# 设备端接收MQTT服务器命令

>  ### 参考:
>
> [cJSON](https://github.com/DaveGamble/cJSON)

- 主要头文件：`cJSON.h`

- 主要源文件：`cJSON.c`

- 主要函数：

  ```c
  #define CJSON_PUBLIC(type) type
  CJSON_PUBLIC(cJSON *) cJSON_Parse(const char *value);
  CJSON_PUBLIC(void) cJSON_Delete(cJSON *item);
  uint8 MQTT_UnpacketRecv(unsigned char *cmd);
  uint8 MQTT_UnpacketCmd(uint8 *rev_data, int8 **cmdid, int8 **req, uint16 *req_len);
  ```