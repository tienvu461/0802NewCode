#include <scale.h>

char TS02_ID[5];
#define	def_TS02_size		50
static int TS02_buff[def_TS02_size];
static int TS02_buff_count;
int8 ID=0;
uint8_t seq_num = 0;



void clear_TS02_buff(void){
    int8 i;
    for( i = 0; i < def_TS02_size; i++ ){
        TS02_buff[i] = '\0';
    }
	TS02_buff_count = 0;
}

void TS02_INIT(void){
	fprintf(TS02, "#MD000A");
	putc(0x0D,TS02);
	delay_ms(200);

	fprintf(TS02, "#CG04");
	putc(0x0D,TS02);
	delay_ms(200);
	
	fprintf(TS02, "#ID0009");
	putc(0x0D,TS02);
	delay_ms(200);

	fprintf(TS02, "#AK0");
	putc(0x0D,TS02);
	delay_ms(200);
}

void sound(int s, int8 t){
	setup_ccp1(CCP_PWM);
   	setup_timer_2(T2_DIV_BY_16, t, 1);
	int n=0;
   	while (n<s)	{
		set_pwm1_duty(300);
	   	delay_ms(50);
		set_pwm1_duty(1023);
	   	delay_ms(25);
		n++;
	}
	setup_ccp1(CCP_OFF);
}

uint8_t ascii2hex(uint8_t value){
	if((value) >= 0x41){
		return (value - 0x37);
	}
	else return (value-0x30);
}

void get_id (void){
	fprintf(TS02, "#?I");
	putc(0x0D,TS02);
	delay_ms(200);
	
	if (TS02_buff!='\0'){
		for(int u = 0; u < strlen(TS02_buff)-1; u++){
			if(TS02_buff[u] == '$'){
				strcpy(&TS02_buff[u], &TS02_buff[u+1]);
				u--;
			}
		}
	}
	strcpy(TS02_ID, TS02_buff);
	ID=ascii2hex(TS02_buff[0])*4096+ascii2hex(TS02_buff[1])*256+ascii2hex(TS02_buff[2])*16+ascii2hex(TS02_buff[3]);
	clear_TS02_buff();
}

void debug (void){
	fprintf(TS02, "\nRESET:%sV.1.3E",TS02_ID );
	while(input(RDY));
}

#INT_RDA
void RDA_isr(void){
	if(kbhit(TS02)){
		TS02_buff[TS02_buff_count] = getc(TS02);
		TS02_buff_count++;
	}
}


void main(void){
	OSCCON=0x72;
	setup_oscillator(OSC_16MHz); //16 mhz
	enable_interrupts(INT_RDA);
	enable_interrupts(GLOBAL);
	
	TS02_INIT();
	
	delay_ms(2000);
	get_id();

	output_low(SET3);
	sound(1, C6);
	sound(1, D6);
	sound(1, E6);
	debug();
	
	while(true){
		if(TS02_buff[TS02_buff_count - 1] == 0x0D){
			int8 i=0;
			for(i = 0; i < strlen(TS02_buff); i++){
				if (((TS02_buff[i] == 0x3F)&&(TS02_buff[i+1] == 0x3F))){
					fprintf(TS02, "S%uN134.3U20.000A20T1S%uN134.3A20T1S%uN134.3A20T1S%uN134.3A20T1S%uN134.3A20T1S%uN134.3A20T1S%uN134.3A20T1S%uN134.3A20T1S%uN134.3A20T1S%uN134.3A20T1E", seq_num,seq_num+1,seq_num+2,seq_num+3,seq_num+4,seq_num+5,seq_num+6,seq_num+7,seq_num+8,seq_num+9);
				    delay_ms(20);
				    while(input(RDY));
				    sound(2,C7);
				    clear_TS02_buff();
				}
				else if((TS02_buff[i] == 'O')  && (TS02_buff[i+1] == 'K')){ //master's response
					clear_TS02_buff();
					sound(2,A6);
					break;
				}
			}
		}
	}	
}			