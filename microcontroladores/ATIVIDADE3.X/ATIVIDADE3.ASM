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
		SEM1  ; REPRESENTA O SEMAFORO 1, BIT 0 = VERDE, BIT 1 = AMARELO, BIT 2 = VERMELHO
		SEM2  ; REPRESENTA O SEMAFORO 2, BIT 0 = VERDE, BIT 1 = AMARELO, BIT 2 = VERMELHO
		

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

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                 ROTINA DE SAÍDA DA INTERRUPÇÃO                  *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; OS VALORES DE "W" E "STATUS" DEVEM SER RECUPERADOS ANTES DE 
; RETORNAR DA INTERRUPÇÃO

SAI_INT
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

DELAY2S
	;CORPO DA ROTINA
	MOVLW .30	    ;O PROCESSO DE COMECOMAXIMO2S ACONTECE 30 VEZES
	MOVWF FLAG
	
COMECOMAXIMO2S
	MOVLW .0	    ;IREMOS PERCORRER 256 NO MAIOR RATE 1:256
	MOVWF TMR0  
	BCF INTCON, T0IF    ;ZERANDO BIT DE ESTOURO DE TIMER
TESTEMAXIMO2S		    ;TESTANDO ATE ENCONTRAR ESTOURO
	BTFSS INTCON, T0IF
	GOTO TESTEMAXIMO2S
	
	DECF FLAG, 1        ;CONTROLANDO O LACO
	BTFSS STATUS, Z	    
	GOTO COMECOMAXIMO2S ;256X256 EH UM NUMERO PEQUENO, ENTAO PRECISAMOS REPETIR 30 VEZES
	
COMECORESTO2S               ;COM O INTUITO DE CHEGAR NO 2 SEGUNDOS EXATOS, FAREMOS MAIS 125 X 256
	MOVLW .125
	MOVWF TMR0  
	BCF INTCON, T0IF    ;ZERANDO T0IF POIS FOI ESTOURADO ANTERIORMENTE
TESTERESTO2S
	BTFSS INTCON, T0IF  ;
	GOTO TESTERESTO2S
	
	MOVLW .10
	MOVWF FLAG
TESTEFINAL2S		    ;FINALMENTE FECHAMOS OS 2 SEGUNDOS COM ESSE ULTIMO PEDACO
	DECF FLAG
	BTFSS STATUS, Z
	GOTO TESTEFINAL2S
	NOP
	NOP
	RETURN
	
	
	
DELAY05S

	;CORPO DA ROTINA
	MOVLW .8             ;O PROCESSO DE COMECOMAXIMO05S ACONTECE 8 VEZES
	MOVWF FLAG
	
COMECOMAXIMO05S
	MOVLW .12            ;POR CALCULOS ENCONTREI QUE 8X256X244 CHEGAVA PERTO DE 500000 = 0,5 S
	MOVWF TMR0	     ;POR ISSO USAMOS 12 PARA O TMR0 
	BCF INTCON, T0IF 
TESTEMAXIMO05S
	BTFSS INTCON, T0IF
	GOTO TESTEMAXIMO05S
	
	DECF FLAG, 1
	BTFSS STATUS, Z
	GOTO COMECOMAXIMO05S ;CONTROLAND O LACO DE FLAG = 8
	
	MOVLW .48
	MOVWF FLAG
TESTEFINAL05S                ;ESSE ULTIMO TRECHO EH PARA CHEGAR NOS EXATOS 0,5 SEGUNDOS
	DECF FLAG
	BTFSS STATUS, Z
	GOTO TESTEFINAL05S
	NOP
	NOP
	RETURN

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIO DO PROGRAMA                          *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
INICIO
	BANK1				;ALTERA PARA O BANCO 1
	MOVLW	B'00000000' ;CONFIGURA TODAS AS PORTAS DO GPIO (PINOS)
	MOVWF	TRISIO		;COMO SAÍDAS
	CLRF	ANSEL 		;DEFINE PORTAS COMO Digital I/O
	MOVLW	B'00000111'
	MOVWF	OPTION_REG	;DEFINE OPÇÕES DE OPERAÇÃO
	MOVLW	B'00000000'
	MOVWF	INTCON		;DEFINE OPÇÕES DE INTERRUPÇÕES
	BANK0				;RETORNA PARA O BANCO
	MOVLW	B'00000111'
	MOVWF	CMCON		;DEFINE O MODO DE OPERAÇÃO DO COMPARADOR ANALÓGICO

	
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIALIZAÇÃO DAS VARIÁVEIS                 *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	CLRF    SEM1
	CLRF	SEM2
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ROTINA PRINCIPAL                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
MAIN

	;CORPO DA ROTINA PRINCIPAL
	BSF SEM1, 2   ;ACENDE LUZ VERMELHA DO SEMAFORO 1
	BSF SEM2, 0   ;ACENDE LUZ VERDE DO SEMAFORO 2
	CALL DELAY2S  ;DELAY DE 2 SEGUNDOS
	BSF SEM2, 1   ;ACENDE LUZ AMARELA DO SEMAFORO 2
	CALL DELAY05S ;DELAY DE 0,5 SEGUNDOS
	BCF SEM1, 2   ;APAGA LUZ VERMELHA DO SEMAFORO 1
	BCF SEM2, 0   ;APAGA LUZ VERDE DO SEMAFORO 2
	BCF SEM2, 1   ;APAGA LUZ AMARELO DO SEMAFORO 2
	
	BSF SEM2, 2   ;ACENDE LUZ VERMELHA DO SEMAFORO 2
	BSF SEM1, 0   ;ACENDE LUZ VERDE DO SEMAFORO 1
	CALL DELAY2S  ;DELAY DE 2 SEGUNDOS
	BSF SEM1, 1   ;ACENDE LUZ AMARELA DO SEMAFORO 1
	CALL DELAY05S ;DELAY DE 0,5 SEGUNDOS
	BCF SEM2, 2   ;APAGA LUZ VERMELHA DO SEMAFORO 2
	BCF SEM1, 0   ;APAGA LUZ VERDE DO SEMAFORO 1
	BCF SEM1, 1   ;APAGA LUZ AMARELO DO SEMAFORO 1
	
	GOTO MAIN     ;FICA EM LOOP

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       FIM DO PROGRAMA                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	END
