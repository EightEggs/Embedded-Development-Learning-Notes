# OLED数据显示

## 示例采用在定时器中断里实现显示

- 主要头文件：`timer.h, oled.h, stdio.h`

- 主要源文件：`timer.c, oled.c`

- 主要函数：

  ```c
  void TIMx_Int_Init(u16 arr, u16 psc); // 计时器初始化
  void TIMx_IRQHandler(void); // TIMx中断
  void OLED_Init(void); // OLED初始化
  void OLED_ColorTurn(bool flag); // 是否反色显示
  void OLED_DisplayTurn(bool flag); // 是否翻转显示
  void OLED_Clear(void); // 清屏
  int sprintf(char *buffer, const char *format, ...); // C标准库函数
  void OLED_ShowString(unsigned char x, unsigned char y, unsigned char *buffer, unsigned char size); // 显示（非中文）字符
  void OLED_Refresh(void); // 刷新
  ```