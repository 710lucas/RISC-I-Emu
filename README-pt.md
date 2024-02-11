[English](README.md)

# Emulador de RISC-I

Este projeto foi feito com o intuito de apenas me aprofundar mais no conhecimento dos opcodes do RISC-I, ele não foi testado muito a fundo e pode apresentar inúmeros problemas, então não considerem este projeto como uma emulação fiel ao RISC-I proposto por David A. Patterson, uma vez que, além de não estar completo, ele ainda possui decisões tomadas por mim, que fazem com que ele seja fundamentalmente diferente do modelo RISC-I originalmente proposto.



## Documentação simples

A maior parte das instruções possuem as seguintes caracteristicas:

- Possuem 6 bytes
- Informam: opcode (1 byte), operando1 (2 bytes), operando2 (2 bytes), operando3 (1 byte)


---

**Como os operandos funcionam:**

Um operando pode tanto resultar em um valor imediato, quanto em um valor armazenado em um registrador.

Temos registradores de 0x00 ate 0x1F, acima disso é impossível recuperar um valor de um registrador.

Logo, o primeiro byte informa qual registrador deve ser recuperado, caso este valor seja acima de 0x1F (a partir de 0x20), o emulador irá recuperar o valor imediato no segundo byte.

Por exemplo:

- 0x0100 -> recupera o valor no registrador (0x01)
- 0xFF05 -> recupera o valor imediato 0x05, já que o valor do primeiro byte(0xFF) é maior que 0x1F

**Exceção para terceiro operando**

Como o terceiro operando possui apenas um byte, ele **sempre** irá representar um registrador

---

**Dicionario:**

Op1: primeiro operando, informa os 2 bytes correspondentes ao primeiro operando

Op2: segundo operando, informa os 2 bytes correspondentes ao segundo operando

Op3: terceiro operando, informa o byte correspondente ao terceiro operando

<br>

a: Valor no op1 (pode tanto ser valor em registrador quanto valor direto)

b: Valor no op2 (pode tanto ser valor em registrador quanto valor direto)

---

Estrutura de algumas instruções:

 - Add: (0x01):
   - 
     - 0x01 - opcode
     - 0x0000 - op1
     - 0x0000 - op2
     - 0x00 - op3 → em qual registrador sera salvo o resultado
     -  registradores[op3] = a+b
     - Exemplo:
       - 
       - 0x01FF01FF0401
         - 0x01: opcode de adicionar
         - 0xff01 -> pegar valor 1
         - 0xff04 -> pegar valor 4
         - 0x01 -> armazenar 1 + 4 no registrador 01
       - 0x010001FF0502
         - 0x01: opcode
         - 0x0001 -> pegar valor em registrador 01 (valor = 5)
         - 0xFF05 -> pegar valor 5
         - 0x02 -> armazenar valor de 5+5 no registrador 2

- ADDC  (0x02):
  - 
  - Funciona da mesma maneira que o ADD, mas irá incrementar um caso a flag de carry tenha sido ativada
  
---
- Sub (0x03) & SUBC (0x04):
  - 
  - Funciona da mesma maneira que a adição e addc, basta mudar o opcode

---
- AND (0x06):
  - 
  - Irá realizar a operação AND entre os valores **a** e **b** e armazenar no **op3**
  - registradores[op3] = a&b

---
- OR (0x07):
  - 
   - Irá realizar a operação OR entre os valores **a** e **b** e armazenar no **op3**
   - registradores[op3] = a|b

---
- XOR (0x08):
  - 
   - Irá realizar a operação XOR entre os valores **a** e **b** e armazenar no **op3**
   - registradores[op3] = a^b

   
---
- SLL (0x09), Shift Left Logical:
  - 
  - Realiza um shift left com o valor de **a**, a quantidade de shifts é determinada por **b** e o resultado é armazenado em **op3**
  - registradores[op3] = a << b;
  - 
---
- SRL (0x0A), Shift Right Logical:
  - 
  - Realiza um right shift logical no valor de **a**, a quantidade de shifts é determinada por **b** e o resultado é armazenado em **op3**
  - registradores[op3] = a >>> b;
---
- SRA (0x0B), Shift Right Arithmetic:
  - 
   - Realiza um right shift arithmetic no valor de **a**, a quantidade de shifts é determinada por **b** e o resultado é armazenado em **op3**
   - registradores[op3] = a >> b;
---
- LDL (0x0C), Load
  - 
  - Carrega um dado da memória na posição a+b e salva o seu valor em op3
  - registradores[op3] = memory[a+b]
  - obs.: a memória é organizada em bytes e os registradores em bits, logo, esta operação não é tão simples quanto parece, na verdade pegamos os 4 bytes a partir de a+b e, a partir deles, calculamos o valor inteiro que deve ser armazenado
---
- STL (0x0B), Store:
  - 
  - Pega os valores no registrador op3 e salva na localização de memoria a+b
  - memory[a+b] = registradores[op3]
  - obs.: Assim como o load, há uma diferença no tamanho dos tipos de dados, onde é necessário armazenar o valor do registrador em 4 endereços de memória
---
- JMP
- JMPR
- CALL
- RET

