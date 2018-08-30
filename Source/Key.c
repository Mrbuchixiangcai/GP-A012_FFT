//ͷ�ļ�header file//
#include "app_main.h"

//�궨��macro definition//
#define  ADCKEY_NUM   1

//���Ͷ���byte definition//


//��������variable definition//
uint8_t   gbKeyPress;     //��������
uint8_t   gbKeyNone;      //û�а�������
uint8_t   KeyValue;       //����ֵ
uint16_t  AdcValue;       //����ɼ���ADֵ
uint8_t   KeyEvent;       //�����¼�
uint8_t   cntKeyLoop;     //��������ѭ�����̰����������������İ���ʱ��
uint8_t   KeyCurValueBK;  //��ǰ����ֵ����
uint8_t   cntKeyLong;
uint8_t   keyNum;
uint8_t   keyBT;
uint8_t   keyBT_bk;



static    uint8_t   KeyCurValue; //������ѹ��ǰֵ��current��ǰ��
static    uint8_t   KeyLastValue;//������ѹ��һ�ε�ֵ

const uint16_t ADKEY_TAB1[ADCKEY_NUM]=  //����������ѹֵ���������ֵ
{
	0x0000,      //T_LIGHT  //����ֻ�ж̰�ģʽ�л�
};
const uint16_t ADKEY_TAB2[ADCKEY_NUM]=  //����������ѹֵ���������ֵ
{
	0x0000+0x50, //T_LIGHT  //����ֻ�ж̰�ģʽ�л�
};

uint8_t SPASongs_Num_Table[4][11]= 
{
	"B005+A00\r\n",
	"B005+K01\r\n",
	"B005+K02\r\n",
	"B005+K03\r\n",
};

//��־λ����flags definetion//


//��������function definetion//
//��ȡ������ѹ����Ӧ��ͬ�������з���ֵ
uint8_t GetKeyValue(void)
{
//	uint8_t  i;
	uint8_t  keyValue=0;
//	AdcValue=HAL_ADC_GetValue(&hadc);//PA0��ȡ��ǰ����IO pin��ѹֵ,��һ�λ�ȡʱ���ܲ��ԣ�ת��ʱ�䲻��
//	if(AdcValue<0x00A0)//�ɼ��������ⰴ����ѹֵҪС��0x00A0
//	{
////		cntIdle=0;
//		for(i=0;i<ADCKEY_NUM;i++)
//		{
//			if((AdcValue>=ADKEY_TAB1[i]) && (AdcValue<=ADKEY_TAB2[i]))//�жϲɼ����İ�����ѹֵΪ��һ������
//			{
//				KeyNum=i+1;//ȷ��Ϊĳ����������Ϊi��ʼ��Ϊ0�����Լ�1
//				break;
//			}
//		}
//	}
	keyBT = BT_POWER();

	if(!KEY_LIGHT())//�ƹⰴ��
		keyValue = T_LIGHT;
	if (keyBT_bk != keyBT)//ÿ���������IO�ڲ����仯ʱ���ܽ��룬��Ȼһֱ�ߵ�ƽ��һֱ����
	{
		keyBT_bk = keyBT;
		if ((!KEY_LIGHT()) && (keyBT))//����ƹⰴ�����º�power����������ͬʱ�������ã��ǾͶ���Ϊ�ƹⰴ��
			keyValue = T_LIGHT;				  //����һֱ����Light���ٰ�power�����ǵƹ�
		else
		{
			if (keyBT)
				PlayMode = PLAY_BT;
			else
				PlayMode = PLAY_OFF;
		}
	}
	
	return keyValue;//���ذ���
}

//������ʱ���յ���GetKeyValue()�ķ���ֵ  һ��̶���������
void KeyEventPorc(uint8_t KeyTmp)
{
	gbKeyPress=0;
	if(KeyCurValue != KeyTmp)//���if�����ȥ�����ᱻִ�����Σ������ν���ʱֱ������
	{//KeyTmpΪ��ʱֵ
		if(KeyCurValueBK != KeyTmp)
			KeyCurValueBK=KeyTmp;
		else //�ڶ��ν���ʱִ����һ��
			KeyCurValue=KeyTmp;
		return;
	}
	if(KeyCurValue == KeyLastValue)
	{
		if((KeyLastValue==0) || (cntKeyLoop==0))
			return;
		if(--cntKeyLoop==0)//����ڵڶ��ν�KeyEventPorc()��������һ�ν���if(KeyCurValue==KeyLastValue)��֮ǰ��ʱ�����渳ֵΪ5
		{//cntKeyLoopΪ5����50msʱ��
			KeyValue=KeyLastValue;//����֮���ȷ���İ�����ֵ��KeyValue
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

//������������
void KeyScan(void)
{
	KeyEventPorc(GetKeyValue());
}

//��������
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
				else if(PlayMode!=PLAY_BT)//�����ػ������lihgt��ֻ��С��͹ر��������
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































