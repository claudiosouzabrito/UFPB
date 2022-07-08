;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*              MODIFICAÇÕES PARA USO COM 12F675                   *
;*                FEITAS PELO PROF. MARDSON                        *
;*                      MARÇO DE 2021                              *
;*                 BASEADO NO EXEMPLO DO LIVRO                     *
;*           Desbravando o PIC. David José de Souza                *
;*-----------------------------------------------------------------*
;*   MODELO PARA O PIC 12F675                                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ARQUIVOS DE DEFINIÇÕES                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#INCLUDE <p12f675.inc>	;ARQUIVO PADRÃO MICROCHIP PARA 12F675

	__CONFIG _BODEN_OFF & _CP_OFF & _PWRTE_ON & _WDT_OFF & _MCLRE_ON & _INTRC_OSC_NOCLKOUT

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                    PAGINAÇÃO DE MEMÓRIA                         *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;DEFINIÇÃO DE COMANDOS DE USUÁRIO PARA ALTERAÇÃO DA PÁGINA DE MEMÓRIA
#DEFINE	BANK0	BCF STATUS,RP0	;SETA BANK 0 DE MEMÓRIA
#DEFINE	BANK1	BSF STATUS,RP0	;SETA BANK 1 DE MAMÓRIA

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                         VARIÁVEIS                               *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DOS NOMES E ENDEREÇOS DE TODAS AS VARIÁVEIS UTILIZADAS 
; PELO SISTEMA

	CBLOCK	0x20	;ENDEREÇO INICIAL DA MEMÓRIA DE
					;USUÁRIO
		W_TEMP		;REGISTRADORES TEMPORÁRIOS PARA USO
		STATUS_TEMP	;JUNTO ÀS INTERRUPÇÕES
		
		
		;COLOQUE AQUI SUAS NOVAS VARIÁVEIS
		;NÃO ESQUEÇA COMENTÁRIOS ESCLARECEDORES
		
		FLAG  ; PARA CONTROLE DE TEMPO

		

	ENDC			;FIM DO BLOCO DE DEFINIÇÃO DE VARIÁVEIS

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                        FLAGS INTERNOS                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DE TODOS OS FLAGS UTILIZADOS PELO SISTEMA

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                         CONSTANTES                              *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DE TODAS AS CONSTANTES UTILIZADAS PELO SISTEMA

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                           ENTRADAS                              *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DE TODOS OS PINOS QUE SERÃO UTILIZADOS COMO ENTRADA
; RECOMENDAMOS TAMBÉM COMENTAR O SIGNIFICADO DE SEUS ESTADOS (0 E 1)

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                           SAÍDAS                                *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; DEFINIÇÃO DE TODOS OS PINOS QUE SERÃO UTILIZADOS COMO SAÍDA
; RECOMENDAMOS TAMBÉM COMENTAR O SIGNIFICADO DE SEUS ESTADOS (0 E 1)

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       VETOR DE RESET                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	ORG	0x00			;ENDEREÇO INICIAL DE PROCESSAMENTO
	GOTO	INICIO
	
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                    INÍCIO DA INTERRUPÇÃO                        *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; ENDEREÇO DE DESVIO DAS INTERRUPÇÕES. A PRIMEIRA TAREFA É SALVAR OS
; VALORES DE "W" E "STATUS" PARA RECUPERAÇÃO FUTURA

	ORG	0x04			;ENDEREÇO INICIAL DA INTERRUPÇÃO
	MOVWF	W_TEMP		;COPIA W PARA W_TEMP
	SWAPF	STATUS,W
	MOVWF	STATUS_TEMP	;COPIA STATUS PARA STATUS_TEMP

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                    ROTINA DE INTERRUPÇÃO                        *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; AQUI SERÃO ESCRITAS AS ROTINAS DE RECONHECIMENTO E TRATAMENTO DAS
; INTERRUPÇÕES
	BTFSS	PIR1, TMR1IF	;INTERRUPCAO CAUSADA PELO TEMPO?
	GOTO	CONVERSOR	;SE NAO, VA PARA A SAIDA BCD
	BSF	ADCON0, 1	;SE SIM, ATIVE A CONVERSAO E VA EMBORA
	GOTO	SAI_INT
	
