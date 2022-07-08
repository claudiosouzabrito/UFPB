;*******************************************************************************
;                                                                              *
;    Microchip licenses this software to you solely for use with Microchip     *
;    products. The software is owned by Microchip and/or its licensors, and is *
;    protected under applicable copyright laws.  All rights reserved.          *
;                                                                              *
;    This software and any accompanying information is for suggestion only.    *
;    It shall not be deemed to modify Microchip?s standard warranty for its    *
;    products.  It is your responsibility to ensure that this software meets   *
;    your requirements.                                                        *
;                                                                              *
;    SOFTWARE IS PROVIDED "AS IS".  MICROCHIP AND ITS LICENSORS EXPRESSLY      *
;    DISCLAIM ANY WARRANTY OF ANY KIND, WHETHER EXPRESS OR IMPLIED, INCLUDING  *
;    BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS    *
;    FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT. IN NO EVENT SHALL          *
;    MICROCHIP OR ITS LICENSORS BE LIABLE FOR ANY INCIDENTAL, SPECIAL,         *
;    INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, HARM TO     *
;    YOUR EQUIPMENT, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR    *
;    SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY   *
;    DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER      *
;    SIMILAR COSTS.                                                            *
;                                                                              *
;    To the fullest extend allowed by law, Microchip and its licensors         *
;    liability shall not exceed the amount of fee, if any, that you have paid  *
;    directly to Microchip to use this software.                               *
;                                                                              *
;    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF    *
;    THESE TERMS.                                                              *
;                                                                              *
;*******************************************************************************
;                                                                              *
;    Filename:                                                                 *
;    Date:                                                                     *
;    File Version:                                                             *
;    Author:                                                                   *
;    Company:                                                                  *
;    Description:                                                              *
;                                                                              *
;*******************************************************************************
;                                                                              *
;    Notes: In the MPLAB X Help, refer to the MPASM Assembler documentation    *
;    for information on assembly instructions.                                 *
;                                                                              *
;*******************************************************************************
;                                                                              *
;    Known Issues: This template is designed for relocatable code.  As such,   *
;    build errors such as "Directive only allowed when generating an object    *
;    file" will result when the 'Build in Absolute Mode' checkbox is selected  *
;    in the project properties.  Designing code in absolute mode is            *
;    antiquated - use relocatable mode.                                        *
;                                                                              *
;*******************************************************************************
;                                                                              *
;    Revision History:                                                         *
;                                                                              *
;*******************************************************************************



