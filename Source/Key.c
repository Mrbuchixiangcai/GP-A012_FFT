//头文件header file//
#include "app_main.h"

//宏定义macro definition//
#define  ADCKEY_NUM   1

//类型定义byte definition//


//变量定义variable definition//
uint8_t   gbKeyPress;     //按键按下
uint8_t   gbKeyNone;      //没有按键按下
uint8_t   KeyValue;       //按键值
uint16_t  AdcValue;       //最初采集的AD值
uint8_t   KeyEvent;       //按键事件
uint8_t   cntKeyLoop;     //计数按键循环，短按，长按，超长按的按下时间
uint8_t   KeyCurValueBK;  //当前按键值备份
uint8_t   cntKeyLong;
uint8_t   keyNum;
uint8_t   keyBT;
uint8_t   keyBT_bk;



static    uint8_t   KeyCurValue; //按键电压当前值，current当前的
static    uint8_t   KeyLastValue;//按键电压上一次的值

const uint16_t ADKEY_TAB1[ADCKEY_NUM]=  //按键正常电压值与允许误差值
{
	0x0000,      //T_LIGHT  //按键只有短按模式切换
};
const uint16_t ADKEY_TAB2[ADCKEY_NUM]=  //按键正常电压值与允许误差值
{
	0x0000+0x50, //T_LIGHT  //按键只有短按模式切换
};

uint8_t SPASongs_Num_Table[4][11]= 
{
	"B005+A00\r\n",
	"B005+K01\r\n",
	"B005+K02\r\n",
	"B005+K03\r\n",
};

//标志位定义flags definetion//


//函数定义function definetion//
//获取按键电压，对应不同按键，有返回值
uint8_t GetKeyValue(void)
{
//	uint8_t  i;
	uint8_t  keyValue=0;
//	AdcValue=HAL_ADC_GetValue(&hadc);//PA0获取当前按键IO pin电压值,第一次获取时可能不对，转换时间不够
//	if(AdcValue<0x00A0)//采集到的任意按键电压值要小于0x00A0
//	{
////		cntIdle=0;
//		for(i=0;i<ADCKEY_NUM;i++)
//		{
//			if((AdcValue>=ADKEY_TAB1[i]) && (AdcValue<=ADKEY_TAB2[i]))//判断采集到的按键电压值为哪一个按键
//			{
//				KeyNum=i+1;//确定为某个按键，因为i初始化为0，所以加1
//				break;
//			}
//		}
//	}
	keyBT = BT_POWER();

	if(!KEY_LIGHT())//灯光按键
		keyValue = T_LIGHT;
	if (keyBT_bk != keyBT)//每次蓝牙检测IO口产生变化时才能进入，不然一直高电平就一直进入
	{
		keyBT_bk = keyBT;
		if ((!KEY_LIGHT()) && (keyBT))//如果灯光按键按下和power按键长按后同时产生作用，那就定义为灯光按键
			keyValue = T_LIGHT;				  //比如一直按着Light，再按power，就是灯光
		else
		{
			if (keyBT)
				PlayMode = PLAY_BT;
			else
				PlayMode = PLAY_OFF;
		}
	}
	
	return keyValue;//返回按键
}

//被调用时接收的是GetKeyValue()的返回值  一般固定，不更改
void KeyEventPorc(uint8_t KeyTmp)
{
	gbKeyPress=0;
	if(KeyCurValue != KeyTmp)//这个if语句是去抖，会被执行两次，第三次进来时直接跳过
	{//KeyTmp为临时值
		if(KeyCurValueBK != KeyTmp)
			KeyCurValueBK=KeyTmp;
		else //第二次进来时执行这一条
			KeyCurValue=KeyTmp;
		return;
	}
	if(KeyCurValue == KeyLastValue)
	{
		if((KeyLastValue==0) || (cntKeyLoop==0))
			return;
		if(--cntKeyLoop==0)//这个在第二次进KeyEventPorc()函数（第一次进“if(KeyCurValue==KeyLastValue)”之前）时被下面赋值为5
		{//cntKeyLoop为5就是50ms时间
			KeyValue=KeyLastValue;//防抖之后把确定的按键赋值给KeyValue
			if(gbKeyNone==0)
				gbKeyPress=1;
			switch(KeyEvent)
			{
				case 0:
					KeyEvent=1;
					KeyValue |= K_D;
					cntKeyLoop=cKEY_HOLD;
					break;
				case 1:
					KeyEvent=2;
					KeyValue |= K_H;
					cntKeyLoop=cKEY_RATE_VOL;
					break;
				case 2:
				case 3:
					KeyEvent=3;
					KeyValue |= K_R;
					cntKeyLoop=cKEY_RATE_VOL;
					if(cntKeyLong<250)
						cntKeyLong++;
					break;
			}
		}
	}
	else
	{
		if(KeyLastValue)
		{
			KeyValue=KeyLastValue;
			if(gbKeyNone==0)
				gbKeyPress=1;
			switch(KeyEvent)
			{
				case 1:KeyValue |= K_U; break;
				case 2:KeyValue |= K_LU;break;
				case 3:KeyValue |= K_LU;break;
			}
			KeyEvent=0;
		}
		else
		{
			gbKeyNone=0;
			cntKeyLong=0;
		}
		cntKeyLoop=cKEY_CLICK;
		KeyLastValue=KeyCurValue;
	}
}

//被主函数调用
void KeyScan(void)
{
	KeyEventPorc(GetKeyValue());
}

//按键处理
void KeyComMsg(void)
{
	if(gbKeyPress)
	{
		switch(KeyValue)
		{
//			case KU(T_BT_POWER):
//			{}
//			case KLU(T_BT_POWER):
//			{
//				if(cntKeyLong>=10)
//					break;
//				PlayMode=PLAY_BT;
//				break;
//			}
			case KU(T_LIGHT): 
			case KLU(T_LIGHT):
			{
				if(PlayMode==PLAY_BT)
				{
					
					if(keyNum==0) 
					{	
						FireSize1=MODE1_SMALL_FIRE1;
						keyNum=1;
					}
					else if(keyNum==1)
					{	
						FireSize1=MODE3_BIG_FIRE1;
						keyNum=2;
					}
					else if(keyNum==2)
					{	
						FireSize1=MODE4_FLASHING;
						keyNum=3;
						   
					}
					else if(keyNum==3)
					{	
						FireSize1=MODE0_OFF_FIRE;
						keyNum=0;
					}

//kevin 					if(FireSize1==MODE4_FLASHING)
//kevin 					{
//kevin 						if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 64) != HAL_OK)
//kevin 						{
//kevin 							_Error_Handler(__FILE__, __LINE__);
//kevin 						}
//kevin 					}
//kevin 				else 
//kevin 					{
//kevin 					if (HAL_ADC_Stop_DMA(&hadc) != HAL_OK) 
//kevin 						{
//kevin 						_Error_Handler(__FILE__, __LINE__);
//kevin 						}
//kevin 					}
					
				}
				else if(PlayMode!=PLAY_BT)//蓝牙关机情况打开lihgt，只有小火和关闭两种情况
				{
					if(keyNum==0)
					{	
						FireSize1=MODE1_SMALL_FIRE1;
						keyNum=1;
						PlayMode = PLAY_ON;
					}
					else
					{	
						FireSize1=MODE0_OFF_FIRE;
						keyNum=0;
						PlayMode = PLAY_OFF;
					}
				}
				Usart1SendData_DMA(&SPASongs_Num_Table[keyNum][0]);
				break;
			}
		}
	}
}