CONVERSOR
	MOVLW	.231
	SUBWF	ADRESH, W
	BTFSS	STATUS, C   ;TENSAO MAIOR QUE 4,5?
	GOTO	TALVEZ8	    ;NAO, TESTAR COM OUTROS VALORES
	BSF	GPIO, GP5   ;SIM, BCD DE 9
	BCF	GPIO, GP4
	BCF	GPIO, GP1
	BSF	GPIO, GP0
	GOTO	SAI_INT
	
TALVEZ8
	MOVLW	.205
	SUBWF	ADRESH, W
	BTFSS	STATUS, C   ;TENSAO MAIOR QUE 4?
	GOTO	TALVEZ7	    ;NAO, TESTAR COM OUTROS VALORES
	BSF	GPIO, GP5   ;SE SIM, BCD DE 8
	BCF	GPIO, GP4
	BCF	GPIO, GP1
	BCF	GPIO, GP0
	GOTO	SAI_INT
	
TALVEZ7
	MOVLW	.180
	SUBWF	ADRESH, W
	BTFSS	STATUS, C   ;TENSAO MAIOR QUE 3,5?
	GOTO	TALVEZ6	    ;NAO, TESTAR COM OUTROS VALORES
	BCF	GPIO, GP5   ;SE SIM, BCD
	BSF	GPIO, GP4
	BSF	GPIO, GP1
	BSF	GPIO, GP0
	GOTO	SAI_INT
	
TALVEZ6
	MOVLW	.154
	SUBWF	ADRESH, W
	BTFSS	STATUS, C   ;TENSAO MAIOR QUE 3?
	GOTO	TALVEZ5	    ;NAO, TESTAR COM OUTROS VALORES
	BCF	GPIO, GP5   ;SE SIM, BCD
	BSF	GPIO, GP4
	BSF	GPIO, GP1
	BCF	GPIO, GP0
	GOTO	SAI_INT
	
TALVEZ5
	MOVLW	.129
	SUBWF	ADRESH, W
	BTFSS	STATUS, C   ;TENSAO MAIOR QUE 2,5?
	GOTO	TALVEZ4	    ;NAO, TESTAR COM OUTROS VALORES
	BCF	GPIO, GP5   ;SE SIM, BCD
	BSF	GPIO, GP4
	BCF	GPIO, GP1
	BSF	GPIO, GP0
	GOTO	SAI_INT
	
TALVEZ4
	MOVLW	.103
	SUBWF	ADRESH, W
	BTFSS	STATUS, C   ;TENSAO MAIOR QUE 2?
	GOTO	TALVEZ3	    ;NAO, TESTAR COM OUTROS VALORES
	BCF	GPIO, GP5   ;SE SIM, BCD
	BSF	GPIO, GP4
	BCF	GPIO, GP1
	BCF	GPIO, GP0
	GOTO	SAI_INT
	
TALVEZ3
	MOVLW	.77
	SUBWF	ADRESH, W
	BTFSS	STATUS, C   ;TENSAO MAIOR QUE 1,5?
	GOTO	TALVEZ2	    ;NAO, TESTAR COM OUTROS VALORES
	BCF	GPIO, GP5   ;SE SIM, BCD
	BCF	GPIO, GP4
	BSF	GPIO, GP1
	BSF	GPIO, GP0
	GOTO	SAI_INT
	
TALVEZ2
	MOVLW	.52
	SUBWF	ADRESH, W
	BTFSS	STATUS, C   ;TENSAO MAIOR QUE 1?
	GOTO	TALVEZ1	    ;NAO, TESTAR COM OUTROS VALORES
	BCF	GPIO, GP5   ;SE SIM, BCD
	BCF	GPIO, GP4
	BSF	GPIO, GP1
	BCF	GPIO, GP0
	GOTO	SAI_INT
	
