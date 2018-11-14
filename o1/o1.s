.thumb
.syntax unified

.include "gpio_constants.s"     // Register-adresser og konstanter for GPIO

.text
	.global Start
	
Start:
    LDR R0, =PORT_E
    LDR R1, PORT_SIZE
    MUL R0, R0, R1
    LDR R1, =GPIO_BASE
    ADD R0, R0, R1

    MOV R2, #1
    LSL R2, R2, #LED_PIN
    LDR R1, =GPIO_PORT_DOUTSET
    STR R2, [R0,R1]


Loop:
	LDR R6, [R2]  //  Lagre bit-representasjonen til DIN-portregisteret på BUTTON-porten i R6
	AND R6, R6, R4  // AND R6 og R4 i R6
	CMP R6, R4  // Dersom knappen er trykt inn, branch til TurnOn; ellers fortsett til TurnOff
	BEQ TurnOn

TurnOff:
	STR R3, [R0]
	B Loop

TurnOn:
	STR R3, [R1]
	B Loop

NOP // Behold denne på bunnen av fila
