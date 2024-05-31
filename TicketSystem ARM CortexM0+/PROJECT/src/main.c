/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>


__asm void ekdosi (int stili_pinaka1, int seira_pinaka1, int stili_pinaka2, int xrimata, int *array){
	
		
		MOVS R5,R4 // METAKINO TIN DIEUTHINSI POU THA GRAPSO STON R5
		ADDS R5,R5,#12 // Epeidi i dieuthinsi r5 stin opoia meta tha grapso, einai idia me ton sp kano +12 oste na mporo na kano push 3 stoixeia kai na min graftoun pano sta stoixeia poy exo apothikeysei. Episis eksipiretei se periptosi poy ksanankaleso tin sinartisi, oste na grapso se 3 theseis pio kato apo tin arxiki.


		PUSH{LR} // KRATAO TON LR GIA XRISI PIO META
	  BL matrix1 // Proto Pliktrologio
		CMP R6,#255
		BEQ error // An to r6 exei to 255 tote exo error(den vrethike) 
	
	  BL matrix2 // Deutero Pliktrologio
		CMP R2,#255
		BEQ error // An to r2 exei to 255 tote exo error(den vrethike) 
		
	
		//R6 XARAKTIRISMOS, R2 DROMOLOGIA, R4 KOSTOS
	  
		MULS R4,R2,R4 // GIA NA VRO KOSTOS EINAI TIMI ANALOGA TO EIDOS * DROMOLOGIA(EITE 1 EITE 10)
	  CMP R4,R3
		BHI error // An to kostos einai megalitero apo ta xrimata pou vazo tote branch
		
		
		
		STR R7,[R5] // STORE TON KODIKO, tin proti fora o r7 einai kenos, opote tha apothikeuso to 0. Epeita tha kano +1 gia na apothikeuontai oi kodikoi me seira.
		STR R2, [R5,#4] // STORE DIADROMES
		STR R6, [R5,#8] // STORE XARAKTIRISO

		ADDS R7,R7,#1 // GIA TON EPOMENO KODIKO	
		MOVS R4,R5	// vazo tin dieuthinsi mnimis ston r4 oste na perasei stin epomeni fora poy kalo tin sinartisi
	
error
		POP{PC} // pop to arxiko LR ston PC oste na teleiosei i sinartisi
	
	
		
}

	__asm void epikirosi (int kodikos,int *array){
		
		MOVS R2,#0
loop
		
		ADDS R1,R1,#12 // psaxno kathe 12h timi tis mnimis afou ekei apothikeusa tous kodikous eisitirion.
		LDR R3,[R1]
		
		CMP R3,R0 // kano compare tin timi  R3 pou fortono kathe fora, me ton kodiko eisitiriou R0, ean einai idia tote to isitirio einai valid
		BEQ valid
		MOVS R4,#8 // EVALA GIA PARADEIGMA 8 EPANALIPSEIS, KANONIKA THA EVAZA POLI PERISSOTERES EFOSON EXOUME MIA MEGALI MNIMI 
		ADDS R2,#1 // Gia tis epanalipseis
		CMP R2,R4
		BNE loop // Kanei loop gia tis protes 8 theseis, an den vrethei to eisitiro tote einai invalid kai kleinei i sinartisi
		
		BX LR 
valid
	
		LDR R3,[R1,#4]//4 theseis meta ton kodiko vriskontai oi diadromes tou eisitiriou. Load ston R3 tis diadromes tou valid eisitiriou (ara R1+4)
		SUBS R3,R3,#1 // afairo mia diadromi opos leei i ekfonisi
		STR R3,[R1,#4]// ananenono tis diadromes
		MOVS R0,#0
		CMP R3,R0
		BEQ diagrafi // an einai oi diadromes ises me 0 tote diagrafi tou eisitiriou
		BX LR
diagrafi
		MOVS R0,#0
		STR R0,[R1]// midenizo tin thesi mnimis opou vriskotan to eisitirio me 0 diadromes
	BX LR
	}
	__asm void matrix1 (){
 
			CMP R0,#1
			BEQ stili1
		 
		  CMP R0,#2
			BEQ stili2
			
			CMP R0,#4
			BEQ stili3	
			
			CMP R0,#8
			BEQ stili4
	
exit  
			 MOVS R6,#255 // ERROR PREPEI NA KSANARXIZEI TO PROGRAMMA 
			 BX LR
			 
		  
		
		
stili1
seira1_1
			CMP R1,#1
			BNE seira2_1
			MOVS R6,#0
			MOVS R4,#1 // TIMI TRAINOU
			BX LR
seira2_1
			CMP R1,#2
			BNE seira3_1
			MOVS R6,#4
			MOVS R4,#1 // TIMI LEOF
			BX LR
seira3_1	
			CMP R1,#4
		  BNE seira4_1
		  MOVS R6,#8
			MOVS R4,#2 // TIMI DIPLOU
			BX LR
seira4_1		  
			CMP R1,#8
			BNE exit
			MOVS R6,#12
			MOVS R4,#3
			BX LR
			
stili2
seira1_2
			CMP R1,#1
			BNE seira2_2
			MOVS R6,#1
			MOVS R4,#1
			BX LR
seira2_2
			CMP R1,#2
			BNE seira3_2
			MOVS R6,#5
			MOVS R4,#2
			BX LR
seira3_2	
			CMP R1,#4
			BNE seira4_2
		  MOVS R6,#9
			MOVS R4,#3
			BX LR
seira4_2
		  CMP R1,#8
		  BNE exit
		  MOVS R6,#13
			MOVS R4,#4
		  BX LR
	
stili3
seira1_3
			CMP R1,#1
			BNE seira2_3
			MOVS R6,#2
			MOVS R4,#1
			BX LR
seira2_3
			CMP R1,#2
			BNE seira3_3
			MOVS R6,#6
			MOVS R4,#2
			BX LR
seira3_3	
			CMP R1,#4
		  BNE seira4_3
		  MOVS R6,#10
			MOVS R4,#3
			BX LR
seira4_3
	 	  CMP R1,#8
			BNE exit
			MOVS R6,#14
			MOVS R4,#4
			BX LR
	
stili4
seira1_4
			CMP R1,#1
			BNE seira2_4
			MOVS R6,#3
			MOVS R4,#1
			BX LR
seira2_4
			CMP R1,#2
			BNE seira3_4
			MOVS R6,#7
			MOVS R4,#2
			BX LR
seira3_4	
			CMP R1,#4
		 	BNE seira4_4
		  MOVS R6,#11
			MOVS R4,#3
			BX LR
seira4_4
		  CMP R1,#8
			BNE exit
			MOVS R6,#15 // en teli exo ston R6 to pliktro epilogis eisitiriou
			MOVS R4,#4
			BX LR

	
				
			}
	
	__asm void matrix2 (){
			CMP R2,#1
			BEQ stili1b		
		  CMP R2,#2
			BEQ stili2b
exitb  
			 MOVS R2,#255 // ERROR PREPEI NA KSANARXIZEI TO PROGRAMMA 

stili1b 
			MOVS R2,#1
			BX LR
stili2b 
			MOVS R2,#10
			BX LR		
			
			
			}	

	
	int main(void)
	{
		int stili_pinaka1= 8;
		int seira_pinaka1= 1;
		int stili_pinaka2= 2;
		int xrimata = 15;
		int array[31] ;
		int kodikos;	
		ekdosi(stili_pinaka1, seira_pinaka1, stili_pinaka2, xrimata, array);
	
		
		stili_pinaka1=2;
		seira_pinaka1=2;
		stili_pinaka2=1;
		xrimata = 4; 
		ekdosi(stili_pinaka1, seira_pinaka1, stili_pinaka2, xrimata, array);
	
		
		stili_pinaka1=1;
		seira_pinaka1=4;
		stili_pinaka2=2;
		xrimata = 40;
		ekdosi(stili_pinaka1, seira_pinaka1, stili_pinaka2, xrimata, array);
		
		
		kodikos=2;
		epikirosi(kodikos,array);
		

		while (1)
		;
}
// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