;*******************************************************************************
; Processor Inclusion
;
; TODO Step #1 Open the task list under Window > Tasks.  Include your
; device .inc file - e.g. #include <device_name>.inc.  Available
; include files are in C:\Program Files\Microchip\MPLABX\mpasmx
; assuming the default installation path for MPLAB X.  You may manually find
; the appropriate include file for your device here and include it, or
; simply copy the include generated by the configuration bits
; generator (see Step #2).
;
;*******************************************************************************

; TODO INSERT INCLUDE CODE HERE
#INCLUDE <p12f617.inc>

;*******************************************************************************
;
; TODO Step #2 - Configuration Word Setup
;
; The 'CONFIG' directive is used to embed the configuration word within the
; .asm file. MPLAB X requires users to embed their configuration words
; into source code.  See the device datasheet for additional information
; on configuration word settings.  Device configuration bits descriptions
; are in C:\Program Files\Microchip\MPLABX\mpasmx\P<device_name>.inc
; (may change depending on your MPLAB X installation directory).
;
; MPLAB X has a feature which generates configuration bits source code.  Go to
; Window > PIC Memory Views > Configuration Bits.  Configure each field as
; needed and select 'Generate Source Code to Output'.  The resulting code which
; appears in the 'Output Window' > 'Config Bits Source' tab may be copied
; below.
;
;*******************************************************************************

; TODO INSERT CONFIG HERE
    __CONFIG _FOSC_INTOSCIO & _WDTE_OFF & _PWRTE_ON & _MCLRE_OFF & _CP_OFF & _IOSCFS_8MHZ & _BOREN_OFF & _WRT_OFF
    
    #DEFINE	BANK0	BCF STATUS,RP0	;SETA BANK 0 DE MEMÓRIA
    #DEFINE	BANK1	BSF STATUS,RP0	;SETA BANK 1 DE MAMÓRIA
;*******************************************************************************
;
; TODO Step #3 - Variable Definitions
;
; Refer to datasheet for available data memory (RAM) organization assuming
; relocatible code organization (which is an option in project
; properties > mpasm (Global Options)).  Absolute mode generally should
; be used sparingly.
;
; Example of using GPR Uninitialized Data
;
;   GPR_VAR        UDATA
;   MYVAR1         RES        1      ; User variable linker places
;   MYVAR2         RES        1      ; User variable linker places
;   MYVAR3         RES        1      ; User variable linker places
;
;   ; Example of using Access Uninitialized Data Section (when available)
;   ; The variables for the context saving in the device datasheet may need
;   ; memory reserved here.
;   INT_VAR        UDATA_ACS
;   W_TEMP         RES        1      ; w register for context saving (ACCESS)
;   STATUS_TEMP    RES        1      ; status used for context saving
;   BSR_TEMP       RES        1      ; bank select used for ISR context saving
;
;*******************************************************************************

; TODO PLACE VARIABLE DEFINITIONS GO HERE
; DEFINIÇÃO DOS NOMES E ENDEREÇOS DE TODAS AS VARIÁVEIS UTILIZADAS 
; PELO SISTEMA

	CBLOCK	0x20	;ENDEREÇO INICIAL DA MEMÓRIA DE
					;USUÁRIO
		W_TEMP		;REGISTRADORES TEMPORÁRIOS PARA USO
		STATUS_TEMP	;JUNTO ÀS INTERRUPÇÕES
		TESTE
		FINAL
		DELAY
		

		;COLOQUE AQUI SUAS NOVAS VARIÁVEIS
		;NÃO ESQUEÇA COMENTÁRIOS ESCLARECEDORES

	ENDC			;FIM DO BLOCO DE DEFINIÇÃO DE VARIÁVEIS

;*******************************************************************************
; Reset Vector
;*******************************************************************************

RES_VECT  CODE    0x0000            ; processor reset vector
    GOTO    START                   ; go to beginning of program

;*******************************************************************************
; TODO Step #4 - Interrupt Service Routines
;
; There are a few different ways to structure interrupt routines in the 8
; bit device families.  On PIC18's the high priority and low priority
; interrupts are located at 0x0008 and 0x0018, respectively.  On PIC16's and
; lower the interrupt is at 0x0004.  Between device families there is subtle
; variation in the both the hardware supporting the ISR (for restoring
; interrupt context) as well as the software used to restore the context
; (without corrupting the STATUS bits).
;
; General formats are shown below in relocatible format.
;
;------------------------------PIC16's and below--------------------------------
;
ISR       CODE    0x0004           ; interrupt vector location
       MOVWF	W_TEMP		;COPIA W PARA W_TEMP
       SWAPF	STATUS,W
       MOVWF	STATUS_TEMP	;COPIA STATUS PARA STATUS_TEMP
       
       BTFSC	PIR1, TMR1IF	;A INTERRUPCAO FOI CAUSA PELO ESTOURO NO TIMER DO PISCA-PISCA?
       GOTO	ESTOUROU_TIMER	;SE SIM, VA PARA O PISCA-PISCA
       
       BTFSC	GPIO, GP3	;A INTERRUPCAO FOI CAUSADA POR UMA DESCIDA?
       GOTO	SAIDA0		;SE NAO, VA EMBORA SEM FAZER NADA
				;SE SIM...
MENORQ5
       BTFSC	TESTE, 1	;VALOR DE TESTE EH MAIOR QUE 1?
       GOTO	ENTRE5_10	;SE SIM, PODE ESTAR EM OUTRO INTERVALO
       MOVLW	B'00110110'	;SE NAO, A DISTANCIA EH <5m, PORTANTO LIGA GPIOs
       GOTO	SAIDA1
       
ENTRE5_10
       BTFSC	TESTE, 2	;VALOR DE TESTE EH MAIOR QUE 3?
       GOTO	ENTRE10_15	;SE SIM, PODE ESTAR EM OUTRO INTERVALO
       MOVLW	B'00110110'	;SE NAO, A DISTANCIA EH ENTRE 5m E 10m, PORTANTO LIGA GPIOs
       GOTO	SAIDA1
       
ENTRE10_15
       BTFSC	TESTE, 3	;VALOR DE TESTE EH MAIOR QUE 7?
       GOTO	ENTRE15_20	;SE SIM, PODE ESTAR EM OUTRO INTERVALO
       MOVLW	B'00010110'	;SE NAO, A DISTANCIA EH ENTRE 10m E 15m, PORTANTO LIGA GPIOs
       GOTO	SAIDA1
       
ENTRE15_20
       BTFSC	TESTE, 4	;VALOR DE TESTE EH MAIOR QUE 15?
       GOTO	ENTRE20_25	;SE SIM, PODE ESTAR EM OUTRO INTERVALO
       MOVLW	B'00000110'	;SE NAO, A DISTANCIA EH ENTRE 15m E 20m, PORTANTO LIGA GPIOs
       GOTO	SAIDA1
       
ENTRE20_25
       BTFSC	TESTE, 5	;VALOR DE TESTE EH MAIOR QUE 31?
       GOTO	ENTRE25_	;SE SIM, PODE ESTAR EM OUTRO INTERVALO
       MOVLW	B'00000010'	;SE NAO, A DISTANCIA EH ENTRE 20m E 25m, PORTANTO LIGA GPIO
       GOTO	SAIDA1
       
ENTRE25_
       MOVLW	B'00000000'	;A DISTANCIA EH MAIOR QUE 25, PORTANTO DESLIGA GPIOs
       GOTO	SAIDA1
       
       
ESTOUROU_TIMER
       BCF	PIR1, TMR1IF	;LIMPA O ESTOURO DO TIMER
				;RECARREGA O TIMER PARA 1/4 DE SEGUNDO, POIS
				;PARA PISCAR COM FREQUENCIA DE 2Hz TEM QUE ACENDER A CADA 0,5s,
				;OU SEJA, PRECISA APAGAR E ACENDER INTERCALANDO A CADA 0,25s
       MOVLW	.11		
       MOVWF	TMR1H
       MOVLW	.236
       MOVWF	TMR1L
       
       BTFSC	TESTE, 1	;VALOR DE TESTE EH MAIOR QUE 1 (<5m de distancia)?
       GOTO	SAI_INT		;SE NAO, VA EMBORA SEM FAZER NADA
				;SE SIM CONTINUA
				
       BTFSC	GPIO, GP1	;OS GPs ESTAO DESLIGADOS?
       GOTO	DESLIGAR	;SE NAO DESLIGA
       MOVLW	B'00110110'	;SE SIM, LIGA E SAI DA INTERRUPCAO
       MOVWF	GPIO
       GOTO	SAI_INT
DESLIGAR
       CLRF	GPIO		;DESLIGANDO GPs E SAI DA INTERRUPCAO
       GOTO	SAI_INT
      
       
SAIDA1
       MOVWF	GPIO		;ENVIA PARA GPIO O VALOR DE WREG ATRIBUIDO NA VERIFICACAO ACIMA
       BSF	INTCON, T0IF	;QUANDO VOLTAR DA INTERRUPCAO PRECISA PARAR O TIMER0 DA SUBROTINA
       INCF	FINAL		;DEFINE QUE A VERIFICACAO ACABOU
SAIDA0
       BCF	INTCON, GPIF	;desligando flag de interrupcao de GPIO
SAI_INT
	SWAPF	STATUS_TEMP,W
	MOVWF	STATUS		;MOVE STATUS_TEMP PARA STATUS
	SWAPF	W_TEMP,F
	SWAPF	W_TEMP,W	;MOVE W_TEMP PARA W
	RETFIE
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;SUBROTINAS;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PULSOINPUT
	
	NOP
	NOP
	NOP
	NOP
	NOP
	;CORPO DA ROTINA
	RETURN
	
RANGE1				;ESSA SUBROTINA EH =~ 580us, EH CHAMADA VARIAS VEZES ESPERANDO O RETORNO 
				;DE ECHO
	MOVLW	.2
	MOVWF	DELAY
DELAY1
	BCF	INTCON, T0IF
	MOVLW	.120
	MOVWF	TMR0
LOOP1
	BTFSS	INTCON, T0IF	;A INTERRUPCAO VOLTA AQUI
	GOTO	LOOP1
	
	BTFSC	FINAL, 0
	RETURN
	
	DECF	DELAY
	BTFSC	DELAY, 0
	GOTO	DELAY1
	
	RETURN

	
RANGE2				;ESSA SUBROTINA EH =~ 43500us, EH CHAMADA A ESPERA DO RETORNO DE ECHO. 
				;QUANDO SOMADO COM TODOS OS DELAYS ANTERIORES, CHEGA EM 46400, QUE EH
				;O TEMPO DE IDA E VOLTA DA ONDA ECHO PARA ALGO A 400cm DE DISTANCIA, 
				;O LIMITE DE ALCANCE DO ULTRASSOM POIS: 
				;400(cm) X 58(equacao 3 do datasheet) X 2(ida e volta) = 46400
				;MAS QUANDO O CODIGO CHEGA NESSE PONTO ELE JA PASSOU POR 2900us
				;ENTAO 46400-2900 = 43500
	MOVLW	.82
	MOVWF	DELAY
DELAY2
	BCF	INTCON, T0IF
	MOVLW	.0
	MOVWF	TMR0
LOOP2
	BTFSS	INTCON, T0IF	;A INTERRUPCAO VOLTA AQUI
	GOTO	LOOP2
	
	BTFSC	FINAL, 0
	RETURN
	
	DECF	DELAY
	MOVLW	.0
	ADDWF	DELAY, W
	BTFSS	STATUS, Z
	GOTO	DELAY2
	
	RETURN


;*******************************************************************************
; MAIN PROGRAM
;*******************************************************************************

MAIN_PROG CODE                      ; let linker place main program

START
	BANK1				;ALTERA PARA O BANCO 1
	MOVLW	B'00000000' ;CONFIGURA TODAS AS PORTAS DO GPIO (PINOS)
	MOVWF	TRISIO		;COMO SAÍDAS
	MOVLW	B'00001000'
	MOVWF	IOC
	CLRF	ANSEL 		;DEFINE PORTAS COMO Digital I/O
	MOVLW	B'00000000'
	MOVWF	OPTION_REG	;DEFINE OPÇÕES DE OPERAÇÃO
	MOVLW	B'11001000'
	MOVWF	INTCON		;DEFINE OPÇÕES DE INTERRUPÇÕES
	MOVLW	B'00000001'
	MOVWF	PIE1
	BANK0				;RETORNA PARA O BANCO
	MOVLW	B'00000000'
	MOVWF	CMCON0		;DEFINE O MODO DE OPERAÇÃO DO COMPARADOR ANALÓGICO
	MOVLW	B'00100001'
	MOVWF	T1CON
	
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIALIZAÇÃO DAS VARIÁVEIS                 *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	MOVLW	.0
	MOVWF	FINAL
	
				;DEFININDO 1/4 DE SEGUNDO PARA O PISCA-PISCA
	BCF	PIR1, TMR1IF
	MOVLW	.11
	MOVWF	TMR1H
	MOVLW	.236
	MOVWF	TMR1L
	
	;ATENCAO!!!!!!!!!!!!!!!!!!!!!!
	;PARA ESSE PROJETO FOI CONSIDERADO QUE O TEMPO DE ESPERA DA ONDA ECHO EH REFERENTE A IDA E A VOLTA
	;POIS EH SO NA VOLTA QUE O PULSO DESCE PARA LOW. SENDO ASSIM, DE ACORDO COM A EQUACAO 3 DO DATASHEET
	;UM OBJETO A 5cm DE DISTANCIA VAI LEVAR 5 X 58 X 2 = 580us
	;ATENCAO!!!!!!!!!!!!!!!!!!!!!!
	
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ROTINA PRINCIPAL                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
MAIN

	BSF	GPIO, GP0	;ENVIANDO PULSO TRIGGER DE 10us PARA O ULTRASSOM
	CALL	PULSOINPUT
	BCF	GPIO, GP0	;FIM DE PULSO
	BCF	PIR1, TMR1IF
				;APOS O TRIGGER, O ECHO SERA ENVIADO. GP3 REPRESENTA ECHO, E
				;VAI FICAR HIGH ATE O RETORNO DA ONDA ECHO
ESPERAGP3
	BTFSS	GPIO, GP3	;ESPERA PELO PULSO ECHO SER ENVIADO (STIMULO DE PULSO PARA GP3 RESOLVE)
	GOTO	ESPERAGP3
				;O CODIGO IRA ESPERAR A DESCIDA DO PULSO ECHO E CLASSIFICANDO A DISTANCIA
				;AO LONGO DO PROCESSO
	NOP
	MOVLW	.1
	MOVWF	TESTE
	CALL	RANGE1
	BTFSC	FINAL, 0	;PULSO DESCEU?
	GOTO	FIM		;SE SIM, VA PARA O FIM
				;SE NAO...
				
	MOVLW	.3		;DISTANCIA ENTRE 5 E 10?
	MOVWF	TESTE
	CALL	RANGE1
	BTFSC	FINAL, 0	;PULSO DESCEU?
	GOTO	FIM		;SE SIM, VA PARA O FIM
				;SE NAO...
	
	MOVLW	.7		;DISTANCIA ENTRE 10 E 15?
	MOVWF	TESTE
	CALL	RANGE1
	BTFSC	FINAL, 0	;PULSO DESCEU?
	GOTO	FIM		;SE SIM, VA PARA O FIM
				;SE NAO...
	
	MOVLW	.15		;DISTANCIA ENTRE 15 E 20?
	MOVWF	TESTE
	CALL	RANGE1
	BTFSC	FINAL, 0	;PULSO DESCEU?
	GOTO	FIM		;SE SIM, VA PARA O FIM
				;SE NAO...
	
	MOVLW	.31		;DISTANCIA ENTRE 20 E 25?
	MOVWF	TESTE
	CALL	RANGE1
	BTFSC	FINAL, 0	;PULSO DESCEU?
	GOTO	FIM		;SE SIM, VA PARA O FIM
				;SE NAO...
	
				
	MOVLW	.63		;DISTANCIA ACIMA DE 25?
	MOVWF	TESTE
	CALL	RANGE2	
	
	
FIM
	CLRF	FINAL		;LIMPANDO FLAG DE FINALIZACAO PARA A PROXIMA VEZ
				;O PROJETISTA TOMOU A LIBERDADE DE DEXAR 60ms ATE A PROXIMA
				;VERIFICACAO, COMO DIZ O DATASHEET.
	MOVLW	.114
	MOVWF	DELAY
DELAY4
	BCF	INTCON, T0IF
	MOVLW	.0
	MOVWF	TMR0
LOOP4
	BTFSS	INTCON, T0IF	;A INTERRUPCAO VOLTA AQUI
	GOTO	LOOP4
	
	DECF	DELAY
	MOVLW	.0
	ADDWF	DELAY, W
	BTFSS	STATUS, Z
	GOTO	DELAY4
	
	
	
	GOTO	MAIN		;PROXIMA RODADA

	END
	
	
