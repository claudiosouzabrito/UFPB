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
		
		FLAG_PULSO	;flag que controla tipo de pulso
		FLAG_CONTAGEM	;flag que controla quando a main ira chamar a subrotina
		
		;NÃO ESQUEÇA COMENTÁRIOS ESCLARECEDORES

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
	GOTO	INICIO			;ATENCAO, esse eh o momento de usar o estimulo HIGH para GP4
	
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
	
	BTFSC	GPIO, GP4   ;GP4 esta em LOW?
	GOTO	TESTE_2	    ;se nao, fim de pulso, va para verificacao de pulso
	BSF	FLAG_CONTAGEM, 0    ; se sim, a contagem eh liberada e sai da interrupcao
	GOTO	SAI_INT
	
TESTE_2
	MOVLW	.2
	SUBWF	FLAG_PULSO, W	
	BTFSS	STATUS, Z   ;descobrindo se a flag de pulso eh 2 (erro)
	GOTO	TESTE_1	    ;se nao, va verificar se eh 1 (HIGH)
	BSF	GPIO, GP2   ;ON
	BCF	GPIO, GP0   ;OFF
	BCF	GPIO, GP1   ;OFF
	BCF	FLAG_CONTAGEM, 0    ;desliga a flag de contagem para a main nao enviar para a subrotina de novo
	BSF	INTCON, T0IF	    ;desativa a contagem do timer0 na subrotina, voltando a main
	GOTO	SAI_INT	 
TESTE_1
	MOVLW	.1
	SUBWF	FLAG_PULSO, W
	BTFSS	STATUS, Z   ;descobrindo se a flag de pulso eh 1 (high)
	GOTO	FLAG_0	    ;se nao, eh 0 (LOW)
	BSF	GPIO, GP1   ;ON
	BCF	GPIO, GP0   ;OFF
	BCF	GPIO, GP2   ;OFF
	BCF	FLAG_CONTAGEM, 0    ;desliga a flag de contagem para a main nao enviar para a subrotina de novo
	BSF	INTCON, T0IF	    ;desativa a contagem do timer0 na subrotina, voltando a main
	GOTO	SAI_INT
FLAG_0			    ;se nao eh 2 nem 1, eh 0
	BSF	GPIO, GP0   ;ON
	BCF	GPIO, GP1   ;OFF
	BCF	GPIO, GP2   ;OFF
	BCF	FLAG_CONTAGEM, 0    ;desliga a flag de contagem para a main nao enviar para a subrotina de novo
	BSF	INTCON, T0IF	    ;desativa a contagem do timer0 na subrotina, voltando a main
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                 ROTINA DE SAÍDA DA INTERRUPÇÃO                  *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
; OS VALORES DE "W" E "STATUS" DEVEM SER RECUPERADOS ANTES DE 
; RETORNAR DA INTERRUPÇÃO

SAI_INT
	BCF	INTCON, GPIF	;desligando flag de interrupcao de GPIO
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

CONTAGEM

	;CORPO DA ROTINA
	MOVLW	.185	    
	MOVWF	TMR0		;iniciando contagem de 0 < x < 170
	BCF	INTCON, T0IF	;limpando flag de estouro de timer0
LOOP_0_170			;vai ficar no looping ate chegar em 170 ou GP4 mudar de estado
	BTFSS	INTCON, T0IF
	GOTO	LOOP_0_170
	
	BTFSC	GPIO, GP4	;GP4 esta em LOW?
	RETURN			;se nao eh porque o looping quebrou por interrupcao, entao saia da subrotina
				;se sim, segue para o proximo intervalo
	MOVLW	.0
	MOVWF	FLAG_PULSO	;se chegou a 170 pode ser considerado LOW
	MOVLW	.231
	MOVWF	TMR0		;iniciando contagem de 170 < x < 230
	BCF	INTCON, T0IF	;limpando flag de estouro de timer0
