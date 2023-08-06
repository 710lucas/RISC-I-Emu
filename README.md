## Simples documentação

A maior parte das instruções possuem as seguintes caracteristicas:

- Possuem 6 bytes
- Informam: opcode (1 byte), operando1 (2 bytes), operando2 (2 bytes), operando3 (1 byte)

Estrutura de algumas instruções:

 - Add: (0x01)

    - 0x01 - opcode
    - 0x0000 - operando1

        - 0xAABB
        - 0xAA → se for de 0 ate 0x1F, indica a posicao do registrador, se passar de 0x1F, pega o valor em 0x00BB
    - 0x0000 - operando2, mesma lógica do 1
    - 0x00 - operando3 → em qual registrador sera salvo o resultado