TALVEZ1
	MOVLW	.26
	SUBWF	ADRESH, W
	BTFSS	STATUS, C   ;TENSAO MAIOR QUE 0,5?
	GOTO	TALVEZ0	    ;NAO, TESTAR COM OUTROS VALORES
	BCF	GPIO, GP5   ;SE SIM, BCD
	BCF	GPIO, GP4
	BCF	GPIO, GP1
	BSF	GPIO, GP0
	GOTO	SAI_INT
	
TALVEZ0
	BCF	GPIO, GP5   ;BCD DE 0
	BCF	GPIO, GP4
	BCF	GPIO, GP1
	BCF	GPIO, GP0
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                 ROTINA DE SAÍDA DA INTERRUPÇÃO                  *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; OS VALORES DE "W" E "STATUS" DEVEM SER RECUPERADOS ANTES DE 
; RETORNAR DA INTERRUPÇÃO

SAI_INT
	BCF PIR1, TMR1IF   ;ZERANDO BIT DE ESTOURO DE TIMER
	BCF PIR1, ADIF	   ;ZERANDO BIT DE ESTOURO DE CONVERSOR
	SWAPF	STATUS_TEMP,W
	MOVWF	STATUS		;MOVE STATUS_TEMP PARA STATUS
	SWAPF	W_TEMP,F
	SWAPF	W_TEMP,W	;MOVE W_TEMP PARA W
	RETFIE

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*	            	 ROTINAS E SUBROTINAS                      *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; CADA ROTINA OU SUBROTINA DEVE POSSUIR A DESCRIÇÃO DE FUNCIONAMENTO
; E UM NOME COERENTE ÀS SUAS FUNÇÕES.

DELAY
	;CORPO DA ROTINA
	MOVLW	.60
	MOVWF	TMR1H
	MOVLW	.222   
	MOVWF	TMR1L
	
TESTE	    ;TESTANDO ATE ENCONTRAR ESTOURO
	BTFSS	PIR1, TMR1IF
	GOTO	TESTE

	RETURN
	

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIO DO PROGRAMA                          *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
INICIO
	BANK1				;ALTERA PARA O BANCO 1
	MOVLW	B'00000100' ;CONFIGURA TODAS AS PORTAS DO GPIO (PINOS)
	MOVWF	TRISIO		;COMO SAÍDAS
	MOVLW	B'00010100'
	MOVWF	ANSEL 		;DEFINE PORTAS COMO Digital ou analogico I/O
	MOVLW	B'00000111'
	MOVWF	OPTION_REG	;DEFINE OPÇÕES DE OPERAÇÃO
	MOVLW	B'11000000'
	MOVWF	INTCON		;DEFINE OPÇÕES DE INTERRUPÇÕES
	MOVLW	B'01000001'	;DEFININDO INTERRUPCOES DE TIMER1 E A/D CONVERTER
	MOVWF	PIE1
	BANK0				;RETORNA PARA O BANCO
	MOVLW	B'00010001'	;DEFINE O TIMER1
	MOVWF	T1CON
	MOVLW	B'00000111'
	MOVWF	CMCON		;DEFINE O MODO DE OPERAÇÃO DO COMPARADOR ANALÓGICO
	MOVLW	B'00001001'
	MOVWF	ADCON0		;CONVERSOR A/D

	
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIALIZAÇÃO DAS VARIÁVEIS                 *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ROTINA PRINCIPAL                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
MAIN

	;CORPO DA ROTINA PRINCIPAL
	CALL	DELAY	   ;CAUSANDO DELAY DE APROXIMADAMENTE 100MS
VOLTA	
	BTFSC	ADCON0, 1  ;EXECUTANDO CONVERSAO
	GOTO	VOLTA

	
	
	GOTO	MAIN 

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       FIM DO PROGRAMA                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	END