LOOP_170_230			;vai ficar no looping ate chegar em 230 ou GP4 mudar de estado
	BTFSS	INTCON, T0IF
	GOTO	LOOP_170_230
	
	BTFSC	GPIO, GP4	;GP4 esta em LOW?
	RETURN			;se nao eh porque o looping quebrou por interrupcao, entao saia da subrotina
				;se sim, segue para o proximo intervalo
	MOVLW	.2
	MOVWF	FLAG_PULSO	;se chegou a 230 pode ser considerado LOW
	MOVLW	.201
	MOVWF	TMR0		;iniciando contagem de 230 < x < 350
	BCF	INTCON, T0IF	;limpando flag de estouro de timer0
LOOP_230_350			;vai ficar no looping ate chegar em 350 ou GP4 mudar de estado
	BTFSS	INTCON, T0IF
	GOTO	LOOP_230_350
	
	BTFSC	GPIO, GP4	;GP4 esta em LOW?
	RETURN			;se nao eh porque o looping quebrou por interrupcao, entao saia da subrotina
				;se sim, segue para o proximo intervalo
	MOVLW	.1
	MOVWF	FLAG_PULSO	;se chegou a 350 pode ser considerado HIGH
	MOVLW	.211
	MOVWF	TMR0		;iniciando contagem de 350 < x < 450
	BCF	INTCON, T0IF	;limpando flag de estouro de timer0
LOOP_350_450			;vai ficar no looping ate chegar em 450 ou GP4 mudar de estado
	BTFSS	INTCON, T0IF
	GOTO	LOOP_350_450
	
	BTFSC	GPIO, GP4	;GP4 esta em LOW?
	RETURN			;se nao eh porque o looping quebrou por interrupcao, entao saia da subrotina
				;se sim, segue para o proximo intervalo	
	MOVLW	.2
	MOVWF	FLAG_PULSO	;se chegou a 450 pode ser considerado Erro
	MOVLW	.0
	MOVWF	TMR0		;iniciando contagem de 450 < x < 962
	BCF	INTCON, T0IF	;limpando flag de estouro de timer0
LOOP_450_			;vai ficar no looping ate chegar em 962 ou GP4 mudar de estado
	BTFSS	INTCON, T0IF
	GOTO	LOOP_450_
	
	
	RETURN

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIO DO PROGRAMA                          *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	
INICIO
	BANK1				;ALTERA PARA O BANCO 1
	MOVLW	B'00010000' ;CONFIGURA TODAS AS PORTAS DO GPIO (PINOS)
	MOVWF	TRISIO		;COMO SAÍDAS
	CLRF	ANSEL 		;DEFINE PORTAS COMO Digital I/O
	MOVLW	B'00000000'
	MOVWF	OPTION_REG	;DEFINE OPÇÕES DE OPERAÇÃO
	MOVLW	B'10001000'
	MOVWF	INTCON		;DEFINE OPÇÕES DE INTERRUPÇÕES
	MOVLW	B'00010000'
	MOVWF	IOC		;DEFINE INTERRUPTION-ON-CHANGE
	BANK0				;RETORNA PARA O BANCO
	MOVLW	B'00000111'
	MOVWF	CMCON		;DEFINE O MODO DE OPERAÇÃO DO COMPARADOR ANALÓGICO

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     INICIALIZAÇÃO DAS VARIÁVEIS                 *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	MOVLW	.2
	MOVWF	FLAG_PULSO	;flag de pulso comeca em Erro
	MOVLW	.0
	MOVWF	FLAG_CONTAGEM	;flag de contagem inicia desativado pois nao houve pulso ainda

;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                     ROTINA PRINCIPAL                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
MAIN

	;CORPO DA ROTINA PRINCIPAL
	BTFSC	FLAG_CONTAGEM, 0    ;contagem bloqueada?
	CALL	CONTAGEM	    ;se nao, comece a contagem
	GOTO	MAIN		    ;se sim, mantenha no looping ate haver interrupcao no GP4


;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                       FIM DO PROGRAMA                           *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
FIM
	GOTO FIM

	END
