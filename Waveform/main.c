
#define GPIOB_BASE 0x40010C00
#define GPIOC_BASE 0x40011000
#define GPIOA_BASE 0x40010800

#define RCC_APB2ENR (*(unsigned int *)0x40021018)

#define GPIOB_CRL (*(unsigned int *)0x40010C00)
#define GPIOC_CRH (*(unsigned int *)0x40011004)
#define GPIOA_CRL (*(unsigned int *)0x40010800)

#define GPIOB_ODR (*(unsigned int *)0x40010C0C)
#define GPIOC_ODR (*(unsigned int *)0x4001100C)
#define GPIOA_ODR (*(unsigned int *)0x4001080C)
	



void SystemInit(void);
void Delay_ms(volatile  unsigned  int);

void Delay_ms( volatile  unsigned  int  t)
{
     unsigned  int  i;
     while(t--)
         for (i=0;i<800;i++);
}


int main(){
	// 开启时钟
	RCC_APB2ENR |= (1<<3); // 开启 GPIOB 时钟
	RCC_APB2ENR |= (1<<4); // 开启 GPIOC 时钟
	RCC_APB2ENR |= (1<<2); // 开启 GPIOA 时钟
	
	
	// 设置 GPIO 为推挽输出
	// 设置 GPIOB 最后四位为 0001 (B0)
	GPIOB_CRL |= (1<<0);  // 最后一位设置为1
	GPIOB_CRL &= ~(0xE);  // 倒数二、三、四位设置为0
	// 设置 GPIOC 前四位为 0001  (C15)
	GPIOC_CRH |= (1<<28); // 第四位设置为1
	GPIOC_CRH &= ~(0xE0000000);  // 前三位设置为0
	// 设置 GPIOA 最后四位为 0001 (A0)
	GPIOA_CRL |= (1<<0);  // 最后一位设置为1
	GPIOA_CRL &= ~(0xE);  // 倒数二、三、四位设置为0

	
	// 3个LED初始化为不亮（即高点位）
	GPIOB_ODR |= (1<<0);  // 最后一位设置为1
	GPIOC_ODR |= (1<<15); // 倒数第15位设置为1
	GPIOA_ODR |= (1<<0);  // 最后一位设置为1
	
	
	while(1){
		GPIOB_ODR &= ~(1<<0); // 点灯1
		Delay_ms(1000000);
		GPIOB_ODR |= (1<<0);  // 灭灯1
		
		GPIOC_ODR &= ~(1<<15); // 点灯2
		Delay_ms(1000000);
		GPIOC_ODR |= (1<<15);  // 灭灯2
		
		GPIOA_ODR &= ~(1<<0); // 点灯3
		Delay_ms(1000000);
		GPIOA_ODR |= (1<<0);  // 灭灯3
		
	}
	
}


void SystemInit(){
	
}























